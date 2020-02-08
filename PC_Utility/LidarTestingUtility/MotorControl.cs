using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace TDC_Testing_v1
{
    public partial class MotorControl : UserControl
    {
        public SerialWorkerClass2 SerialWorkerRef;//reference object
        public MavlinkCommandsSendClass MavlinkCommandsSendRef;

        bool numFieldsNeedUpdate = true;

        public MotorControl()
        {
            InitializeComponent();
        }

        private void chkMotorAutoRequests_CheckedChanged(object sender, EventArgs e)
        {
            timerMotorRequests.Enabled = chkMotorAutoRequests.Checked;
        }

        private void timerMotorRequests_Tick(object sender, EventArgs e)
        {
            MavlinkCommandsSendRef?.MotorStateRequest();
        }

        //Parsing mavlink packet
        public void ParseMotorState(MavLink.Msg_motor_state msg)
        {
            Invoke((MethodInvoker)delegate ()
            {
                lblCurMotorSpeed.Text = $"Motor Speed: {msg.motor_speed:0.0} RPS";
                lblCurrentMotorDuty.Text = $"Motor PWM Duty: {msg.pwm_duty}";
                lblMotorTargeSpeed.Text = $"Motor Target Speed: {msg.setted_motor_speed:0.0} RPS";
                lblMotorManualPWM.Text = $"Motor Manual PWM: {msg.setted_pwm_duty}";
                lblState.Text = $"State: 0x{msg.state:X}";

                /*


                if (msg.pwm_state != 0)
                    lblAPDVoltFB.Text = "APD Volt. Feedback: Auto";
                else
                    lblAPDVoltFB.Text = "APD Volt. Feedback: Manual";

                */
                if (numFieldsNeedUpdate)
                {
                    if (msg.setted_pwm_duty < numMotorDuty.Maximum)
                        numMotorDuty.Value = (decimal)msg.setted_pwm_duty;
                    numMotorTargetSpeed.Value = (decimal)msg.setted_motor_speed;
                    numFieldsNeedUpdate = false;
                }

            });
        }

        private void btnSetMotorDuty_Click(object sender, EventArgs e)
        {
            ushort pwm_duty = (ushort)numMotorDuty.Value;
            MavlinkCommandsSendRef?.SetMotorPwmDuty(pwm_duty);
        }

        private void btnSetMotorTargetSpeed_Click(object sender, EventArgs e)
        {
            float speed = (float)numMotorTargetSpeed.Value;
            MavlinkCommandsSendRef?.SetMotorSpeed(speed);
        }

        private void btnResetMCU_Click(object sender, EventArgs e)
        {
            MavlinkCommandsSendRef?.SendDeviceCommandReset();
        }
    }
}
