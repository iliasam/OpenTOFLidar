namespace TDC_Testing_v1
{
    partial class Form1
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

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.Windows.Forms.DataVisualization.Charting.ChartArea chartArea1 = new System.Windows.Forms.DataVisualization.Charting.ChartArea();
            System.Windows.Forms.DataVisualization.Charting.Series series1 = new System.Windows.Forms.DataVisualization.Charting.Series();
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.tabPageMain = new System.Windows.Forms.TabPage();
            this.chkSkipFirst = new System.Windows.Forms.CheckBox();
            this.chart1 = new System.Windows.Forms.DataVisualization.Charting.Chart();
            this.lblResults = new System.Windows.Forms.Label();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.lblRecFileName = new System.Windows.Forms.Label();
            this.lblRecordedCount = new System.Windows.Forms.Label();
            this.btnStopRecording = new System.Windows.Forms.Button();
            this.btnStartRecording = new System.Windows.Forms.Button();
            this.chkAutoBatch = new System.Windows.Forms.CheckBox();
            this.btnRunBatch = new System.Windows.Forms.Button();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.btnSetBinLength = new System.Windows.Forms.Button();
            this.nudBinLength = new System.Windows.Forms.NumericUpDown();
            this.lblTDCBinLength = new System.Windows.Forms.Label();
            this.lblStateMask = new System.Windows.Forms.Label();
            this.btnResetMCU = new System.Windows.Forms.Button();
            this.btnSetRefDistance = new System.Windows.Forms.Button();
            this.numRefDistance = new System.Windows.Forms.NumericUpDown();
            this.label1 = new System.Windows.Forms.Label();
            this.lblTestDistance = new System.Windows.Forms.Label();
            this.btnSaveToFlash = new System.Windows.Forms.Button();
            this.lblAPDVoltFB = new System.Windows.Forms.Label();
            this.btnSetAPD_TargVoltage = new System.Windows.Forms.Button();
            this.numAPD_TargVoltage = new System.Windows.Forms.NumericUpDown();
            this.lblAPD_TargetVoltage = new System.Windows.Forms.Label();
            this.btnSetCompVolt = new System.Windows.Forms.Button();
            this.btnSetAPD_PWM = new System.Windows.Forms.Button();
            this.btnSetLaserVolt = new System.Windows.Forms.Button();
            this.numCompVolt = new System.Windows.Forms.NumericUpDown();
            this.numAPD_PWM = new System.Windows.Forms.NumericUpDown();
            this.numLaserVolt = new System.Windows.Forms.NumericUpDown();
            this.chkAutoRequests = new System.Windows.Forms.CheckBox();
            this.lblRawTOFWidth = new System.Windows.Forms.Label();
            this.lblRawTOFValue = new System.Windows.Forms.Label();
            this.lblCompVolt = new System.Windows.Forms.Label();
            this.lblAPD_PWM = new System.Windows.Forms.Label();
            this.lblAPDVolt = new System.Windows.Forms.Label();
            this.lblLaserVolt = new System.Windows.Forms.Label();
            this.btnStateRequest = new System.Windows.Forms.Button();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.lblRXPacketCNT = new System.Windows.Forms.Label();
            this.btnOpen = new System.Windows.Forms.Button();
            this.comboBox_ports = new System.Windows.Forms.ComboBox();
            this.dataGridView1 = new System.Windows.Forms.DataGridView();
            this.Column1 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Column4 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Column2 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.tabPageCalibration = new System.Windows.Forms.TabPage();
            this.tabPageMotor = new System.Windows.Forms.TabPage();
            this.timer_batch = new System.Windows.Forms.Timer(this.components);
            this.timer_req = new System.Windows.Forms.Timer(this.components);
            this.btnStateInfo = new System.Windows.Forms.Button();
            this.calibrationControl1 = new TDC_Testing_v1.CalibrationControl();
            this.motorControl1 = new TDC_Testing_v1.MotorControl();
            this.tabControl1.SuspendLayout();
            this.tabPageMain.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.chart1)).BeginInit();
            this.groupBox3.SuspendLayout();
            this.groupBox2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.nudBinLength)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numRefDistance)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numAPD_TargVoltage)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numCompVolt)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numAPD_PWM)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numLaserVolt)).BeginInit();
            this.groupBox1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).BeginInit();
            this.tabPageCalibration.SuspendLayout();
            this.tabPageMotor.SuspendLayout();
            this.SuspendLayout();
            // 
            // tabControl1
            // 
            this.tabControl1.Controls.Add(this.tabPageMain);
            this.tabControl1.Controls.Add(this.tabPageCalibration);
            this.tabControl1.Controls.Add(this.tabPageMotor);
            this.tabControl1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tabControl1.Location = new System.Drawing.Point(0, 0);
            this.tabControl1.Margin = new System.Windows.Forms.Padding(2);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(1004, 541);
            this.tabControl1.TabIndex = 0;
            this.tabControl1.SelectedIndexChanged += new System.EventHandler(this.tabControl1_SelectedIndexChanged);
            // 
            // tabPageMain
            // 
            this.tabPageMain.Controls.Add(this.chkSkipFirst);
            this.tabPageMain.Controls.Add(this.chart1);
            this.tabPageMain.Controls.Add(this.lblResults);
            this.tabPageMain.Controls.Add(this.groupBox3);
            this.tabPageMain.Controls.Add(this.chkAutoBatch);
            this.tabPageMain.Controls.Add(this.btnRunBatch);
            this.tabPageMain.Controls.Add(this.groupBox2);
            this.tabPageMain.Controls.Add(this.groupBox1);
            this.tabPageMain.Controls.Add(this.dataGridView1);
            this.tabPageMain.Location = new System.Drawing.Point(4, 22);
            this.tabPageMain.Margin = new System.Windows.Forms.Padding(2);
            this.tabPageMain.Name = "tabPageMain";
            this.tabPageMain.Padding = new System.Windows.Forms.Padding(2);
            this.tabPageMain.Size = new System.Drawing.Size(996, 515);
            this.tabPageMain.TabIndex = 0;
            this.tabPageMain.Text = "Main";
            this.tabPageMain.UseVisualStyleBackColor = true;
            // 
            // chkSkipFirst
            // 
            this.chkSkipFirst.Checked = true;
            this.chkSkipFirst.CheckState = System.Windows.Forms.CheckState.Checked;
            this.chkSkipFirst.Location = new System.Drawing.Point(562, 68);
            this.chkSkipFirst.Margin = new System.Windows.Forms.Padding(2);
            this.chkSkipFirst.Name = "chkSkipFirst";
            this.chkSkipFirst.Size = new System.Drawing.Size(78, 20);
            this.chkSkipFirst.TabIndex = 18;
            this.chkSkipFirst.Text = "Skip first";
            this.chkSkipFirst.UseVisualStyleBackColor = true;
            // 
            // chart1
            // 
            this.chart1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            chartArea1.Name = "ChartArea1";
            this.chart1.ChartAreas.Add(chartArea1);
            this.chart1.Location = new System.Drawing.Point(316, 314);
            this.chart1.Margin = new System.Windows.Forms.Padding(2);
            this.chart1.Name = "chart1";
            series1.ChartArea = "ChartArea1";
            series1.Name = "Series1";
            this.chart1.Series.Add(series1);
            this.chart1.Size = new System.Drawing.Size(366, 175);
            this.chart1.TabIndex = 17;
            this.chart1.Text = "chart1";
            // 
            // lblResults
            // 
            this.lblResults.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.lblResults.BackColor = System.Drawing.SystemColors.ButtonHighlight;
            this.lblResults.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.lblResults.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.lblResults.Location = new System.Drawing.Point(315, 105);
            this.lblResults.Name = "lblResults";
            this.lblResults.Size = new System.Drawing.Size(367, 205);
            this.lblResults.TabIndex = 16;
            this.lblResults.Text = "Results";
            // 
            // groupBox3
            // 
            this.groupBox3.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.groupBox3.Controls.Add(this.lblRecFileName);
            this.groupBox3.Controls.Add(this.lblRecordedCount);
            this.groupBox3.Controls.Add(this.btnStopRecording);
            this.groupBox3.Controls.Add(this.btnStartRecording);
            this.groupBox3.Location = new System.Drawing.Point(687, 416);
            this.groupBox3.Margin = new System.Windows.Forms.Padding(2);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Padding = new System.Windows.Forms.Padding(2);
            this.groupBox3.Size = new System.Drawing.Size(297, 88);
            this.groupBox3.TabIndex = 20;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "Slow Recording";
            // 
            // lblRecFileName
            // 
            this.lblRecFileName.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.lblRecFileName.Location = new System.Drawing.Point(7, 54);
            this.lblRecFileName.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.lblRecFileName.Name = "lblRecFileName";
            this.lblRecFileName.Size = new System.Drawing.Size(284, 19);
            this.lblRecFileName.TabIndex = 16;
            this.lblRecFileName.Text = "File Name: N/A";
            // 
            // lblRecordedCount
            // 
            this.lblRecordedCount.AutoSize = true;
            this.lblRecordedCount.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.lblRecordedCount.Location = new System.Drawing.Point(140, 21);
            this.lblRecordedCount.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.lblRecordedCount.Name = "lblRecordedCount";
            this.lblRecordedCount.Size = new System.Drawing.Size(127, 17);
            this.lblRecordedCount.TabIndex = 15;
            this.lblRecordedCount.Text = "Recorded Count: 0";
            // 
            // btnStopRecording
            // 
            this.btnStopRecording.Location = new System.Drawing.Point(71, 18);
            this.btnStopRecording.Margin = new System.Windows.Forms.Padding(2);
            this.btnStopRecording.Name = "btnStopRecording";
            this.btnStopRecording.Size = new System.Drawing.Size(56, 27);
            this.btnStopRecording.TabIndex = 1;
            this.btnStopRecording.Text = "STOP";
            this.btnStopRecording.UseVisualStyleBackColor = true;
            this.btnStopRecording.Click += new System.EventHandler(this.btnStopRecording_Click);
            // 
            // btnStartRecording
            // 
            this.btnStartRecording.Location = new System.Drawing.Point(10, 18);
            this.btnStartRecording.Margin = new System.Windows.Forms.Padding(2);
            this.btnStartRecording.Name = "btnStartRecording";
            this.btnStartRecording.Size = new System.Drawing.Size(56, 27);
            this.btnStartRecording.TabIndex = 0;
            this.btnStartRecording.Text = "START";
            this.btnStartRecording.UseVisualStyleBackColor = true;
            this.btnStartRecording.Click += new System.EventHandler(this.btnStartRecording_Click);
            // 
            // chkAutoBatch
            // 
            this.chkAutoBatch.Location = new System.Drawing.Point(112, 75);
            this.chkAutoBatch.Margin = new System.Windows.Forms.Padding(2);
            this.chkAutoBatch.Name = "chkAutoBatch";
            this.chkAutoBatch.Size = new System.Drawing.Size(152, 20);
            this.chkAutoBatch.TabIndex = 19;
            this.chkAutoBatch.Text = "Auto Request Batch";
            this.chkAutoBatch.UseVisualStyleBackColor = true;
            this.chkAutoBatch.CheckedChanged += new System.EventHandler(this.chkAutoBatch_CheckedChanged);
            // 
            // btnRunBatch
            // 
            this.btnRunBatch.Location = new System.Drawing.Point(15, 68);
            this.btnRunBatch.Name = "btnRunBatch";
            this.btnRunBatch.Size = new System.Drawing.Size(83, 32);
            this.btnRunBatch.TabIndex = 12;
            this.btnRunBatch.Text = "Start";
            this.btnRunBatch.UseVisualStyleBackColor = true;
            this.btnRunBatch.Click += new System.EventHandler(this.btnRunBatch_Click);
            // 
            // groupBox2
            // 
            this.groupBox2.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.groupBox2.Controls.Add(this.btnStateInfo);
            this.groupBox2.Controls.Add(this.btnSetBinLength);
            this.groupBox2.Controls.Add(this.nudBinLength);
            this.groupBox2.Controls.Add(this.lblTDCBinLength);
            this.groupBox2.Controls.Add(this.lblStateMask);
            this.groupBox2.Controls.Add(this.btnResetMCU);
            this.groupBox2.Controls.Add(this.btnSetRefDistance);
            this.groupBox2.Controls.Add(this.numRefDistance);
            this.groupBox2.Controls.Add(this.label1);
            this.groupBox2.Controls.Add(this.lblTestDistance);
            this.groupBox2.Controls.Add(this.btnSaveToFlash);
            this.groupBox2.Controls.Add(this.lblAPDVoltFB);
            this.groupBox2.Controls.Add(this.btnSetAPD_TargVoltage);
            this.groupBox2.Controls.Add(this.numAPD_TargVoltage);
            this.groupBox2.Controls.Add(this.lblAPD_TargetVoltage);
            this.groupBox2.Controls.Add(this.btnSetCompVolt);
            this.groupBox2.Controls.Add(this.btnSetAPD_PWM);
            this.groupBox2.Controls.Add(this.btnSetLaserVolt);
            this.groupBox2.Controls.Add(this.numCompVolt);
            this.groupBox2.Controls.Add(this.numAPD_PWM);
            this.groupBox2.Controls.Add(this.numLaserVolt);
            this.groupBox2.Controls.Add(this.chkAutoRequests);
            this.groupBox2.Controls.Add(this.lblRawTOFWidth);
            this.groupBox2.Controls.Add(this.lblRawTOFValue);
            this.groupBox2.Controls.Add(this.lblCompVolt);
            this.groupBox2.Controls.Add(this.lblAPD_PWM);
            this.groupBox2.Controls.Add(this.lblAPDVolt);
            this.groupBox2.Controls.Add(this.lblLaserVolt);
            this.groupBox2.Controls.Add(this.btnStateRequest);
            this.groupBox2.Location = new System.Drawing.Point(688, 6);
            this.groupBox2.Margin = new System.Windows.Forms.Padding(2);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Padding = new System.Windows.Forms.Padding(2);
            this.groupBox2.Size = new System.Drawing.Size(296, 406);
            this.groupBox2.TabIndex = 14;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Rangefinder State";
            // 
            // btnSetBinLength
            // 
            this.btnSetBinLength.Location = new System.Drawing.Point(246, 251);
            this.btnSetBinLength.Margin = new System.Windows.Forms.Padding(2);
            this.btnSetBinLength.Name = "btnSetBinLength";
            this.btnSetBinLength.Size = new System.Drawing.Size(44, 24);
            this.btnSetBinLength.TabIndex = 27;
            this.btnSetBinLength.Text = "SET";
            this.btnSetBinLength.UseVisualStyleBackColor = true;
            this.btnSetBinLength.Click += new System.EventHandler(this.btnSetBinLength_Click);
            // 
            // nudBinLength
            // 
            this.nudBinLength.DecimalPlaces = 1;
            this.nudBinLength.Location = new System.Drawing.Point(190, 254);
            this.nudBinLength.Margin = new System.Windows.Forms.Padding(2);
            this.nudBinLength.Maximum = new decimal(new int[] {
            20,
            0,
            0,
            0});
            this.nudBinLength.Minimum = new decimal(new int[] {
            5,
            0,
            0,
            0});
            this.nudBinLength.Name = "nudBinLength";
            this.nudBinLength.Size = new System.Drawing.Size(49, 20);
            this.nudBinLength.TabIndex = 26;
            this.nudBinLength.Value = new decimal(new int[] {
            14,
            0,
            0,
            0});
            // 
            // lblTDCBinLength
            // 
            this.lblTDCBinLength.AutoSize = true;
            this.lblTDCBinLength.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.lblTDCBinLength.Location = new System.Drawing.Point(8, 254);
            this.lblTDCBinLength.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.lblTDCBinLength.Name = "lblTDCBinLength";
            this.lblTDCBinLength.Size = new System.Drawing.Size(158, 20);
            this.lblTDCBinLength.TabIndex = 25;
            this.lblTDCBinLength.Text = "BIN Length, mm: N/A";
            // 
            // lblStateMask
            // 
            this.lblStateMask.AutoSize = true;
            this.lblStateMask.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.lblStateMask.Location = new System.Drawing.Point(8, 375);
            this.lblStateMask.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.lblStateMask.Name = "lblStateMask";
            this.lblStateMask.Size = new System.Drawing.Size(109, 17);
            this.lblStateMask.TabIndex = 24;
            this.lblStateMask.Text = "State mask: N/A";
            // 
            // btnResetMCU
            // 
            this.btnResetMCU.BackColor = System.Drawing.Color.Yellow;
            this.btnResetMCU.Location = new System.Drawing.Point(194, 342);
            this.btnResetMCU.Margin = new System.Windows.Forms.Padding(2);
            this.btnResetMCU.Name = "btnResetMCU";
            this.btnResetMCU.Size = new System.Drawing.Size(98, 24);
            this.btnResetMCU.TabIndex = 23;
            this.btnResetMCU.Text = "Reset MCU";
            this.btnResetMCU.UseVisualStyleBackColor = false;
            this.btnResetMCU.Click += new System.EventHandler(this.btnResetMCU_Click);
            // 
            // btnSetRefDistance
            // 
            this.btnSetRefDistance.Location = new System.Drawing.Point(246, 221);
            this.btnSetRefDistance.Margin = new System.Windows.Forms.Padding(2);
            this.btnSetRefDistance.Name = "btnSetRefDistance";
            this.btnSetRefDistance.Size = new System.Drawing.Size(44, 24);
            this.btnSetRefDistance.TabIndex = 22;
            this.btnSetRefDistance.Text = "SET";
            this.btnSetRefDistance.UseVisualStyleBackColor = true;
            this.btnSetRefDistance.Click += new System.EventHandler(this.btnSetRefDistance_Click);
            // 
            // numRefDistance
            // 
            this.numRefDistance.Location = new System.Drawing.Point(170, 224);
            this.numRefDistance.Margin = new System.Windows.Forms.Padding(2);
            this.numRefDistance.Maximum = new decimal(new int[] {
            10000,
            0,
            0,
            0});
            this.numRefDistance.Name = "numRefDistance";
            this.numRefDistance.Size = new System.Drawing.Size(71, 20);
            this.numRefDistance.TabIndex = 21;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label1.Location = new System.Drawing.Point(8, 222);
            this.label1.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(137, 20);
            this.label1.TabIndex = 20;
            this.label1.Text = "Ref distance, mm:";
            // 
            // lblTestDistance
            // 
            this.lblTestDistance.AutoSize = true;
            this.lblTestDistance.Font = new System.Drawing.Font("Microsoft Sans Serif", 13.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.lblTestDistance.Location = new System.Drawing.Point(8, 337);
            this.lblTestDistance.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.lblTestDistance.Name = "lblTestDistance";
            this.lblTestDistance.Size = new System.Drawing.Size(124, 24);
            this.lblTestDistance.TabIndex = 19;
            this.lblTestDistance.Text = "Distance: N/A";
            // 
            // btnSaveToFlash
            // 
            this.btnSaveToFlash.BackColor = System.Drawing.Color.Yellow;
            this.btnSaveToFlash.Location = new System.Drawing.Point(194, 371);
            this.btnSaveToFlash.Margin = new System.Windows.Forms.Padding(2);
            this.btnSaveToFlash.Name = "btnSaveToFlash";
            this.btnSaveToFlash.Size = new System.Drawing.Size(98, 24);
            this.btnSaveToFlash.TabIndex = 18;
            this.btnSaveToFlash.Text = "Save to Flash";
            this.btnSaveToFlash.UseVisualStyleBackColor = false;
            this.btnSaveToFlash.Click += new System.EventHandler(this.btnSaveToFlash_Click);
            // 
            // lblAPDVoltFB
            // 
            this.lblAPDVoltFB.AutoSize = true;
            this.lblAPDVoltFB.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.lblAPDVoltFB.Location = new System.Drawing.Point(8, 166);
            this.lblAPDVoltFB.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.lblAPDVoltFB.Name = "lblAPDVoltFB";
            this.lblAPDVoltFB.Size = new System.Drawing.Size(187, 20);
            this.lblAPDVoltFB.TabIndex = 17;
            this.lblAPDVoltFB.Text = "APD Volt. Feedback: N/A";
            // 
            // btnSetAPD_TargVoltage
            // 
            this.btnSetAPD_TargVoltage.Location = new System.Drawing.Point(246, 138);
            this.btnSetAPD_TargVoltage.Margin = new System.Windows.Forms.Padding(2);
            this.btnSetAPD_TargVoltage.Name = "btnSetAPD_TargVoltage";
            this.btnSetAPD_TargVoltage.Size = new System.Drawing.Size(44, 24);
            this.btnSetAPD_TargVoltage.TabIndex = 16;
            this.btnSetAPD_TargVoltage.Text = "SET";
            this.btnSetAPD_TargVoltage.UseVisualStyleBackColor = true;
            this.btnSetAPD_TargVoltage.Click += new System.EventHandler(this.btnSetAPD_TargVoltage_Click);
            // 
            // numAPD_TargVoltage
            // 
            this.numAPD_TargVoltage.Location = new System.Drawing.Point(190, 141);
            this.numAPD_TargVoltage.Margin = new System.Windows.Forms.Padding(2);
            this.numAPD_TargVoltage.Maximum = new decimal(new int[] {
            150,
            0,
            0,
            0});
            this.numAPD_TargVoltage.Minimum = new decimal(new int[] {
            10,
            0,
            0,
            0});
            this.numAPD_TargVoltage.Name = "numAPD_TargVoltage";
            this.numAPD_TargVoltage.Size = new System.Drawing.Size(49, 20);
            this.numAPD_TargVoltage.TabIndex = 15;
            this.numAPD_TargVoltage.Value = new decimal(new int[] {
            90,
            0,
            0,
            0});
            // 
            // lblAPD_TargetVoltage
            // 
            this.lblAPD_TargetVoltage.AutoSize = true;
            this.lblAPD_TargetVoltage.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.lblAPD_TargetVoltage.Location = new System.Drawing.Point(8, 140);
            this.lblAPD_TargetVoltage.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.lblAPD_TargetVoltage.Name = "lblAPD_TargetVoltage";
            this.lblAPD_TargetVoltage.Size = new System.Drawing.Size(131, 20);
            this.lblAPD_TargetVoltage.TabIndex = 14;
            this.lblAPD_TargetVoltage.Text = "APD Targ. V: N/A";
            // 
            // btnSetCompVolt
            // 
            this.btnSetCompVolt.Location = new System.Drawing.Point(246, 191);
            this.btnSetCompVolt.Margin = new System.Windows.Forms.Padding(2);
            this.btnSetCompVolt.Name = "btnSetCompVolt";
            this.btnSetCompVolt.Size = new System.Drawing.Size(44, 24);
            this.btnSetCompVolt.TabIndex = 13;
            this.btnSetCompVolt.Text = "SET";
            this.btnSetCompVolt.UseVisualStyleBackColor = true;
            this.btnSetCompVolt.Click += new System.EventHandler(this.btnSetCompVolt_Click);
            // 
            // btnSetAPD_PWM
            // 
            this.btnSetAPD_PWM.Location = new System.Drawing.Point(246, 106);
            this.btnSetAPD_PWM.Margin = new System.Windows.Forms.Padding(2);
            this.btnSetAPD_PWM.Name = "btnSetAPD_PWM";
            this.btnSetAPD_PWM.Size = new System.Drawing.Size(44, 24);
            this.btnSetAPD_PWM.TabIndex = 12;
            this.btnSetAPD_PWM.Text = "SET";
            this.btnSetAPD_PWM.UseVisualStyleBackColor = true;
            this.btnSetAPD_PWM.Click += new System.EventHandler(this.btnSetAPD_PWM_Click);
            // 
            // btnSetLaserVolt
            // 
            this.btnSetLaserVolt.Location = new System.Drawing.Point(246, 52);
            this.btnSetLaserVolt.Margin = new System.Windows.Forms.Padding(2);
            this.btnSetLaserVolt.Name = "btnSetLaserVolt";
            this.btnSetLaserVolt.Size = new System.Drawing.Size(44, 24);
            this.btnSetLaserVolt.TabIndex = 11;
            this.btnSetLaserVolt.Text = "SET";
            this.btnSetLaserVolt.UseVisualStyleBackColor = true;
            this.btnSetLaserVolt.Click += new System.EventHandler(this.btnSetLaserVolt_Click);
            // 
            // numCompVolt
            // 
            this.numCompVolt.Location = new System.Drawing.Point(190, 193);
            this.numCompVolt.Margin = new System.Windows.Forms.Padding(2);
            this.numCompVolt.Maximum = new decimal(new int[] {
            1000,
            0,
            0,
            0});
            this.numCompVolt.Name = "numCompVolt";
            this.numCompVolt.Size = new System.Drawing.Size(51, 20);
            this.numCompVolt.TabIndex = 10;
            // 
            // numAPD_PWM
            // 
            this.numAPD_PWM.Location = new System.Drawing.Point(190, 110);
            this.numAPD_PWM.Margin = new System.Windows.Forms.Padding(2);
            this.numAPD_PWM.Maximum = new decimal(new int[] {
            200,
            0,
            0,
            0});
            this.numAPD_PWM.Name = "numAPD_PWM";
            this.numAPD_PWM.Size = new System.Drawing.Size(49, 20);
            this.numAPD_PWM.TabIndex = 9;
            // 
            // numLaserVolt
            // 
            this.numLaserVolt.Location = new System.Drawing.Point(190, 55);
            this.numLaserVolt.Margin = new System.Windows.Forms.Padding(2);
            this.numLaserVolt.Maximum = new decimal(new int[] {
            19,
            0,
            0,
            0});
            this.numLaserVolt.Name = "numLaserVolt";
            this.numLaserVolt.Size = new System.Drawing.Size(51, 20);
            this.numLaserVolt.TabIndex = 8;
            // 
            // chkAutoRequests
            // 
            this.chkAutoRequests.AutoSize = true;
            this.chkAutoRequests.Location = new System.Drawing.Point(110, 30);
            this.chkAutoRequests.Margin = new System.Windows.Forms.Padding(2);
            this.chkAutoRequests.Name = "chkAutoRequests";
            this.chkAutoRequests.Size = new System.Drawing.Size(91, 17);
            this.chkAutoRequests.TabIndex = 7;
            this.chkAutoRequests.Text = "Auto requests";
            this.chkAutoRequests.UseVisualStyleBackColor = true;
            this.chkAutoRequests.CheckedChanged += new System.EventHandler(this.chkAutoRequests_CheckedChanged);
            // 
            // lblRawTOFWidth
            // 
            this.lblRawTOFWidth.AutoSize = true;
            this.lblRawTOFWidth.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.lblRawTOFWidth.Location = new System.Drawing.Point(8, 312);
            this.lblRawTOFWidth.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.lblRawTOFWidth.Name = "lblRawTOFWidth";
            this.lblRawTOFWidth.Size = new System.Drawing.Size(151, 20);
            this.lblRawTOFWidth.TabIndex = 6;
            this.lblRawTOFWidth.Text = "Raw TOF width: N/A";
            // 
            // lblRawTOFValue
            // 
            this.lblRawTOFValue.AutoSize = true;
            this.lblRawTOFValue.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.lblRawTOFValue.Location = new System.Drawing.Point(8, 288);
            this.lblRawTOFValue.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.lblRawTOFValue.Name = "lblRawTOFValue";
            this.lblRawTOFValue.Size = new System.Drawing.Size(110, 20);
            this.lblRawTOFValue.TabIndex = 5;
            this.lblRawTOFValue.Text = "Raw TOF: N/A";
            // 
            // lblCompVolt
            // 
            this.lblCompVolt.AutoSize = true;
            this.lblCompVolt.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.lblCompVolt.Location = new System.Drawing.Point(8, 192);
            this.lblCompVolt.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.lblCompVolt.Name = "lblCompVolt";
            this.lblCompVolt.Size = new System.Drawing.Size(117, 20);
            this.lblCompVolt.TabIndex = 4;
            this.lblCompVolt.Text = "Comp Volt: N/A";
            // 
            // lblAPD_PWM
            // 
            this.lblAPD_PWM.AutoSize = true;
            this.lblAPD_PWM.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.lblAPD_PWM.Location = new System.Drawing.Point(8, 110);
            this.lblAPD_PWM.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.lblAPD_PWM.Name = "lblAPD_PWM";
            this.lblAPD_PWM.Size = new System.Drawing.Size(118, 20);
            this.lblAPD_PWM.TabIndex = 3;
            this.lblAPD_PWM.Text = "APD PWM: N/A";
            // 
            // lblAPDVolt
            // 
            this.lblAPDVolt.AutoSize = true;
            this.lblAPDVolt.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.lblAPDVolt.Location = new System.Drawing.Point(8, 83);
            this.lblAPDVolt.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.lblAPDVolt.Name = "lblAPDVolt";
            this.lblAPDVolt.Size = new System.Drawing.Size(108, 20);
            this.lblAPDVolt.TabIndex = 2;
            this.lblAPDVolt.Text = "APD Volt: N/A";
            // 
            // lblLaserVolt
            // 
            this.lblLaserVolt.AutoSize = true;
            this.lblLaserVolt.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.lblLaserVolt.Location = new System.Drawing.Point(8, 55);
            this.lblLaserVolt.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.lblLaserVolt.Name = "lblLaserVolt";
            this.lblLaserVolt.Size = new System.Drawing.Size(115, 20);
            this.lblLaserVolt.TabIndex = 1;
            this.lblLaserVolt.Text = "Laser Volt: N/A";
            // 
            // btnStateRequest
            // 
            this.btnStateRequest.Location = new System.Drawing.Point(11, 25);
            this.btnStateRequest.Margin = new System.Windows.Forms.Padding(2);
            this.btnStateRequest.Name = "btnStateRequest";
            this.btnStateRequest.Size = new System.Drawing.Size(76, 24);
            this.btnStateRequest.TabIndex = 0;
            this.btnStateRequest.Text = "Request";
            this.btnStateRequest.UseVisualStyleBackColor = true;
            this.btnStateRequest.Click += new System.EventHandler(this.btnStateRequest_Click);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.lblRXPacketCNT);
            this.groupBox1.Controls.Add(this.btnOpen);
            this.groupBox1.Controls.Add(this.comboBox_ports);
            this.groupBox1.Location = new System.Drawing.Point(8, 6);
            this.groupBox1.Margin = new System.Windows.Forms.Padding(2);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Padding = new System.Windows.Forms.Padding(2);
            this.groupBox1.Size = new System.Drawing.Size(518, 57);
            this.groupBox1.TabIndex = 13;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Port";
            // 
            // lblRXPacketCNT
            // 
            this.lblRXPacketCNT.AutoSize = true;
            this.lblRXPacketCNT.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.lblRXPacketCNT.Location = new System.Drawing.Point(330, 24);
            this.lblRXPacketCNT.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.lblRXPacketCNT.Name = "lblRXPacketCNT";
            this.lblRXPacketCNT.Size = new System.Drawing.Size(137, 17);
            this.lblRXPacketCNT.TabIndex = 14;
            this.lblRXPacketCNT.Text = "RX Packet CNT: N/A";
            // 
            // btnOpen
            // 
            this.btnOpen.Location = new System.Drawing.Point(8, 18);
            this.btnOpen.Name = "btnOpen";
            this.btnOpen.Size = new System.Drawing.Size(83, 32);
            this.btnOpen.TabIndex = 2;
            this.btnOpen.Text = "Open";
            this.btnOpen.UseVisualStyleBackColor = true;
            this.btnOpen.Click += new System.EventHandler(this.btnOpen_Click);
            // 
            // comboBox_ports
            // 
            this.comboBox_ports.FormattingEnabled = true;
            this.comboBox_ports.Location = new System.Drawing.Point(104, 24);
            this.comboBox_ports.Name = "comboBox_ports";
            this.comboBox_ports.Size = new System.Drawing.Size(207, 21);
            this.comboBox_ports.TabIndex = 3;
            this.comboBox_ports.DropDown += new System.EventHandler(this.comboBox_ports_DropDown);
            // 
            // dataGridView1
            // 
            this.dataGridView1.AllowUserToOrderColumns = true;
            this.dataGridView1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left)));
            this.dataGridView1.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView1.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.Column1,
            this.Column4,
            this.Column2});
            this.dataGridView1.Location = new System.Drawing.Point(8, 106);
            this.dataGridView1.Name = "dataGridView1";
            this.dataGridView1.RowHeadersVisible = false;
            this.dataGridView1.Size = new System.Drawing.Size(301, 401);
            this.dataGridView1.TabIndex = 15;
            // 
            // Column1
            // 
            this.Column1.HeaderText = "START";
            this.Column1.Name = "Column1";
            this.Column1.ReadOnly = true;
            // 
            // Column4
            // 
            this.Column4.HeaderText = "WIDTH";
            this.Column4.Name = "Column4";
            this.Column4.ReadOnly = true;
            this.Column4.Width = 60;
            // 
            // Column2
            // 
            this.Column2.HeaderText = "CORR. START";
            this.Column2.Name = "Column2";
            this.Column2.Width = 120;
            // 
            // tabPageCalibration
            // 
            this.tabPageCalibration.Controls.Add(this.calibrationControl1);
            this.tabPageCalibration.Location = new System.Drawing.Point(4, 22);
            this.tabPageCalibration.Margin = new System.Windows.Forms.Padding(2);
            this.tabPageCalibration.Name = "tabPageCalibration";
            this.tabPageCalibration.Padding = new System.Windows.Forms.Padding(2);
            this.tabPageCalibration.Size = new System.Drawing.Size(996, 515);
            this.tabPageCalibration.TabIndex = 1;
            this.tabPageCalibration.Text = "Calibration";
            this.tabPageCalibration.UseVisualStyleBackColor = true;
            // 
            // tabPageMotor
            // 
            this.tabPageMotor.Controls.Add(this.motorControl1);
            this.tabPageMotor.Location = new System.Drawing.Point(4, 22);
            this.tabPageMotor.Name = "tabPageMotor";
            this.tabPageMotor.Padding = new System.Windows.Forms.Padding(3);
            this.tabPageMotor.Size = new System.Drawing.Size(996, 515);
            this.tabPageMotor.TabIndex = 2;
            this.tabPageMotor.Text = "Motor Settings";
            this.tabPageMotor.UseVisualStyleBackColor = true;
            // 
            // timer_batch
            // 
            this.timer_batch.Interval = 1000;
            this.timer_batch.Tick += new System.EventHandler(this.timer_batch_Tick);
            // 
            // timer_req
            // 
            this.timer_req.Interval = 200;
            this.timer_req.Tick += new System.EventHandler(this.timer_req_Tick);
            // 
            // btnStateInfo
            // 
            this.btnStateInfo.Location = new System.Drawing.Point(142, 373);
            this.btnStateInfo.Margin = new System.Windows.Forms.Padding(2);
            this.btnStateInfo.Name = "btnStateInfo";
            this.btnStateInfo.Size = new System.Drawing.Size(39, 21);
            this.btnStateInfo.TabIndex = 28;
            this.btnStateInfo.Text = "Info";
            this.btnStateInfo.UseVisualStyleBackColor = true;
            this.btnStateInfo.Click += new System.EventHandler(this.btnStateInfo_Click);
            // 
            // calibrationControl1
            // 
            this.calibrationControl1.Location = new System.Drawing.Point(4, 5);
            this.calibrationControl1.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.calibrationControl1.Name = "calibrationControl1";
            this.calibrationControl1.Size = new System.Drawing.Size(943, 440);
            this.calibrationControl1.TabIndex = 0;
            // 
            // motorControl1
            // 
            this.motorControl1.Location = new System.Drawing.Point(8, 6);
            this.motorControl1.Name = "motorControl1";
            this.motorControl1.Size = new System.Drawing.Size(572, 279);
            this.motorControl1.TabIndex = 0;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1004, 541);
            this.Controls.Add(this.tabControl1);
            this.Margin = new System.Windows.Forms.Padding(2);
            this.Name = "Form1";
            this.Text = "OpenTOFLidar Testing Utility v1.1";
            this.tabControl1.ResumeLayout(false);
            this.tabPageMain.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.chart1)).EndInit();
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.nudBinLength)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numRefDistance)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numAPD_TargVoltage)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numCompVolt)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numAPD_PWM)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numLaserVolt)).EndInit();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).EndInit();
            this.tabPageCalibration.ResumeLayout(false);
            this.tabPageMotor.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage tabPageMain;
        private System.Windows.Forms.CheckBox chkSkipFirst;
        private System.Windows.Forms.DataVisualization.Charting.Chart chart1;
        private System.Windows.Forms.Label lblResults;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.Label lblRecordedCount;
        private System.Windows.Forms.Button btnStopRecording;
        private System.Windows.Forms.Button btnStartRecording;
        private System.Windows.Forms.CheckBox chkAutoBatch;
        private System.Windows.Forms.Button btnRunBatch;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Button btnSetCompVolt;
        private System.Windows.Forms.Button btnSetAPD_PWM;
        private System.Windows.Forms.Button btnSetLaserVolt;
        private System.Windows.Forms.NumericUpDown numCompVolt;
        private System.Windows.Forms.NumericUpDown numAPD_PWM;
        private System.Windows.Forms.NumericUpDown numLaserVolt;
        private System.Windows.Forms.CheckBox chkAutoRequests;
        private System.Windows.Forms.Label lblRawTOFWidth;
        private System.Windows.Forms.Label lblRawTOFValue;
        private System.Windows.Forms.Label lblCompVolt;
        private System.Windows.Forms.Label lblAPD_PWM;
        private System.Windows.Forms.Label lblAPDVolt;
        private System.Windows.Forms.Label lblLaserVolt;
        private System.Windows.Forms.Button btnStateRequest;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Label lblRXPacketCNT;
        private System.Windows.Forms.Button btnOpen;
        private System.Windows.Forms.ComboBox comboBox_ports;
        private System.Windows.Forms.DataGridView dataGridView1;
        private System.Windows.Forms.TabPage tabPageCalibration;
        private System.Windows.Forms.Timer timer_batch;
        private System.Windows.Forms.Timer timer_req;
        private System.Windows.Forms.Label lblRecFileName;
        private CalibrationControl calibrationControl1;
        private System.Windows.Forms.Label lblAPDVoltFB;
        private System.Windows.Forms.Button btnSetAPD_TargVoltage;
        private System.Windows.Forms.NumericUpDown numAPD_TargVoltage;
        private System.Windows.Forms.Label lblAPD_TargetVoltage;
        private System.Windows.Forms.Button btnSaveToFlash;
        private System.Windows.Forms.Label lblTestDistance;
        private System.Windows.Forms.Button btnSetRefDistance;
        private System.Windows.Forms.NumericUpDown numRefDistance;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.DataGridViewTextBoxColumn Column1;
        private System.Windows.Forms.DataGridViewTextBoxColumn Column4;
        private System.Windows.Forms.DataGridViewTextBoxColumn Column2;
        private System.Windows.Forms.Button btnResetMCU;
        private System.Windows.Forms.Label lblStateMask;
        private System.Windows.Forms.TabPage tabPageMotor;
        private MotorControl motorControl1;
        private System.Windows.Forms.Button btnSetBinLength;
        private System.Windows.Forms.NumericUpDown nudBinLength;
        private System.Windows.Forms.Label lblTDCBinLength;
        private System.Windows.Forms.Button btnStateInfo;
    }
}

