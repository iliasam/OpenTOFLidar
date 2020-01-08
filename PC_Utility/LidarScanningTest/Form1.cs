using MavLink;
using System;
using System.Collections.Generic;
using System.Data;
using System.Linq;
using System.Windows.Forms;

namespace LidarScanningTest1
{
    public struct RadarPoint
    {
        public double x;
        public double y;
        public double dist;
        public bool corr;
        public bool black;
        public bool NotVisible;
    }

    public partial class Form1 : Form
    {
        const int UART_BAUD = 500000;
        const int RADAR_ROTATION_DEG = 180;

        struct ScanPoint
        {
            public int RawValue;

            public double RealAngleDeg;

            public double DistM;//meters
        }


        SerialWorkerClass2 SerialWorker;
        Mavlink MavlinkObj;
        MavlinkLongPacketClass LongPacketObj = new MavlinkLongPacketClass();
        DataAnalyseClass DataAnalyseObj = new DataAnalyseClass();

        public IniParser SettingsHolder;//Used for storing settings

        /// <summary>
        /// Rotation period in ms
        /// </summary>
        int RotationPeriod = 0;
        DateTime PrevScanTime = DateTime.Now;

        int RXPacketCnt = 0;

        ScanPoint[] ScanPoints = new ScanPoint[360];
        RadarPoint[] RadarPoints = new RadarPoint[400];

        /// <summary>
        /// Additional rotation, deg
        /// </summary>
        double CurrAngularCorrection = 0.0;//degrees
        int CurrStartAngle = 50;
        int CurrStopAngle = (360 - 50);

        public Form1()
        {
            InitializeComponent();

            cmbPortList.Items.Clear();

            SerialWorker = new SerialWorkerClass2(Application.StartupPath + @"\config.ini");
            SerialWorker.AnswerReceived = SerialPortReceivedHandler;
            SerialWorker.SerialFailSignal = SerialFailSignal_function;

            MavlinkObj = new Mavlink();
            MavlinkObj.PacketReceived += new PacketReceivedEventHandler(ProcessRxMavlinkPacket);
            LongPacketObj.LongPacketReceived += ParseLongPacket;

            string settingsFilePath = Application.StartupPath + @"\config.ini";
            SettingsHolder = new IniParser(settingsFilePath);

            string serialName = SettingsHolder.GetSetting("SERIAL_SETTINGS", "serial");
            if (cmbPortList.Items.Count == 0)
            {
                cmbPortList.Items.Add(serialName);
                cmbPortList.SelectedItem = cmbPortList.Items[0];
            }

            //Load calibration coefficients
            string angCorrStr = SettingsHolder.GetSetting("LIDAR_SETTINGS", "angular_corr");
            CurrAngularCorrection = Convert.ToDouble(angCorrStr, System.Globalization.CultureInfo.InvariantCulture);
            numAngCorrection.Value = (decimal)CurrAngularCorrection;

            string startAngleStr = SettingsHolder.GetSetting("LIDAR_SETTINGS", "start_angle");
            CurrStartAngle = Convert.ToInt32(startAngleStr, System.Globalization.CultureInfo.InvariantCulture);
            numStartAngle.Value = CurrStartAngle;

            string stopAngleStr = SettingsHolder.GetSetting("LIDAR_SETTINGS", "stop_angle");
            CurrStopAngle = Convert.ToInt32(stopAngleStr, System.Globalization.CultureInfo.InvariantCulture);
            numStopAngle.Value = CurrStopAngle;

            radarPlotComponent1.SetRadarRotation(RADAR_ROTATION_DEG);

            timer1.Enabled = true;
        }

        private void SerialFailSignal_function(bool obj)
        {
        }

        // Callback from "Serial Worker"
        private void SerialPortReceivedHandler(byte[] received_data)
        {
            MavlinkObj.ParseBytes(received_data);
        }

        private void ProcessRxMavlinkPacket(object sender, MavlinkPacket packet)
        {
            RXPacketCnt++;
            Invoke((MethodInvoker)delegate ()
            {
                lblPacketCnt.Text = $"RX Packet CNT: {RXPacketCnt}";
            });

            if (packet.Message.GetType() == typeof(MavLink.Msg_long_packet))
            {
                LongPacketObj.AddPacket(packet.Message as MavLink.Msg_long_packet);
            }
            else if (packet.Message.GetType() == typeof(MavLink.Msg_device_state))
            {
                ParseDeviceState(packet.Message as MavLink.Msg_device_state);
            }
        }

        private void ParseLongPacket(MavlinkLongPacketClass.LongPacketStruct rxPacket)
        {
            if (rxPacket.dataCode == 2) //scan data
            {
                byte[] tmp_byte_buf = rxPacket.byteDataList.Cast<byte>().ToArray();
                UInt16[] captured_buf = new UInt16[tmp_byte_buf.Length / 2];
                Buffer.BlockCopy(tmp_byte_buf, 0, captured_buf, 0, tmp_byte_buf.Length);

                Invoke((MethodInvoker)(() =>
                {
                    ProcessRxData(captured_buf);
                }));
            }
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            CurrAngularCorrection = (double)numAngCorrection.Value;
            CurrStartAngle = (int)numStartAngle.Value;
            CurrStopAngle = (int)numStopAngle.Value;

            if (chkSendStateRequests.Checked)
                DeviceStateRequest();

        }

        /// <summary>
        /// Process packet received from the Lidar
        /// </summary>
        /// <param name="data_array"></param>
        void ProcessRxData(UInt16[] data_array)
        {
            for (int i = 0; i < 360; i++)
            {
                ScanPoints[i].RealAngleDeg = i;
                ScanPoints[i].RawValue = data_array[i];
                if ((ScanPoints[i].RealAngleDeg < CurrStartAngle) || 
                    (ScanPoints[i].RealAngleDeg > CurrStopAngle))
                    ScanPoints[i].DistM = 0.0;
                else
                    ScanPoints[i].DistM = (double)data_array[i] / 1000.0;
            }

            CalculateRadarData();
            radarPlotComponent1.DrawRadar(RadarPoints, (int)CurrAngularCorrection);

            RotationPeriod = (int)(DateTime.Now - PrevScanTime).TotalMilliseconds;
            PrevScanTime = DateTime.Now;
            double freq = Math.Round(1.0 / (double)(RotationPeriod / 1000.0), 1);//ms -> sec
            lblScanPeriod.Text = "Scan Perod: " + RotationPeriod.ToString() + " ms";
            lblScanFreq.Text = "Scan Freq: " + freq.ToString() + " Hz";

            AnalysePointerData();
        }

        // Simple statisctilac analyse of point at given direction
        void AnalysePointerData()
        {
            int pointer_angle = radarPlotComponent1.GetPointerAngle();

            int raw_val = ScanPoints[pointer_angle].RawValue;
            double dist = ScanPoints[pointer_angle].DistM;

            DataAnalyseObj.AddDataPoint(dist);

            lblRawValue.Text = "Raw Value: " + raw_val.ToString();
            lblDistValue.Text = "Distance: " + dist.ToString("0.00") + " m";

            lblAVRValue.Text = "Average: " + DataAnalyseObj.average.ToString("0.00") + " m";

            lblMaxMIn.Text = "MaxMin: " + DataAnalyseObj.min_max.ToString("0.00") + " m";
        }

        void CalculateRadarData()
        {
            int i;
            double x = 0;
            double y = 0;
            double angle_rad = 0;
            double dist;
            int offset1_deg;

            // Radar rotation
            double ang5 = 90 + RADAR_ROTATION_DEG;

            for (i = 0; i < 360; i++)
            {
                dist = ScanPoints[i].DistM;
                offset1_deg = i;//angle
                if (offset1_deg > 359)
                    offset1_deg = offset1_deg - 360;

                angle_rad = (double)(offset1_deg + CurrAngularCorrection + ang5) / 180.0 * (Math.PI);

                RadarPoints[offset1_deg].dist = dist;
                RadarPoints[offset1_deg].x = (Math.Cos(angle_rad) * dist);
                RadarPoints[offset1_deg].y = (Math.Sin(angle_rad) * dist);
                if (RadarPoints[offset1_deg].dist < 0.03)
                    RadarPoints[offset1_deg].NotVisible = true;
                else
                    RadarPoints[offset1_deg].NotVisible = false;
            }
        }


        private void btnOpenClose_Click(object sender, EventArgs e)
        {
            // If we have opened port - just close it and make necessary things
            if (SerialWorker.ConnectionState == true)
            {
                SerialWorker.ClosePort();

                btnOpenClose.Text = "Open";
                // Exit
                return;
            }

            // Try to open selected COM port
            string port_name = SerialWorker.GetSerialName(cmbPortList.Text);
            int result = SerialWorker.OpenSerialPort(port_name, UART_BAUD);
            if (result == 1)
            {
                btnOpenClose.Text = "Close";
            }
        }

        void UpdatePortList()
        {
            cmbPortList.Items.Clear();
            List<String> portNames = SerialWorker.GetSerialPortInfo();
            foreach (string s in portNames)
            {
                cmbPortList.Items.Add(s);
            }

            if (portNames.Count == 0)
            {
                MessageBox.Show("No serial ports in system!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            else
            {
                cmbPortList.SelectedItem = cmbPortList.Items[0];//нашелся хотя бы один порт
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
                lblStateMask.Text = $"State Mask: 0x{msg.state:X}";

                if (msg.pwm_state != 0)
                    lblAPDVoltFB.Text = "APD Volt. FB: Auto";
                else
                    lblAPDVoltFB.Text = "APD Volt. FB: Manual";
            });
        }

        public void DeviceStateRequest()
        {
            MavLink.Msg_data_request mav_msg = new MavLink.Msg_data_request();

            mav_msg.data_type = (byte)MavLink.DATA_REQUEST.DATA_REQUEST_DEVICE_STATE;

            var mvp = new MavlinkPacket
            {
                ComponentId = 1,
                SystemId = 2,//PC
                Message = mav_msg
            };
            SendMavlinkPaket(mvp);
        }

        void SendMavlinkPaket(MavlinkPacket packet)
        {
            byte[] dataToSend = MavlinkObj.Send(packet);
            SerialWorker.send_bin_data_to_serial(dataToSend);
        }

        // GUI *********************************************************

        private void btnSaveCoeff_Click(object sender, EventArgs e)
        {
            string ang_corr_str = CurrAngularCorrection.ToString(System.Globalization.CultureInfo.InvariantCulture);
            SettingsHolder.AddSetting("LIDAR_SETTINGS", "angular_corr", ang_corr_str);

            string start_angle_str = CurrStartAngle.ToString(System.Globalization.CultureInfo.InvariantCulture);
            SettingsHolder.AddSetting("LIDAR_SETTINGS", "start_angle", start_angle_str);

            string stop_angle_str = CurrStopAngle.ToString(System.Globalization.CultureInfo.InvariantCulture);
            SettingsHolder.AddSetting("LIDAR_SETTINGS", "stop_angle", stop_angle_str);

            SettingsHolder.SaveSettings();
        }

        private void numericUpDown1_ValueChanged(object sender, EventArgs e)
        {
            DataAnalyseObj.SetLength((int)numericUpDown1.Value);
        }

        private void cmbPortList_DropDown(object sender, EventArgs e)
        {
            UpdatePortList();
        }

        private void numStartAngle_ValueChanged(object sender, EventArgs e)
        {
            radarPlotComponent1.UpdateStartStopLines(CurrStartAngle, CurrStopAngle);
        }

        private void numStopAngle_ValueChanged(object sender, EventArgs e)
        {
            radarPlotComponent1.UpdateStartStopLines(CurrStartAngle, CurrStopAngle);
        }
    }
}
