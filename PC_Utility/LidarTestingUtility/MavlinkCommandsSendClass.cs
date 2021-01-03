using MavLink;

namespace TDC_Testing_v1
{
    public class MavlinkCommandsSendClass
    {
        Mavlink MavlinkObjSender;
        public SerialWorkerClass2 SerialWorkerRef;//external object

        public MavlinkCommandsSendClass()
        {
            MavlinkObjSender = new Mavlink();
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

        public void MotorStateRequest()
        {
            MavLink.Msg_data_request mav_msg = new MavLink.Msg_data_request();

            mav_msg.data_type = (byte)MavLink.DATA_REQUEST.DATA_REQUEST_MOTOR_STATE;

            var mvp = new MavlinkPacket
            {
                ComponentId = 1,
                SystemId = 2,//PC
                Message = mav_msg
            };
            SendMavlinkPaket(mvp);
        }

        public void SendDeviceCommandSaveToFlash()
        {
            MavLink.Msg_device_command mav_msg = new MavLink.Msg_device_command();

            mav_msg.cmd = (byte)MavLink.DEVICE_COMMAND_TYPE.CMD_SAVE_TO_FLASH;

            var mvp = new MavlinkPacket
            {
                ComponentId = 1,
                SystemId = 2,//PC
                Message = mav_msg
            };
            SendMavlinkPaket(mvp);
        }

        public void SendDeviceCommandReset()
        {
            MavLink.Msg_device_command mav_msg = new MavLink.Msg_device_command();

            mav_msg.cmd = (byte)MavLink.DEVICE_COMMAND_TYPE.CMD_MCU_REBOOT;

            var mvp = new MavlinkPacket
            {
                ComponentId = 1,
                SystemId = 2,//PC
                Message = mav_msg
            };
            SendMavlinkPaket(mvp);
        }

        public void SetLaserVoltage(float voltage)
        {
            MavLink.Msg_set_laser_voltage mav_msg = new MavLink.Msg_set_laser_voltage();

            mav_msg.voltage = voltage;

            var mvp = new MavlinkPacket
            {
                ComponentId = 1,
                SystemId = 2,//PC
                Message = mav_msg
            };
            SendMavlinkPaket(mvp);
        }

        public void SetAPD_PWM(short value)
        {
            MavLink.Msg_set_apd_voltage mav_msg = new MavLink.Msg_set_apd_voltage();

            mav_msg.pwm_value = value;
            mav_msg.voltage = -1.0f;

            var mvp = new MavlinkPacket
            {
                ComponentId = 1,
                SystemId = 2,//PC
                Message = mav_msg
            };
            SendMavlinkPaket(mvp);
        }

        public void SetReferenceDistance(ushort ref_dist_mm)
        {
            MavLink.Msg_set_ref_offset mav_msg = new MavLink.Msg_set_ref_offset();

            mav_msg.dist_value = ref_dist_mm;

            var mvp = new MavlinkPacket
            {
                ComponentId = 1,
                SystemId = 2,//PC
                Message = mav_msg
            };
            SendMavlinkPaket(mvp);
        }

        public void SetAPD_TargetVoltage(float voltage_v)
        {
            MavLink.Msg_set_apd_voltage mav_msg = new MavLink.Msg_set_apd_voltage();

            mav_msg.pwm_value = -1;//do not change
            mav_msg.voltage = voltage_v;

            var mvp = new MavlinkPacket
            {
                ComponentId = 1,
                SystemId = 2,//PC
                Message = mav_msg
            };
            SendMavlinkPaket(mvp);
        }

        public void SetComparatorThreshold(int voltage_mv)
        {
            MavLink.Msg_set_comp_threshold mav_msg = new MavLink.Msg_set_comp_threshold();

            mav_msg.voltage_mv = (ushort)voltage_mv;

            var mvp = new MavlinkPacket
            {
                ComponentId = 1,
                SystemId = 2,//PC
                Message = mav_msg
            };
            SendMavlinkPaket(mvp);
        }

        public void SetTDCBinLength(float binLengthMM)
        {
            MavLink.Msg_set_bin_length mav_msg = new MavLink.Msg_set_bin_length();

            mav_msg.tdc_bin_length = binLengthMM;

            var mvp = new MavlinkPacket
            {
                ComponentId = 1,
                SystemId = 2,//PC
                Message = mav_msg
            };
            SendMavlinkPaket(mvp);
        }

        public void SendRunBatchMeasurement(int size)
        {
            MavLink.Msg_start_batch_measurement mav_msg = new MavLink.Msg_start_batch_measurement();

            mav_msg.length = (ushort)size;

            var mvp = new MavlinkPacket
            {
                ComponentId = 1,
                SystemId = 2,//PC
                Message = mav_msg
            };
            SendMavlinkPaket(mvp);
        }

        public void SendWidthCoeff(float coeffA, float coeffB)
        {
            MavLink.Msg_set_width_corr_coeff mav_msg = new MavLink.Msg_set_width_corr_coeff();

            mav_msg.coeff_a = coeffA;
            mav_msg.coeff_b = coeffB;

            var mvp = new MavlinkPacket
            {
                ComponentId = 1,
                SystemId = 2,//PC
                Message = mav_msg
            };
            SendMavlinkPaket(mvp);
        }

        public void SetMotorPwmDuty(int newDuty)
        {
            MavLink.Msg_set_motor_duty mav_msg = new MavLink.Msg_set_motor_duty();

            mav_msg.duty = (ushort)newDuty;

            var mvp = new MavlinkPacket
            {
                ComponentId = 1,
                SystemId = 2,//PC
                Message = mav_msg
            };
            SendMavlinkPaket(mvp);
        }

        public void SetMotorSpeed(float speed_rps)
        {
            MavLink.Msg_set_motor_speed mav_msg = new MavLink.Msg_set_motor_speed();

            mav_msg.speed = speed_rps;

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
            byte[] data_to_send = MavlinkObjSender.Send(packet);
            SerialWorkerRef.send_bin_data_to_serial(data_to_send);
        }
    }
}
