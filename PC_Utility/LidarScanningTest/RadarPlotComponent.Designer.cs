namespace LidarScanningTest1
{
    partial class RadarPlotComponent
    {
        private System.ComponentModel.IContainer components = null;

        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Код, автоматически созданный конструктором компонентов

        /// <summary> 
        /// Требуемый метод для поддержки конструктора — не изменяйте 
        /// содержимое этого метода с помощью редактора кода.
        /// </summary>
        private void InitializeComponent()
        {
            this.cmbRadiusList = new System.Windows.Forms.ComboBox();
            this.label1 = new System.Windows.Forms.Label();
            this.chkBlackMode = new System.Windows.Forms.CheckBox();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.splitContainer1 = new System.Windows.Forms.SplitContainer();
            this.btnAngleMinus = new System.Windows.Forms.Button();
            this.btnAnglePlus = new System.Windows.Forms.Button();
            this.trackBar1 = new System.Windows.Forms.TrackBar();
            this.lblPointerAnle = new System.Windows.Forms.Label();
            this.chkDrawWrongPoints = new System.Windows.Forms.CheckBox();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).BeginInit();
            this.splitContainer1.Panel1.SuspendLayout();
            this.splitContainer1.Panel2.SuspendLayout();
            this.splitContainer1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.trackBar1)).BeginInit();
            this.SuspendLayout();
            // 
            // cmbRadiusList
            // 
            this.cmbRadiusList.FormattingEnabled = true;
            this.cmbRadiusList.Location = new System.Drawing.Point(10, 31);
            this.cmbRadiusList.Margin = new System.Windows.Forms.Padding(2);
            this.cmbRadiusList.Name = "cmbRadiusList";
            this.cmbRadiusList.Size = new System.Drawing.Size(70, 21);
            this.cmbRadiusList.TabIndex = 2;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(14, 10);
            this.label1.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(54, 13);
            this.label1.TabIndex = 3;
            this.label1.Text = "Radius, m";
            // 
            // chkBlackMode
            // 
            this.chkBlackMode.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.chkBlackMode.AutoSize = true;
            this.chkBlackMode.Location = new System.Drawing.Point(9, 62);
            this.chkBlackMode.Margin = new System.Windows.Forms.Padding(2);
            this.chkBlackMode.Name = "chkBlackMode";
            this.chkBlackMode.Size = new System.Drawing.Size(83, 17);
            this.chkBlackMode.TabIndex = 4;
            this.chkBlackMode.Text = "Black Mode";
            this.chkBlackMode.UseVisualStyleBackColor = true;
            // 
            // pictureBox1
            // 
            this.pictureBox1.BackColor = System.Drawing.Color.Silver;
            this.pictureBox1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.pictureBox1.Location = new System.Drawing.Point(0, 0);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(486, 415);
            this.pictureBox1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.CenterImage;
            this.pictureBox1.TabIndex = 1;
            this.pictureBox1.TabStop = false;
            // 
            // splitContainer1
            // 
            this.splitContainer1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer1.FixedPanel = System.Windows.Forms.FixedPanel.Panel2;
            this.splitContainer1.Location = new System.Drawing.Point(0, 0);
            this.splitContainer1.Margin = new System.Windows.Forms.Padding(2);
            this.splitContainer1.Name = "splitContainer1";
            // 
            // splitContainer1.Panel1
            // 
            this.splitContainer1.Panel1.Controls.Add(this.pictureBox1);
            // 
            // splitContainer1.Panel2
            // 
            this.splitContainer1.Panel2.Controls.Add(this.chkDrawWrongPoints);
            this.splitContainer1.Panel2.Controls.Add(this.btnAngleMinus);
            this.splitContainer1.Panel2.Controls.Add(this.btnAnglePlus);
            this.splitContainer1.Panel2.Controls.Add(this.trackBar1);
            this.splitContainer1.Panel2.Controls.Add(this.lblPointerAnle);
            this.splitContainer1.Panel2.Controls.Add(this.label1);
            this.splitContainer1.Panel2.Controls.Add(this.chkBlackMode);
            this.splitContainer1.Panel2.Controls.Add(this.cmbRadiusList);
            this.splitContainer1.Size = new System.Drawing.Size(615, 415);
            this.splitContainer1.SplitterDistance = 486;
            this.splitContainer1.SplitterWidth = 3;
            this.splitContainer1.TabIndex = 5;
            // 
            // btnAngleMinus
            // 
            this.btnAngleMinus.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.btnAngleMinus.Location = new System.Drawing.Point(78, 369);
            this.btnAngleMinus.Name = "btnAngleMinus";
            this.btnAngleMinus.Size = new System.Drawing.Size(35, 35);
            this.btnAngleMinus.TabIndex = 9;
            this.btnAngleMinus.Text = "-";
            this.btnAngleMinus.UseVisualStyleBackColor = true;
            this.btnAngleMinus.Click += new System.EventHandler(this.btnAngleMinus_Click);
            // 
            // btnAnglePlus
            // 
            this.btnAnglePlus.Location = new System.Drawing.Point(78, 156);
            this.btnAnglePlus.Name = "btnAnglePlus";
            this.btnAnglePlus.Size = new System.Drawing.Size(35, 35);
            this.btnAnglePlus.TabIndex = 8;
            this.btnAnglePlus.Text = "+";
            this.btnAnglePlus.UseVisualStyleBackColor = true;
            this.btnAnglePlus.Click += new System.EventHandler(this.btnAnglePlus_Click);
            // 
            // trackBar1
            // 
            this.trackBar1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left)));
            this.trackBar1.LargeChange = 10;
            this.trackBar1.Location = new System.Drawing.Point(9, 145);
            this.trackBar1.Margin = new System.Windows.Forms.Padding(2);
            this.trackBar1.Maximum = 358;
            this.trackBar1.Name = "trackBar1";
            this.trackBar1.Orientation = System.Windows.Forms.Orientation.Vertical;
            this.trackBar1.Size = new System.Drawing.Size(45, 259);
            this.trackBar1.SmallChange = 2;
            this.trackBar1.TabIndex = 7;
            this.trackBar1.TickFrequency = 10;
            this.trackBar1.Scroll += new System.EventHandler(this.trackBar1_Scroll);
            // 
            // lblPointerAnle
            // 
            this.lblPointerAnle.Location = new System.Drawing.Point(8, 110);
            this.lblPointerAnle.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.lblPointerAnle.Name = "lblPointerAnle";
            this.lblPointerAnle.Size = new System.Drawing.Size(75, 28);
            this.lblPointerAnle.TabIndex = 6;
            this.lblPointerAnle.Text = "Pointer angle, deg: 0";
            // 
            // chkDrawWrongPoints
            // 
            this.chkDrawWrongPoints.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.chkDrawWrongPoints.AutoSize = true;
            this.chkDrawWrongPoints.Location = new System.Drawing.Point(9, 83);
            this.chkDrawWrongPoints.Margin = new System.Windows.Forms.Padding(2);
            this.chkDrawWrongPoints.Name = "chkDrawWrongPoints";
            this.chkDrawWrongPoints.Size = new System.Drawing.Size(90, 17);
            this.chkDrawWrongPoints.TabIndex = 10;
            this.chkDrawWrongPoints.Text = "Wrong Points";
            this.chkDrawWrongPoints.UseVisualStyleBackColor = true;
            // 
            // RadarPlotComponent
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.splitContainer1);
            this.Margin = new System.Windows.Forms.Padding(2);
            this.Name = "RadarPlotComponent";
            this.Size = new System.Drawing.Size(615, 415);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.splitContainer1.Panel1.ResumeLayout(false);
            this.splitContainer1.Panel2.ResumeLayout(false);
            this.splitContainer1.Panel2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).EndInit();
            this.splitContainer1.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.trackBar1)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion
        private System.Windows.Forms.ComboBox cmbRadiusList;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.CheckBox chkBlackMode;
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.SplitContainer splitContainer1;
        private System.Windows.Forms.Label lblPointerAnle;
        private System.Windows.Forms.TrackBar trackBar1;
        private System.Windows.Forms.Button btnAngleMinus;
        private System.Windows.Forms.Button btnAnglePlus;
        private System.Windows.Forms.CheckBox chkDrawWrongPoints;
    }
}
