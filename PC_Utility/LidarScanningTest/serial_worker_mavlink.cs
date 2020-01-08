using System;
using System.IO.Ports;
using System.Collections.Generic;
using System.Windows.Forms;
using System.ComponentModel;
using System.Timers;
using System.Linq;
using System.Management;
using System.Management.Instrumentation;

namespace LidarScanningTest1
{
	public enum CommandSendStatusType
	{
		Idle = 0,
		Prosessing=1,
		Timeout=2,
		ErrorReceived=3,
		CommandOK=4
	}
	        
	/// <summary>
	/// Class for working with serial port
	/// </summary>
	public class SerialWorkerClass2
	{
		// Global variable that handle all operations with COM PORT
        SerialPort port;
        
        public int command_timeout = 200;//in ms
        const int max_repeat = 1;//число повторов передаваемой команды

       
        public Queue<string> tx_queue = new Queue<string>();//очередь передаваемых команд
        
        public bool ConnectionState = false;
        public IniParser settings_holder;//используется для работы с файлом настроек
        public Action<byte[]> AnswerReceived;//callback, который передает принятые и обработанные данные
		public Action<bool> SerialFailSignal;//callback, который передает сигнал о ошибке порта в основную форму
		
		BackgroundWorker back_worker = new BackgroundWorker();//обеспечивает отдельный поток, который отвечает за передачу команд
		

		int answer_received = 0;//1 - принято нормально, -1 - команда не распознана, -2 - неверная CRC, -3 - неверная структура, -4 - модуль не смог обработать команду, -5 - timeout
		
		CommandSendStatusType command_send_status = CommandSendStatusType.Idle;
		
		bool serial_locked = false;//блокировка передачи (отключается при запуске новом вызове Send_command_to_device)
		
		public bool slow_mode = false;//медленный режим - для работы c bluetooth
		
        /// <summary>
		/// Создает объект для работы с портом
		/// </summary>
		/// <param name="ini_file_path"></param> Путь, по которому находится INI-файл
		/// <returns></returns>
		public SerialWorkerClass2(string ini_file_path)
		{
            settings_holder = new IniParser(ini_file_path);//для работы с файлом настроек
      		
            back_worker.RunWorkerCompleted += SerialWorkerFail;
      		back_worker.DoWork += DoWork;
      		back_worker.RunWorkerAsync();
      		
      		string slow_mode_str = settings_holder.GetSetting("SERIAL_SETTINGS", "slow_mode");
      		if (slow_mode_str.Length > 0)
      		{
      			if (slow_mode_str == "1")//slow mode
      			{
      				command_timeout = 300;
      				slow_mode = true;
      			}
      		}
      		else
      		{
      			settings_holder.AddSetting("SERIAL_SETTINGS", "slow_mode", "0");
      		}
		}
		
		void SerialWorkerFail(object sender, RunWorkerCompletedEventArgs e)
		{
			if (e == null)
			{
				MessageBox.Show("SerialWorkerFail_0: null");
			}
			else if (e.Error != null) 
			{
				MessageBox.Show("SerialWorkerFail_1:" + e.Error.Message);
			} 
			else if (e.Cancelled) 
			{
				MessageBox.Show("SerialWorkerFail_2: Cancel");
			}
			else
			{
				// Finally, handle the case where the operation 
        		// succeeded.
				if (e.Result == null)
				{
					MessageBox.Show("SerialWorkerFail_3: null");
				}
				else
				{
					MessageBox.Show("SerialWorkerFail_3:" + e.Result.ToString());
				}
				
			}

			var copy = SerialFailSignal;
			if(copy != null) copy(true);//вызываем callback SerialFailSignal
		}
		
		void DoWork(object sender, DoWorkEventArgs e)//бесконечный цикл - связан с автоматической отправкой команд
		{
			long time_from_data_send = 0;
			long time_command_send = 0;//время отправки команды
			int request_cnt = 0;//количество попыток			
			try 
			{
				while(true)
				{
					//сюда попадает, когда принят ответ или истек таймаут
					if (slow_mode == false)
					{
					}
					else
					{
						System.Threading.Thread.Sleep(300);//slow mode - delay
					}
					
					if (tx_queue.Count > 0)//есть ли данные в очереди
					{
						request_cnt = 0;//количество попыток
						string queueElement = tx_queue.Dequeue();//извлекаем из очереди
						command_send_status = CommandSendStatusType.Prosessing;
						
						if (String.IsNullOrEmpty(queueElement))//в очередь попал пустой элемент
						{
							request_cnt = max_repeat+1;//попыток передачи не будет
							answer_received = -1;//ниже выставиться CommandSendStatusType.ErrorReceived;
						}
						else //можно передавать команду
						{
							while (request_cnt <= (max_repeat-1))//0 тоже считется
							{
								int send_res = send_data_to_serial(queueElement);//физически отправляем данные в порт
								if (send_res == -1)//при ошибке произошла ошибка
								{
									var copy = SerialFailSignal;
									if(copy != null) copy(false);//вызываем callback SerialFailSignal
								}
								
								time_command_send = (DateTime.Now.Ticks / 10000);
								time_from_data_send = 0;
								
								while ((answer_received == 0) && (time_from_data_send < command_timeout) && (serial_locked == false))// ожидаем приема данных или таймаута
								{
									System.Threading.Thread.Sleep(20);
									time_from_data_send = (DateTime.Now.Ticks / 10000) - time_command_send;//столько времени прошло от последней отправки команды
								}
								
								if (serial_locked == true) {request_cnt = max_repeat+1;}//повторных попыток не будет
								else if (answer_received == 1) {request_cnt = max_repeat+1;}//повторных попыток не будет
								
								request_cnt++;
							}//while - request_cnt
						}
						
						//попытки запроса закончились - определяем окончательный результат выполнения
						if (serial_locked == true) command_send_status = CommandSendStatusType.Idle;
						else if (time_from_data_send >= command_timeout) command_send_status = CommandSendStatusType.Timeout;
						else if (answer_received < 0) command_send_status = CommandSendStatusType.ErrorReceived;
						else {command_send_status = CommandSendStatusType.CommandOK;}
					}//end if
                    System.Threading.Thread.Sleep(50);
				}//while(true)
				
			} 
			catch (Exception ex)
			{
				e.Result = ex.Message;
				return;
				throw;
			}
		}
		
		
		//вызывается из port, когда в порт приходят данные
		void SerialPortReceivedHandler(object sender, SerialDataReceivedEventArgs e)
		{
			try
			{
				int bytes_to_read = port.BytesToRead;
				byte[]	rx_data = new byte[bytes_to_read];
				port.Read(rx_data, 0, bytes_to_read);

                AnswerReceived?.Invoke(rx_data);//вызываем callback

                //var copy = AnswerReceived;
                //if(copy != null) copy("CRC ERR: " + received_str);//вызываем callback
            }
			catch (SystemException ex)
			{
				MessageBox.Show(ex.Message, "Data Received Event");
			}
		}
		
		
		/// <summary>
		/// Пытается открыть порт (тот, который был указан ранее)
		/// </summary>
		/// <param name="port_name"></param> Номер порта - например, COM1
		/// <param name="baud"></param> Baudrate
		/// <param name="cur_parity"></param> Serial parity
		/// <param name="cur_stop"></param> Serial stop bits
		/// <returns></returns>
		public int OpenSerialPort(string port_name, int baud)
		{
        	try
            {
                // Create object and connect to selected port
                port = new SerialPort(port_name, baud, Parity.None, 8, StopBits.One);
                port.NewLine = "\r\n";
                port.DataReceived += SerialPortReceivedHandler;
                
                port.Open();
				ConnectionState = true;
				
                if (port.IsOpen)
                {
                	Save_Serial_settings();
                	ConnectionState = true;
                	return 1;
                }
                return -1;
            }
        	catch (Exception ex)
            {
                // Free resource
                MessageBox.Show(ex.Message, "Error in open port", MessageBoxButtons.OK);// Show message about error
                port.Dispose();
                ConnectionState = false;
				return 0;
            } //end of try
		}//end of function
		
		
		/// <summary>
		/// Cохраняет настройки порта в конфигурационный файл
		/// </summary>
		/// <returns></returns>
        public void Save_Serial_settings()
        {
        	string serial = port.PortName;
        	settings_holder.AddSetting("SERIAL_SETTINGS", "serial", serial);
        	string baud = port.BaudRate.ToString();
        	settings_holder.AddSetting("SERIAL_SETTINGS", "baud", baud);
        	string parity = port.Parity.ToString();
        	settings_holder.AddSetting("SERIAL_SETTINGS", "parity", parity);
        	string stop_bits = port.StopBits.ToString();
        	settings_holder.AddSetting("SERIAL_SETTINGS", "stopbits", stop_bits);
        	settings_holder.SaveSettings();
        }
        
        /// <summary>
        /// Записывает данные в порт
        /// </summary>
        /// <returns>возвращает 1, если записать в порт можно, иначе возвращает -1</returns>
        public int send_data_to_serial(string data)
        {
        	if (String.IsNullOrEmpty(data)) return 1;//проверка на нулевую строку	
        	
        	try
        	{
        		if ((port != null) && (port.IsOpen))
        		{
        			port.Write(data);
        			answer_received = 0;//ожидаем ответа
        			return 1;
        		}
        		else
        		{
        			ConnectionState = false;
        			return -1;
        		}
        	} catch (Exception e) {
        		ConnectionState = false;
        		return -1;
        		throw;
        	}
        }
        
        public int send_bin_data_to_serial(byte[] data)
        {
        	if (data.Length == 0) 
        		return 1;//проверка на нулевую строку
        	
        	try
        	{
        		if ((port != null) && (port.IsOpen))
        		{
        			port.Write(data, 0, data.Length);
        			answer_received = 0;//ожидаем ответа
        			return 1;
        		}
        		else
        		{
        			ConnectionState = false;
        			return -1;
        		}
        	} catch (Exception e) {
        		ConnectionState = false;
        		return -1;
        		throw;
        	}
        }
        
        /// <summary>
        /// Закрывает порт
        /// </summary>
        /// <returns></returns>
        public void ClosePort()
        {
        	if (port != null)
        	{
        		port.Close();
        	}
        	ConnectionState = false;
        }
        
        /// <summary>
        /// Переключает скоростной режим порта
        /// </summary>
        ///<param name="is_slow_mode"></param> Медленный режим работы порта - для bluetooth
        /// <returns></returns>
        public void SwitchSpeedMode(bool is_slow_mode)
        {
        	slow_mode = is_slow_mode;
        	if (slow_mode == true)
        	{
        		command_timeout = 300;
        		settings_holder.AddSetting("SERIAL_SETTINGS", "slow_mode", "1");
        	}
        	else
        	{
        		command_timeout = 200;
        		settings_holder.AddSetting("SERIAL_SETTINGS", "slow_mode", "0");
        	}
        	settings_holder.SaveSettings();
        	
        }
        
        /// <summary>
        /// Очистить очередь передачи
        /// </summary>
        /// <returns></returns>
        public void CleanTxQueue()
        {
        	tx_queue.Clear();
        }
        
        /// <summary>
        /// Уведомляет объект этого класса о том, что данные нормально декодированы
        /// </summary>
        /// <returns></returns>
        public void ComfirmReceivedOK()
        {
			answer_received = 1;//нормально прянято
        }
        
        /// <summary>
        /// Уведомляет объект этого класса о том, что данные приняты с ошибкой
        /// </summary>
        /// <returns></returns>
        public void ComfirmReceivedFail(int code)
        {
			answer_received = code;
        }
        
         /// <summary>
        /// Проверка, пуста ли очередь отправляемых сообщений
        /// </summary>
        /// <returns>Возвращает true, если очередь пуста</returns>
        public bool TXQuqueIsEmpty()
        {
        	bool result = false;
        	if (tx_queue.Count == 0) {result = true;} 	else {result = false;}
        	return result;
        }
        
        /// <summary>
        /// Запрос состояния выполнения команды передачи
        /// </summary>
        /// <returns></returns>
        public CommandSendStatusType GetTxCommandStatus()
        {
        	return command_send_status;
        }
        
        /// <summary>
		///Блокирует порт на передачу, очищает очередь
		/// </summary>
        public void LockSerialTx()
        {
        	tx_queue.Clear();
        	serial_locked = true;
        	command_send_status = CommandSendStatusType.Idle;
        }
        
        //*************************************************************************************************************************
        
        /*
        /// <summary>
		/// Отправляет в порт команду
		/// </summary>
		/// <param name="command"></param> Строка - имя команды
		/// <param name="data_str"></param> Строка - данные
		/// <param name="address"></param> int - адрес устройства, которому передаем строку
		/// <returns></returns>
        public void Send_command_to_device(string command, string data_str, int address)
        {
        	string work_str = "$";//command begins
        	work_str+=command;//command name
        	work_str+=address.ToString("X2");//device adress
        	work_str+=data_str;//data to send
        	work_str+=crc_functions.Calculate_CRC(work_str.Remove(0,1));//data crc
        	work_str+= "\r\n";

        	if (String.IsNullOrEmpty(work_str) && (work_str.Length > 128))//unknown error
        	{
        		return;
        	}
        	              	
        	if (tx_queue.Count == 0) 
        	{
        		command_send_status = CommandSendStatusType.Prosessing;//сбрасываем состояние команды
        	}
        	
        	serial_locked = false;
        	tx_queue.Enqueue(work_str);//добавляем элемент в очередь
        }
        */
        
        
        //OLD
        public List<String> GetSerialPortInfo2()
        {
        	List<String > portList = new List<string>();
        	
        	using (var searcher = new ManagementObjectSearcher("SELECT * FROM WIN32_SerialPort"))
        	{
        		string[] portnames = SerialPort.GetPortNames();
        		var ports = searcher.Get().Cast<ManagementBaseObject>().ToList();
        		
        		var tList = (from n in portnames
                            join p in ports on n equals p["DeviceID"].ToString()
                            select n + " - " + p["Caption"]).ToList();
        		
        		foreach (string s in tList)
                {
        			portList.Add(s);
                }

        	}
        	return portList;
        }

        //You need to add System.Management.dll to your project references.
        internal class ProcessConnection
        {

        	public static ConnectionOptions ProcessConnectionOptions()
        	{
        		ConnectionOptions options = new ConnectionOptions();
        		options.Impersonation = ImpersonationLevel.Impersonate;
        		options.Authentication = AuthenticationLevel.Default;
        		options.EnablePrivileges = true;
        		return options;
        	}
        	
        	public static ManagementScope ConnectionScope(string machineName, ConnectionOptions options, string path)
        	{
        		ManagementScope connectScope = new ManagementScope();
        		connectScope.Path = new ManagementPath(@"\\" + machineName + path);
        		connectScope.Options = options;
        		connectScope.Connect();
        		return connectScope;
        	}
        }
        
        
        public List<String> GetSerialPortInfo()
        {
        	List<String> comPortInfoList = new List<String>();
        	
        	ConnectionOptions options = ProcessConnection.ProcessConnectionOptions();
        	ManagementScope connectionScope = ProcessConnection.ConnectionScope(Environment.MachineName, options, @"\root\CIMV2");
        	
        	ObjectQuery objectQuery = new ObjectQuery("SELECT * FROM Win32_PnPEntity WHERE ConfigManagerErrorCode = 0");
        	ManagementObjectSearcher comPortSearcher = new ManagementObjectSearcher(connectionScope, objectQuery);
        	
        	using (comPortSearcher)
        	{
        		string caption = null;
        		foreach (ManagementObject obj in comPortSearcher.Get())
        		{
        			if (obj != null)
        			{
        				object captionObj = obj["Caption"];
        				if (captionObj != null)
        				{
        					caption = captionObj.ToString();
        					if (caption.Contains("(COM"))
        					{
        						String comPortInfo = "";
        						comPortInfo = caption.Substring(caption.LastIndexOf("(COM")).Replace("(", string.Empty).Replace(")", string.Empty);
        						comPortInfo = comPortInfo + " " + caption;
        						comPortInfoList.Add(comPortInfo);
        					}
        				}
        			}
        		}
        	}
        	return comPortInfoList;
        }
        
        
        
        //"COM1 - xxxxxxx" -> "COM1"
        public String GetSerialName(String info_str)
        {
        	String result = "";
        	int pos = info_str.IndexOf(' ');
        	if (pos < 0) return info_str;
        	result = info_str.Substring(0,pos);
        	return result;
        }
        
        
	}//end of CLASS
}
