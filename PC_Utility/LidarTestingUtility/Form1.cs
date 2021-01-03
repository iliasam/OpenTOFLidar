using MavLink;
using System;
using System.Collections.Generic;
using System.Data;
using System.Linq;
using System.Windows.Forms;

namespace TDC_Testing_v1
{
    public partial class Form1 : Form
    {
        const double BIN_TIME = 90.0; //in picosec
        const double BIN_LENGTH = 13.63;//in mm

        const int UART_BAUD = 500000;

        SerialWorkerClass2 SerialWorkerObj;
        Mavlink mavlinkObj;
        MavlinkLongPacketClass LongPacketObj = new MavlinkLongPacketClass();
        DataProcesingClass DataProcessingObj;
        MavlinkCommandsSendClass MavlinkCommandsSendObj;

        CalibrationControl.FunctionParamsStruct functParamsMainForm;

        bool numFieldsNeedUpdate = true;

        int RXPacketCnt = 0;

        struct TdcItem
        {
            public int Start;//time of flight - in bin
            public int Width;//pulse witch in bin
            public double StartCorrected;//in bin
        }
        List<TdcItem> TdcList = new List<TdcItem> { };

        DataRecordingClass DataRecordingObj;

        UInt16 DeviceStateBitField = 0; 

        // ********************************************************************

        public Form1()
        {
            InitializeComponent();

            comboBox_ports.Items.Clear();
            SerialWorkerObj = new SerialWorkerClass2(Application.StartupPath + @"\config.ini");
            SerialWorkerObj.AnswerReceived = SerialPortReceivedHandler;
            SerialWorkerObj.SerialFailSignal = SerialFailSignalFunction;

            MavlinkCommandsSendObj = new MavlinkCommandsSendClass();
            MavlinkCommandsSendObj.SerialWorkerRef = SerialWorkerObj;

            string serial = SerialWorkerObj.settings_holder.GetSetting("SERIAL_SETTINGS", "serial");
            if (comboBox_ports.Items.Count == 0)
            {
                comboBox_ports.Items.Add(serial);
                comboBox_ports.SelectedItem = comboBox_ports.Items[0];//нашелся хотя бы один порт
            }

            motorControl1.SerialWorkerRef = SerialWorkerObj;
            motorControl1.MavlinkCommandsSendRef = MavlinkCommandsSendObj;

            mavlinkObj = new Mavlink();
            mavlinkObj.PacketReceived += new PacketReceivedEventHandler(ProcessRxMavlinkPacket);
            LongPacketObj.LongPacketReceived += ParseLongPacket;

            DataProcessingObj = new DataProcesingClass();
            DataRecordingObj = new DataRecordingClass();

            calibrationControl1.UpdateLastFileName += UpdateCalibLastFileName;
            calibrationControl1.UpdateFunctionParams += UpdateFunctionParams;
            calibrationControl1.SendParamsToMCU += SendCorrCoeffToMCU;
        }


        private void ProcessRxMavlinkPacket(object sender, MavlinkPacket packet)
        {
            RXPacketCnt++;
            Invoke((MethodInvoker)delegate ()
            {
                lblRXPacketCNT.Text = $"RX Packet CNT: {RXPacketCnt}";
            });

            if (packet.Message.GetType() == typeof(MavLink.Msg_device_state))
            {
                ParseDeviceState(packet.Message as MavLink.Msg_device_state);
            }
            else if (packet.Message.GetType() == typeof(MavLink.Msg_motor_state))
            {
               motorControl1.ParseMotorState(packet.Message as MavLink.Msg_motor_state);
            }
            else if (packet.Message.GetType() == typeof(MavLink.Msg_long_packet))
            {
                LongPacketObj.AddPacket(packet.Message as MavLink.Msg_long_packet);
            }

        }

        //Parsing mavlink packet
        private void ParseLongPacket(MavlinkLongPacketClass.LongPacketStruct rxPacket)
        {
            if (rxPacket.dataCode == 1) //batch data
            {
                byte[] tmpByteBuf = rxPacket.byteDataList.Cast<byte>().ToArray();
                UInt16[] capturedBuf = new UInt16[tmpByteBuf.Length / 2];
                Buffer.BlockCopy(tmpByteBuf, 0, capturedBuf, 0, tmpByteBuf.Length);

                AddTOFDataToList(capturedBuf);
                Invoke((MethodInvoker)(() =>
                {
                    ProcessTDCData();
                }));
            }
        }

        void AddTOFDataToList(UInt16[] data)
        {
            for (int i = 0; i < data.Length; i += 2)
            {
                TdcItem item = new TdcItem();
                item.Start = data[i];
                item.Width = data[i+1];
                item.StartCorrected = GetCorrectedValue(item.Start, item.Width);//bin

                if (chkSkipFirst.Checked && (i == 0))//skip first item
                    continue;

                TdcList.Add(item);
            }
        }



        void ProcessTDCData()
        {
            RedrawTable();

            var start_values = TdcList.Select(item => item.Start).ToArray();
            var width_values = TdcList.Select(item => item.Width).ToArray();

            double start_std_dev_bin = 0;
            double width_std_dev_bin = 0;
            double start_average_bin = 0;
            double width_average_bin = 0;

            start_std_dev_bin = DataProcessingObj.FindStandardDev(ref start_values);
            width_std_dev_bin = DataProcessingObj.FindStandardDev(ref width_values);

            start_average_bin = DataProcessingObj.FindAverage(ref start_values);
            width_average_bin = DataProcessingObj.FindAverage(ref width_values);

            lblResults.Text = "";
            lblResults.Text += $"Elements: {TdcList.Count} \r\n";

            lblResults.Text += $"AVR TOF: {start_average_bin:0.0} bin - {(start_average_bin * BIN_LENGTH / 1000):0.00}  m\r\n";
            lblResults.Text += $"TOF std. dev.: ±{start_std_dev_bin:0.0} bin";
            lblResults.Text += $" ±{(start_std_dev_bin * BIN_TIME):0.0} ps";
            lblResults.Text += $" : ±{(start_std_dev_bin * BIN_LENGTH):0.0} mm" + "\r\n";

            int min_max_diff_bin = TdcDoMinMaxDataAnalyse();
            lblResults.Text += TdcDoDataAnalyseStr(min_max_diff_bin);
            lblResults.Text += "\r\n";
            lblResults.Text += TdcAnalyseCorrected();
            lblResults.Text += "\r\n";

            lblResults.Text += $"AVR WIDTH: {width_average_bin:0.0} bin - ({(width_average_bin * BIN_TIME / 1000):0.0} ns)" + "\r\n";
            lblResults.Text += $"WIDTH std. dev.: ±{width_std_dev_bin:0.0} bin" + "\r\n";

            UpdateHistogram((int)start_average_bin);

            DataRecordingClass.RecordingPoint point;
            point.position_bin = start_average_bin;
            point.position_std_bin = start_std_dev_bin;
            point.position_max_min_bin = min_max_diff_bin;
            point.width_bin = width_average_bin;
            point.width_std_bin = width_std_dev_bin;
            DataRecordingObj.AddPoint(point);

            lblRecordedCount.Text = $"Recorded Count: {DataRecordingObj.GetRecordePoints()}";
        }

        void RedrawTable()
        {
            dataGridView1.Rows.Clear();

            if (TdcList.Count < 2)
                return;

            for (int i = 0; i < TdcList.Count; i++)
            {
                dataGridView1.Rows.Add();
                dataGridView1.Rows[i].Cells[0].Value = TdcList[i].Start;
                dataGridView1.Rows[i].Cells[1].Value = TdcList[i].Width;
                dataGridView1.Rows[i].Cells[2].Value = (int)TdcList[i].StartCorrected;
            }
            dataGridView1.Refresh();
        }

        string TdcAnalyseCorrected()
        {
            string result_str = "";
            var start_corrected_values = TdcList.Select(item => item.StartCorrected).ToArray();

            double start_corr_average_bin = DataProcessingObj.FindAverage(ref start_corrected_values);

            double min = start_corrected_values.Min();
            double max = start_corrected_values.Max();
            double diff = max - min;

            result_str += $"Corr. AVR TOF: {start_corr_average_bin:0.0} bin : {(start_corr_average_bin * BIN_LENGTH / 1000):0.00}  m\r\n";
            result_str += $"Corr. Max diff: {diff:0.0} bin\r\n";
            return result_str;
        }


        /// <summary>
        /// Get start values min-max difference
        /// </summary>
        /// <returns></returns>
        int TdcDoMinMaxDataAnalyse()
        {
            var start_values = TdcList.Select(item => item.Start).ToArray();

            int min = start_values.Min();
            int max = start_values.Max();
            int diff = max - min;

            return diff;
        }
        
        string TdcDoDataAnalyseStr(int diff_dist_bin)
        {
            string tmp_str = "";

            double diff_dist = diff_dist_bin * BIN_LENGTH;//mm

            tmp_str += "Max diff: " + diff_dist_bin.ToString() + " ";
            tmp_str += "( " + diff_dist.ToString() + " mm)";
            tmp_str += "\r\n";

            return tmp_str;
        }

        /// <summary>
        /// Update "Start" Histogram
        /// </summary>
        /// <param name="avrValue">Average value of "Start" values - center of Histogram</param>
        void UpdateHistogram(int avrValue)
        {
            const int histSize = 20;
            UInt16[] histogramData = new ushort[histSize];
            chart1.Series["Series1"].Points.Clear();

            chart1.ChartAreas[0].AxisX.Minimum = -histSize / 2;
            chart1.ChartAreas[0].AxisX.Maximum = histSize / 2;
            chart1.ChartAreas[0].AxisX.Interval = 2;

            for (int i = 0; i < TdcList.Count; i++)
            {
                int curValue = TdcList[i].Start;
                int curPosition = (histSize / 2 - 1) + (curValue - avrValue);
                if ((curPosition >= 0) && (curPosition < histSize))
                {
                    histogramData[curPosition]++;
                }
            }

            for (int i = 0; i < histSize; i++)
            {
                chart1.Series["Series1"].Points.AddXY(i - (histSize/2), histogramData[i]);
            }
        }

        //Parsing mavlink packet
        void ParseDeviceState(MavLink.Msg_device_state msg)
        {
            Invoke((MethodInvoker)delegate ()
            {
                lblLaserVolt.Text = $"Laser Volt: {msg.las_voltage:0.0} V";
                lblAPDVolt.Text = $"APD Volt: {msg.apd_voltage_curr:0.0} V";
                lblCompVolt.Text = $"Comp Volt: {msg.voltage_mv} mv";
                lblAPD_PWM.Text = $"APD PWM: {msg.pwm_value} steps";

                lblRawTOFValue.Text = $"Raw TOF:  {msg.raw_tof_value} bin";
                lblRawTOFWidth.Text = $"Raw TOF width:  {msg.raw_tof_width_value} bin";

                lblAPD_TargetVoltage.Text = $"APD Targ. Volt: {msg.apd_voltage_targ:0.0} V";
                lblTestDistance.Text = $"Distance: {((float)msg.distance / 1000):0.00} m";

                lblTDCBinLength.Text = $"BIN Length, mm: {msg.tdc_bin_length:0.0}";

                lblStateMask.Text = $"State Mask: 0x{msg.state:X}";

                if (msg.pwm_state != 0)
                    lblAPDVoltFB.Text = "APD Volt. Feedback: Auto";
                else
                    lblAPDVoltFB.Text = "APD Volt. Feedback: Manual";

                if (numFieldsNeedUpdate)
                {
                    numAPD_PWM.Value = (decimal)msg.pwm_value;
                    numCompVolt.Value = (decimal)msg.voltage_mv;
                    numLaserVolt.Value = (decimal)msg.las_voltage;
                    numAPD_TargVoltage.Value = (decimal)msg.apd_voltage_targ;
                    numFieldsNeedUpdate = false;
                }

                DeviceStateBitField = msg.state;
            });
        }

        private void SerialFailSignalFunction(bool obj)
        {
        }

        private void SerialPortReceivedHandler(byte[] received_data)
        {
            mavlinkObj.ParseBytes(received_data);
        }

        private void btnOpen_Click(object sender, EventArgs e)
        {
            // If we have opened port - just close it and make necessary things
            if (SerialWorkerObj.ConnectionState == true)
            {
                SerialWorkerObj.ClosePort();

                btnOpen.Text = "Open";
                // Exit
                return;
            }

            // Try to open selected COM port
            string port_name = SerialWorkerObj.GetSerialName(comboBox_ports.Text);
            int result = SerialWorkerObj.OpenSerialPort(port_name, UART_BAUD);
            if (result == 1)
            {
                btnOpen.Text = "Close";
            }
        }

        void UpdatePortList()
        {
            comboBox_ports.Items.Clear();
            List<String> portNames = SerialWorkerObj.GetSerialPortInfo();
            foreach (string s in portNames)
            {
                comboBox_ports.Items.Add(s);
            }

            if (portNames.Count == 0)
            {
                MessageBox.Show("No serial ports in system!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            else
            {
                comboBox_ports.SelectedItem = comboBox_ports.Items[0];//нашелся хотя бы один порт
            }
        }

        void RunBatchMeasurement(int size)
        {
            TdcList.Clear();
            MavlinkCommandsSendObj.SendRunBatchMeasurement(size);
        }

        //callback from CalibrationControl
        void UpdateCalibLastFileName()
        {
            calibrationControl1.CalibLastFileName = DataRecordingObj.LastFileName;
        }

        //callback from CalibrationControl
        void UpdateFunctionParams(CalibrationControl.FunctionParamsStruct funcParams)
        {
            functParamsMainForm = funcParams;
        }

        //callback from CalibrationControl
        void SendCorrCoeffToMCU(CalibrationControl.FunctionParamsStruct funcParams)
        {
            MavlinkCommandsSendObj.SendWidthCoeff((float)funcParams.a, (float)funcParams.b);
        }

        // GUI <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

        private void comboBox_ports_DropDown(object sender, EventArgs e)
        {
            UpdatePortList();
        }

        //Request device state
        private void btnStateRequest_Click(object sender, EventArgs e)
        {
            numFieldsNeedUpdate = true;
            MavlinkCommandsSendObj.DeviceStateRequest();
        }

        private void chkAutoRequests_CheckedChanged(object sender, EventArgs e)
        {
            timer_req.Enabled = chkAutoRequests.Checked;
        }

        private void timer_req_Tick(object sender, EventArgs e)
        {
            MavlinkCommandsSendObj.DeviceStateRequest();
        }

        private void btnSetLaserVolt_Click(object sender, EventArgs e)
        {
            float voltage = (float)numLaserVolt.Value;
            MavlinkCommandsSendObj.SetLaserVoltage(voltage);
        }

        //set apd manual voltage
        private void btnSetAPD_PWM_Click(object sender, EventArgs e)
        {
            short apdPwmValue = (short)numAPD_PWM.Value;
            MavlinkCommandsSendObj.SetAPD_PWM(apdPwmValue);
        }


        //set auto feedback apd voltage
        private void btnSetAPD_TargVoltage_Click(object sender, EventArgs e)
        {
            float ApdTargVoltage = (float)numAPD_TargVoltage.Value;
            MavlinkCommandsSendObj.SetAPD_TargetVoltage(ApdTargVoltage);
        }

        private void btnSetCompVolt_Click(object sender, EventArgs e)
        {
            ushort voltage_mv = (ushort)numCompVolt.Value;
            MavlinkCommandsSendObj.SetComparatorThreshold(voltage_mv);
        }

        private void btnSetBinLength_Click(object sender, EventArgs e)
        {
            float newTDCBinLength = (float)nudBinLength.Value;
            MavlinkCommandsSendObj.SetTDCBinLength(newTDCBinLength);
        }

        private void btnSetRefDistance_Click(object sender, EventArgs e)
        {
            ushort refDistanceMm = (ushort)numRefDistance.Value;
            MavlinkCommandsSendObj.SetReferenceDistance(refDistanceMm);
        }

        private void btnSaveToFlash_Click(object sender, EventArgs e)
        {
            MavlinkCommandsSendObj.SendDeviceCommandSaveToFlash();
        }

        private void btnResetMCU_Click(object sender, EventArgs e)
        {
            MavlinkCommandsSendObj.SendDeviceCommandReset();
        }

        private void btnRunBatch_Click(object sender, EventArgs e)
        {
            RunBatchMeasurement(100);
        }

        private void chkAutoBatch_CheckedChanged(object sender, EventArgs e)
        {
            timer_batch.Enabled = chkAutoBatch.Checked;
        }

        private void timer_batch_Tick(object sender, EventArgs e)
        {
            RunBatchMeasurement(100);
        }

        private void btnStartRecording_Click(object sender, EventArgs e)
        {
            DataRecordingObj.StartRecording();
        }

        private void btnStopRecording_Click(object sender, EventArgs e)
        {
            DataRecordingObj.StopRecording();
            lblRecFileName.Text = $"File Name: " + DataRecordingObj.LastFileName;
        }

        double GetCorrectedValue(double start, double width)
        {
            if (functParamsMainForm.a == 0)
                return -1;

            double compensation = Math.Exp((functParamsMainForm.a - width) / functParamsMainForm.b);
            return (start - compensation);
        }

        private void tabControl1_SelectedIndexChanged(object sender, EventArgs e)
        {
            chkAutoBatch.Checked = false;
            chkAutoRequests.Checked = false;
        }

        private void btnStateInfo_Click(object sender, EventArgs e)
        {
            string res = "";
            if ((DeviceStateBitField & 1) != 0)
                res += "Bit 0: Bad communication with TDC after init\r\n";
            if ((DeviceStateBitField & 2) != 0)
                res += "Bit 1: No return signal was found\r\n";
            if ((DeviceStateBitField & 4) != 0)
                res += "Bit 2: Wrong hits number from laser comparator\r\n";
            if ((DeviceStateBitField & 8) != 0)
            {
                res += "Bit 3: Wrong number of encoder events.\r\n";
                res += "       Encoder is dirty or wrong installed\r\n";
            }
            if ((DeviceStateBitField & 16) != 0)
                res += "Bit 4: Mirror is stopped or encoder is not working\r\n";
            if ((DeviceStateBitField & 32) != 0)
                res += "Bit 5: Mirror speed is too low or too high\r\n";
            if ((DeviceStateBitField & 64) != 0)
                res += "Bit 6: No calibration values are set\r\n";

            if (DeviceStateBitField == 0)
                res = "No data!";

            MessageBox.Show(res, "State Bit Field");
        }
    }
}
