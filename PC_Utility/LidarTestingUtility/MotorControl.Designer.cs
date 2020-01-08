namespace TDC_Testing_v1
{
    partial class MotorControl
    {
        /// <summary> 
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary> 
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Component Designer generated code

        /// <summary> 
        /// Required method for Designer support - do not modify 
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.lblCurrentMotorDuty = new System.Windows.Forms.Label();
            this.lblCurMotorSpeed = new System.Windows.Forms.Label();
            this.chkMotorAutoRequests = new System.Windows.Forms.CheckBox();
            this.timerMotorRequests = new System.Windows.Forms.Timer(this.components);
            this.btnSetMotorDuty = new System.Windows.Forms.Button();
            this.numMotorDuty = new System.Windows.Forms.NumericUpDown();
            this.btnSetMotorTargetSpeed = new System.Windows.Forms.Button();
            this.numMotorTargetSpeed = new System.Windows.Forms.NumericUpDown();
            this.lblMotorTargeSpeed = new System.Windows.Forms.Label();
            this.lblMotorManualPWM = new System.Windows.Forms.Label();
            this.lblState = new System.Windows.Forms.Label();
            this.btnResetMCU = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.numMotorDuty)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numMotorTargetSpeed)).BeginInit();
            this.SuspendLayout();
            // 
            // lblCurrentMotorDuty
            // 
            this.lblCurrentMotorDuty.AutoSize = true;
            this.lblCurrentMotorDuty.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.lblCurrentMotorDuty.Location = new System.Drawing.Point(16, 119);
            this.lblCurrentMotorDuty.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.lblCurrentMotorDuty.Name = "lblCurrentMotorDuty";
            this.lblCurrentMotorDuty.Size = new System.Drawing.Size(163, 20);
            this.lblCurrentMotorDuty.TabIndex = 2;
            this.lblCurrentMotorDuty.Text = "Motor PWM Duty: N/A";
            // 
            // lblCurMotorSpeed
            // 
            this.lblCurMotorSpeed.AutoSize = true;
            this.lblCurMotorSpeed.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.lblCurMotorSpeed.Location = new System.Drawing.Point(16, 89);
            this.lblCurMotorSpeed.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.lblCurMotorSpeed.Name = "lblCurMotorSpeed";
            this.lblCurMotorSpeed.Size = new System.Drawing.Size(135, 20);
            this.lblCurMotorSpeed.TabIndex = 3;
            this.lblCurMotorSpeed.Text = "Motor Speed: N/A";
            // 
            // chkMotorAutoRequests
            // 
            this.chkMotorAutoRequests.AutoSize = true;
            this.chkMotorAutoRequests.Location = new System.Drawing.Point(455, 22);
            this.chkMotorAutoRequests.Name = "chkMotorAutoRequests";
            this.chkMotorAutoRequests.Size = new System.Drawing.Size(96, 17);
            this.chkMotorAutoRequests.TabIndex = 4;
            this.chkMotorAutoRequests.Text = "Auto Requests";
            this.chkMotorAutoRequests.UseVisualStyleBackColor = true;
            this.chkMotorAutoRequests.CheckedChanged += new System.EventHandler(this.chkMotorAutoRequests_CheckedChanged);
            // 
            // timerMotorRequests
            // 
            this.timerMotorRequests.Interval = 200;
            this.timerMotorRequests.Tick += new System.EventHandler(this.timerMotorRequests_Tick);
            // 
            // btnSetMotorDuty
            // 
            this.btnSetMotorDuty.Location = new System.Drawing.Point(319, 23);
            this.btnSetMotorDuty.Margin = new System.Windows.Forms.Padding(2);
            this.btnSetMotorDuty.Name = "btnSetMotorDuty";
            this.btnSetMotorDuty.Size = new System.Drawing.Size(44, 24);
            this.btnSetMotorDuty.TabIndex = 24;
            this.btnSetMotorDuty.Text = "SET";
            this.btnSetMotorDuty.UseVisualStyleBackColor = true;
            this.btnSetMotorDuty.Click += new System.EventHandler(this.btnSetMotorDuty_Click);
            // 
            // numMotorDuty
            // 
            this.numMotorDuty.Location = new System.Drawing.Point(243, 25);
            this.numMotorDuty.Margin = new System.Windows.Forms.Padding(2);
            this.numMotorDuty.Maximum = new decimal(new int[] {
            65000,
            0,
            0,
            0});
            this.numMotorDuty.Name = "numMotorDuty";
            this.numMotorDuty.Size = new System.Drawing.Size(71, 20);
            this.numMotorDuty.TabIndex = 23;
            this.numMotorDuty.Value = new decimal(new int[] {
            10,
            0,
            0,
            0});
            // 
            // btnSetMotorTargetSpeed
            // 
            this.btnSetMotorTargetSpeed.Location = new System.Drawing.Point(319, 52);
            this.btnSetMotorTargetSpeed.Margin = new System.Windows.Forms.Padding(2);
            this.btnSetMotorTargetSpeed.Name = "btnSetMotorTargetSpeed";
            this.btnSetMotorTargetSpeed.Size = new System.Drawing.Size(44, 24);
            this.btnSetMotorTargetSpeed.TabIndex = 27;
            this.btnSetMotorTargetSpeed.Text = "SET";
            this.btnSetMotorTargetSpeed.UseVisualStyleBackColor = true;
            this.btnSetMotorTargetSpeed.Click += new System.EventHandler(this.btnSetMotorTargetSpeed_Click);
            // 
            // numMotorTargetSpeed
            // 
            this.numMotorTargetSpeed.Location = new System.Drawing.Point(243, 54);
            this.numMotorTargetSpeed.Margin = new System.Windows.Forms.Padding(2);
            this.numMotorTargetSpeed.Maximum = new decimal(new int[] {
            30,
            0,
            0,
            0});
            this.numMotorTargetSpeed.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.numMotorTargetSpeed.Name = "numMotorTargetSpeed";
            this.numMotorTargetSpeed.Size = new System.Drawing.Size(71, 20);
            this.numMotorTargetSpeed.TabIndex = 26;
            this.numMotorTargetSpeed.Value = new decimal(new int[] {
            15,
            0,
            0,
            0});
            // 
            // lblMotorTargeSpeed
            // 
            this.lblMotorTargeSpeed.AutoSize = true;
            this.lblMotorTargeSpeed.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.lblMotorTargeSpeed.Location = new System.Drawing.Point(16, 54);
            this.lblMotorTargeSpeed.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.lblMotorTargeSpeed.Name = "lblMotorTargeSpeed";
            this.lblMotorTargeSpeed.Size = new System.Drawing.Size(185, 20);
            this.lblMotorTargeSpeed.TabIndex = 25;
            this.lblMotorTargeSpeed.Text = "Motor Target Speed: N/A";
            // 
            // lblMotorManualPWM
            // 
            this.lblMotorManualPWM.AutoSize = true;
            this.lblMotorManualPWM.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.lblMotorManualPWM.Location = new System.Drawing.Point(16, 26);
            this.lblMotorManualPWM.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.lblMotorManualPWM.Name = "lblMotorManualPWM";
            this.lblMotorManualPWM.Size = new System.Drawing.Size(182, 20);
            this.lblMotorManualPWM.TabIndex = 28;
            this.lblMotorManualPWM.Text = "Motor Manual PWM: N/A";
            // 
            // lblState
            // 
            this.lblState.AutoSize = true;
            this.lblState.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.lblState.Location = new System.Drawing.Point(16, 148);
            this.lblState.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.lblState.Name = "lblState";
            this.lblState.Size = new System.Drawing.Size(82, 20);
            this.lblState.TabIndex = 29;
            this.lblState.Text = "State: N/A";
            // 
            // btnResetMCU
            // 
            this.btnResetMCU.BackColor = System.Drawing.Color.Yellow;
            this.btnResetMCU.Location = new System.Drawing.Point(453, 52);
            this.btnResetMCU.Margin = new System.Windows.Forms.Padding(2);
            this.btnResetMCU.Name = "btnResetMCU";
            this.btnResetMCU.Size = new System.Drawing.Size(98, 24);
            this.btnResetMCU.TabIndex = 30;
            this.btnResetMCU.Text = "Reset MCU";
            this.btnResetMCU.UseVisualStyleBackColor = false;
            this.btnResetMCU.Click += new System.EventHandler(this.btnResetMCU_Click);
            // 
            // MotorControl
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.btnResetMCU);
            this.Controls.Add(this.lblState);
            this.Controls.Add(this.lblMotorManualPWM);
            this.Controls.Add(this.btnSetMotorTargetSpeed);
            this.Controls.Add(this.numMotorTargetSpeed);
            this.Controls.Add(this.lblMotorTargeSpeed);
            this.Controls.Add(this.btnSetMotorDuty);
            this.Controls.Add(this.numMotorDuty);
            this.Controls.Add(this.chkMotorAutoRequests);
            this.Controls.Add(this.lblCurMotorSpeed);
            this.Controls.Add(this.lblCurrentMotorDuty);
            this.Name = "MotorControl";
            this.Size = new System.Drawing.Size(572, 322);
            ((System.ComponentModel.ISupportInitialize)(this.numMotorDuty)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numMotorTargetSpeed)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label lblCurrentMotorDuty;
        private System.Windows.Forms.Label lblCurMotorSpeed;
        private System.Windows.Forms.CheckBox chkMotorAutoRequests;
        private System.Windows.Forms.Timer timerMotorRequests;
        private System.Windows.Forms.Button btnSetMotorDuty;
        private System.Windows.Forms.NumericUpDown numMotorDuty;
        private System.Windows.Forms.Button btnSetMotorTargetSpeed;
        private System.Windows.Forms.NumericUpDown numMotorTargetSpeed;
        private System.Windows.Forms.Label lblMotorTargeSpeed;
        private System.Windows.Forms.Label lblMotorManualPWM;
        private System.Windows.Forms.Label lblState;
        private System.Windows.Forms.Button btnResetMCU;
    }
}
