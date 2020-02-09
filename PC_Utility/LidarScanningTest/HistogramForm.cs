using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace LidarScanningTest1
{
    public partial class HistogramForm : Form
    {
        //distances in cm
        FixedSizedQueue<int> HistFIFO;

        const int DEFAULT_FIFO_LENGTH = 20;

        public HistogramForm()
        {
            InitializeComponent();

            HistFIFO = new FixedSizedQueue<int>();
            HistFIFO.Limit = DEFAULT_FIFO_LENGTH;
        }

        public void AddNewDisatnceValue(double ValueMeters)
        {
            int average_cm = 0;

            if (this.Disposing || this.IsDisposed)
                return;

            if (ValueMeters < 0.05)
                return;

            HistFIFO.Enqueue((int)(ValueMeters * 100));

            int[] data_buf = HistFIFO.q.ToArray();

            if (data_buf.Length < DEFAULT_FIFO_LENGTH)
                return;

            average_cm = (int)FindAverage(ref data_buf);

            UpdateHistogram(average_cm, data_buf);

            int min_dist = data_buf.Min();
            int max_dist = data_buf.Max();

            lblAVRValue.Text = $"Average Distance: {average_cm} cm";

            int min_max = max_dist - min_dist;
            lblMaxMIn.Text = $"MaxMin: {min_max} cm / ±{min_max/2} cm";

            double sdtDevCm = FindStandardDev(ref data_buf);
            lblStdDev.Text = $"STD DEV: ±{sdtDevCm:0.0} cm";
        }


        /// <summary>
        /// Update "Start" Histogram
        /// </summary>
        /// <param name="avrValue">Average value of "Start" values - center of Histogram</param>
        void UpdateHistogram(int avrValue, int[] data_buf)
        {
            const int histSize = 32;
            UInt16[] histogramData = new ushort[histSize];
            chart1.Series["Series1"].Points.Clear();

            chart1.ChartAreas[0].AxisX.Minimum = -histSize / 2;
            chart1.ChartAreas[0].AxisX.Maximum = histSize / 2;
            chart1.ChartAreas[0].AxisX.Interval = 2;

            for (int i = 0; i < data_buf.Length; i++)
            {
                int curValue = data_buf[i];
                int curPosition = (histSize / 2 - 1) + (curValue - avrValue);
                if ((curPosition >= 0) && (curPosition < histSize))
                {
                    histogramData[curPosition]++;
                }
            }

            for (int i = 0; i < histSize; i++)
            {
                chart1.Series["Series1"].Points.AddXY(i - (histSize / 2), histogramData[i]);
            }
        }


        public void SetLength(int length)
        {
            if (length < 1)
                return;

            HistFIFO.Limit = length;
        }

        public double FindStandardDev(ref int[] arr)
        {
            double summ_derivation = 0;
            int i;

            double averageValue = FindAverage(ref arr);

            for (i = 0; i < arr.Length; i++)
                summ_derivation += Math.Pow(((double)averageValue - (double)arr[i]), 2);
            summ_derivation = summ_derivation / (arr.Length - 1);

            return Math.Sqrt(summ_derivation);
        }

        public double FindAverage(ref int[] arr)
        {
            int i;
            Int64 summ_avr = 0;
            for (i = 0; i < arr.Length; i++)
                summ_avr += (Int64)arr[i];

            double avr = (double)summ_avr / (double)arr.Length;
            return avr;
        }

        private void nudScansNumber_ValueChanged(object sender, EventArgs e)
        {
            SetLength((int)nudScansNumber.Value);
        }
    }//end of class
}
