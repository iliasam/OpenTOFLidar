namespace TDC_Testing_v1
{
    partial class CalibrationControl
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
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            this.btnSelectFile = new System.Windows.Forms.Button();
            this.btnOpenLastFile = new System.Windows.Forms.Button();
            this.openFileDialog1 = new System.Windows.Forms.OpenFileDialog();
            this.lblPointsNumber = new System.Windows.Forms.Label();
            this.panel1 = new System.Windows.Forms.Panel();
            this.button1 = new System.Windows.Forms.Button();
            this.lblMinDelay = new System.Windows.Forms.Label();
            this.chkRemoveDelayOffset = new System.Windows.Forms.CheckBox();
            this.richTextBoxResults = new System.Windows.Forms.RichTextBox();
            this.btnFitFunction = new System.Windows.Forms.Button();
            this.btnSendCoeffsToMCU = new System.Windows.Forms.Button();
            this.groupBox4.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBox4
            // 
            this.groupBox4.Controls.Add(this.btnSelectFile);
            this.groupBox4.Controls.Add(this.btnOpenLastFile);
            this.groupBox4.Location = new System.Drawing.Point(13, 10);
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.Size = new System.Drawing.Size(201, 68);
            this.groupBox4.TabIndex = 2;
            this.groupBox4.TabStop = false;
            this.groupBox4.Text = "Open";
            // 
            // btnSelectFile
            // 
            this.btnSelectFile.Location = new System.Drawing.Point(93, 25);
            this.btnSelectFile.Name = "btnSelectFile";
            this.btnSelectFile.Size = new System.Drawing.Size(93, 32);
            this.btnSelectFile.TabIndex = 1;
            this.btnSelectFile.Text = "Select File";
            this.btnSelectFile.UseVisualStyleBackColor = true;
            this.btnSelectFile.Click += new System.EventHandler(this.btnSelectFile_Click);
            // 
            // btnOpenLastFile
            // 
            this.btnOpenLastFile.Location = new System.Drawing.Point(9, 25);
            this.btnOpenLastFile.Name = "btnOpenLastFile";
            this.btnOpenLastFile.Size = new System.Drawing.Size(75, 32);
            this.btnOpenLastFile.TabIndex = 0;
            this.btnOpenLastFile.Text = "Last File";
            this.btnOpenLastFile.UseVisualStyleBackColor = true;
            this.btnOpenLastFile.Click += new System.EventHandler(this.btnOpenLastFile_Click);
            // 
            // openFileDialog1
            // 
            this.openFileDialog1.FileName = "openFileDialog1";
            // 
            // lblPointsNumber
            // 
            this.lblPointsNumber.AutoSize = true;
            this.lblPointsNumber.Location = new System.Drawing.Point(230, 22);
            this.lblPointsNumber.Name = "lblPointsNumber";
            this.lblPointsNumber.Size = new System.Drawing.Size(147, 17);
            this.lblPointsNumber.TabIndex = 3;
            this.lblPointsNumber.Text = "Number of points: N/A";
            // 
            // panel1
            // 
            this.panel1.BackColor = System.Drawing.SystemColors.ActiveCaption;
            this.panel1.Location = new System.Drawing.Point(14, 97);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(950, 484);
            this.panel1.TabIndex = 4;
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(787, 7);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(93, 32);
            this.button1.TabIndex = 5;
            this.button1.Text = "Redraw";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // lblMinDelay
            // 
            this.lblMinDelay.AutoSize = true;
            this.lblMinDelay.Location = new System.Drawing.Point(230, 45);
            this.lblMinDelay.Name = "lblMinDelay";
            this.lblMinDelay.Size = new System.Drawing.Size(99, 17);
            this.lblMinDelay.TabIndex = 6;
            this.lblMinDelay.Text = "Min delay: N/A";
            // 
            // chkRemoveDelayOffset
            // 
            this.chkRemoveDelayOffset.AutoSize = true;
            this.chkRemoveDelayOffset.Checked = true;
            this.chkRemoveDelayOffset.CheckState = System.Windows.Forms.CheckState.Checked;
            this.chkRemoveDelayOffset.Location = new System.Drawing.Point(1015, 10);
            this.chkRemoveDelayOffset.Name = "chkRemoveDelayOffset";
            this.chkRemoveDelayOffset.Size = new System.Drawing.Size(164, 21);
            this.chkRemoveDelayOffset.TabIndex = 7;
            this.chkRemoveDelayOffset.Text = "Remove Delay Offset";
            this.chkRemoveDelayOffset.UseVisualStyleBackColor = true;
            // 
            // richTextBoxResults
            // 
            this.richTextBoxResults.Location = new System.Drawing.Point(980, 60);
            this.richTextBoxResults.Name = "richTextBoxResults";
            this.richTextBoxResults.Size = new System.Drawing.Size(204, 167);
            this.richTextBoxResults.TabIndex = 9;
            this.richTextBoxResults.Text = "";
            // 
            // btnFitFunction
            // 
            this.btnFitFunction.Location = new System.Drawing.Point(886, 7);
            this.btnFitFunction.Name = "btnFitFunction";
            this.btnFitFunction.Size = new System.Drawing.Size(93, 32);
            this.btnFitFunction.TabIndex = 10;
            this.btnFitFunction.Text = "Fit";
            this.btnFitFunction.UseVisualStyleBackColor = true;
            this.btnFitFunction.Click += new System.EventHandler(this.btnFitFunction_Click);
            // 
            // btnSendCoeffsToMCU
            // 
            this.btnSendCoeffsToMCU.Location = new System.Drawing.Point(1015, 248);
            this.btnSendCoeffsToMCU.Name = "btnSendCoeffsToMCU";
            this.btnSendCoeffsToMCU.Size = new System.Drawing.Size(169, 32);
            this.btnSendCoeffsToMCU.TabIndex = 11;
            this.btnSendCoeffsToMCU.Text = "Sent Coeff. to MCU";
            this.btnSendCoeffsToMCU.UseVisualStyleBackColor = true;
            this.btnSendCoeffsToMCU.Click += new System.EventHandler(this.btnSendCoeffsToMCU_Click);
            // 
            // CalibrationControl
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.btnSendCoeffsToMCU);
            this.Controls.Add(this.btnFitFunction);
            this.Controls.Add(this.richTextBoxResults);
            this.Controls.Add(this.chkRemoveDelayOffset);
            this.Controls.Add(this.lblMinDelay);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.lblPointsNumber);
            this.Controls.Add(this.groupBox4);
            this.Name = "CalibrationControl";
            this.Size = new System.Drawing.Size(1200, 600);
            this.groupBox4.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBox4;
        private System.Windows.Forms.Button btnSelectFile;
        private System.Windows.Forms.Button btnOpenLastFile;
        private System.Windows.Forms.OpenFileDialog openFileDialog1;
        private System.Windows.Forms.Label lblPointsNumber;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Label lblMinDelay;
        private System.Windows.Forms.CheckBox chkRemoveDelayOffset;
        private System.Windows.Forms.RichTextBox richTextBoxResults;
        private System.Windows.Forms.Button btnFitFunction;
        private System.Windows.Forms.Button btnSendCoeffsToMCU;
    }
}
