namespace LidarScanningTest1
{
    partial class HistogramForm
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
            System.Windows.Forms.DataVisualization.Charting.ChartArea chartArea2 = new System.Windows.Forms.DataVisualization.Charting.ChartArea();
            System.Windows.Forms.DataVisualization.Charting.Series series2 = new System.Windows.Forms.DataVisualization.Charting.Series();
            this.chart1 = new System.Windows.Forms.DataVisualization.Charting.Chart();
            this.lblMaxMIn = new System.Windows.Forms.Label();
            this.lblStdDev = new System.Windows.Forms.Label();
            this.lblAVRValue = new System.Windows.Forms.Label();
            this.nudScansNumber = new System.Windows.Forms.NumericUpDown();
            this.label1 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.chart1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.nudScansNumber)).BeginInit();
            this.SuspendLayout();
            // 
            // chart1
            // 
            this.chart1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            chartArea2.Name = "ChartArea1";
            this.chart1.ChartAreas.Add(chartArea2);
            this.chart1.Location = new System.Drawing.Point(12, 11);
            this.chart1.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.chart1.Name = "chart1";
            series2.ChartArea = "ChartArea1";
            series2.Name = "Series1";
            this.chart1.Series.Add(series2);
            this.chart1.Size = new System.Drawing.Size(520, 198);
            this.chart1.TabIndex = 18;
            this.chart1.Text = "chart1";
            // 
            // lblMaxMIn
            // 
            this.lblMaxMIn.AutoSize = true;
            this.lblMaxMIn.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.lblMaxMIn.Location = new System.Drawing.Point(11, 304);
            this.lblMaxMIn.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.lblMaxMIn.Name = "lblMaxMIn";
            this.lblMaxMIn.Size = new System.Drawing.Size(97, 20);
            this.lblMaxMIn.TabIndex = 19;
            this.lblMaxMIn.Text = "MaxMin: N/A";
            // 
            // lblStdDev
            // 
            this.lblStdDev.AutoSize = true;
            this.lblStdDev.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.lblStdDev.Location = new System.Drawing.Point(11, 276);
            this.lblStdDev.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.lblStdDev.Name = "lblStdDev";
            this.lblStdDev.Size = new System.Drawing.Size(113, 20);
            this.lblStdDev.TabIndex = 20;
            this.lblStdDev.Text = "STD DEV: N/A";
            // 
            // lblAVRValue
            // 
            this.lblAVRValue.AutoSize = true;
            this.lblAVRValue.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.lblAVRValue.Location = new System.Drawing.Point(12, 251);
            this.lblAVRValue.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.lblAVRValue.Name = "lblAVRValue";
            this.lblAVRValue.Size = new System.Drawing.Size(102, 20);
            this.lblAVRValue.TabIndex = 21;
            this.lblAVRValue.Text = "Average: N/A";
            // 
            // nudScansNumber
            // 
            this.nudScansNumber.Increment = new decimal(new int[] {
            5,
            0,
            0,
            0});
            this.nudScansNumber.Location = new System.Drawing.Point(130, 223);
            this.nudScansNumber.Margin = new System.Windows.Forms.Padding(2);
            this.nudScansNumber.Minimum = new decimal(new int[] {
            20,
            0,
            0,
            0});
            this.nudScansNumber.Name = "nudScansNumber";
            this.nudScansNumber.Size = new System.Drawing.Size(68, 20);
            this.nudScansNumber.TabIndex = 22;
            this.nudScansNumber.Value = new decimal(new int[] {
            20,
            0,
            0,
            0});
            this.nudScansNumber.ValueChanged += new System.EventHandler(this.nudScansNumber_ValueChanged);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label1.Location = new System.Drawing.Point(13, 225);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(112, 16);
            this.label1.TabIndex = 23;
            this.label1.Text = "Number of scans:";
            // 
            // HistogramForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(544, 335);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.nudScansNumber);
            this.Controls.Add(this.lblAVRValue);
            this.Controls.Add(this.lblStdDev);
            this.Controls.Add(this.lblMaxMIn);
            this.Controls.Add(this.chart1);
            this.Name = "HistogramForm";
            this.Text = "Histogram";
            ((System.ComponentModel.ISupportInitialize)(this.chart1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.nudScansNumber)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.DataVisualization.Charting.Chart chart1;
        private System.Windows.Forms.Label lblMaxMIn;
        private System.Windows.Forms.Label lblStdDev;
        private System.Windows.Forms.Label lblAVRValue;
        private System.Windows.Forms.NumericUpDown nudScansNumber;
        private System.Windows.Forms.Label label1;
    }
}