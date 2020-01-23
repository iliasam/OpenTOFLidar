using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace LidarScanningTest1
{
    public partial class RadarPlotComponent : UserControl
    {
        int BoxWidth = 400;

        Bitmap img;
        Graphics g;

        int curentRadius = 350;//in cm

        // Radar rotation in deg
        int RadarRotaton = 0;

        int StartLineAngle = 0;
        int StopLineAngle = 0;

        public RadarPlotComponent()
        {
            InitializeComponent();

            cmbRadiusList.Items.Add((double)3.5);
            cmbRadiusList.Items.Add((double)1.0);
            cmbRadiusList.Items.Add((double)4.0);
            cmbRadiusList.Items.Add((double)5.0);
            cmbRadiusList.Items.Add((double)8.0);
            cmbRadiusList.Items.Add((double)10.0);
            cmbRadiusList.Items.Add((double)20.0);
            cmbRadiusList.Items.Add((double)30.0);
            cmbRadiusList.Items.Add((double)40.0);
            cmbRadiusList.SelectedIndex = 0;
        }

        public void DrawRadar(RadarPoint[] points, int pointsCnt, int angularCorr = 0)
        {
            int i = 0;

            BoxWidth = GetImageSize();
            img = new Bitmap(BoxWidth, BoxWidth);

            Pen linesPen;
            Pen wrongPointsPen;

            Pen yellowPen = new System.Drawing.Pen(Color.FromArgb(200, 255, 255, 0), 2);
            Pen blackPen = new System.Drawing.Pen(Color.FromArgb(255, 0, 0, 0), 2);//black
            Pen redPen = new System.Drawing.Pen(Color.FromArgb(255, 255, 0, 0), 3);

            g = Graphics.FromImage(img);

            g.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.AntiAlias;
            if (chkBlackMode.Checked)
            {
                linesPen = new System.Drawing.Pen(Color.LightGray, 1);
                wrongPointsPen = new System.Drawing.Pen(Color.Blue, 3);
                g.FillRectangle(new SolidBrush(Color.FromArgb(0, 0, 0)), 0, 0, BoxWidth, BoxWidth);
            }
            else
            {
                linesPen = new System.Drawing.Pen(Color.BlueViolet, 1);
                wrongPointsPen = redPen;
                g.FillRectangle(new SolidBrush(Color.FromArgb(0, 0, 200)), 0, 0, BoxWidth, BoxWidth);
            }

            //main lines
            g.DrawLine(linesPen, 0, BoxWidth / 2, BoxWidth, BoxWidth / 2);
            g.DrawLine(linesPen, BoxWidth / 2, 0, BoxWidth / 2, BoxWidth);

            if (cmbRadiusList.SelectedItem != null)
                curentRadius = (int)((double)cmbRadiusList.SelectedItem * 100);//to cm

            UInt16 circleStep = 100;//cm
            if (curentRadius > 500)
                circleStep = 300;

            for (UInt16 radius = 100; radius <= curentRadius; radius += circleStep)
            {
                DrawCircle(g, linesPen, BoxWidth / 2 * radius / curentRadius);
            }

            
            //Scan points
            for (i = 0; i < pointsCnt; i++)
            {
                if (points[i].NotVisible == false)
                    DrawXYPoint(yellowPen, points[i].x, points[i].y);

                if (chkDrawWrongPoints.Checked && points[i].Wrong)
                {
                    DrawWrongPoint(wrongPointsPen, points[i].angleDeg);
                }
            }

            int angle = trackBar1.Value;
            DrawCenterdLine(yellowPen, angle + angularCorr);

            DrawCenterdLine(redPen, StartLineAngle + angularCorr);
            DrawCenterdLine(redPen, StopLineAngle + angularCorr);

            pictureBox1.Image = img;
        }

        //radius - in pixels
        void DrawCircle(Graphics g, Pen curPen, int radius)
        {
            g.DrawEllipse(curPen, BoxWidth / 2 - radius, BoxWidth / 2 - radius, radius * 2, radius * 2);
        }

        /// <summary>
        /// Draw oint
        /// </summary>
        /// <param name="curPen"></param>
        /// <param name="x">Position in meters</param>
        /// <param name="y">Position in meters</param>
        void DrawXYPoint(Pen curPen, double x, double y)
        {
            double xx;
            double yy;

            xx = x / (((double)curentRadius / 100)) * ((double)(BoxWidth / 2));
            yy = y / (((double)curentRadius / 100)) * ((double)(BoxWidth / 2));

            g.DrawEllipse(curPen, (float)(BoxWidth / 2 + xx), (float)(BoxWidth / 2 - yy), 1 * 2, 1 * 2);
        }

        /// <summary>
        ///  Draw a line going from image center
        /// </summary>
        /// <param name="curPen"></param>
        /// <param name="angleDeg"></param>
        void DrawCenterdLine(Pen curPen, double angleDeg)
        {
            float length = 1000;//cm

            float x_start = (float)(BoxWidth / 2);
            float y_start = (float)(BoxWidth / 2);

            angleDeg += (90 + RadarRotaton);

            float angle_rad = (float)(angleDeg * Math.PI / 180);
            float x_end = (float)(length * Math.Cos(angle_rad));
            float y_end = (float)(length * Math.Sin(angle_rad));

            x_end = x_end / (((float)curentRadius / 100)) * ((float)(BoxWidth / 2));//pixels from center
            y_end = y_end / (((float)curentRadius / 100)) * ((float)(BoxWidth / 2));//pixels from center

            x_end = x_start + x_end;
            y_end = y_start - y_end;

            g.DrawLine(curPen, x_start, y_start, x_end, y_end);
        }

        /// <summary>
        ///  Draw a line going from image center
        /// </summary>
        /// <param name="curPen"></param>
        /// <param name="angleDeg"></param>
        void DrawWrongPoint(Pen curPen, double angleDeg)
        {
            float length = BoxWidth * 0.95f / 2;//pixels

            float x_start = (float)(BoxWidth / 2);
            float y_start = (float)(BoxWidth / 2);

            float angle_rad = (float)(angleDeg * Math.PI / 180);
            float x_end = (float)(length * Math.Cos(angle_rad));
            float y_end = (float)(length * Math.Sin(angle_rad));

            x_end = x_start + x_end;
            y_end = y_start - y_end;

            g.DrawEllipse(curPen, x_end, y_end, 1 * 2, 1 * 2);
        }

        int GetImageSize()
        {
            int height = pictureBox1.Height;
            int width = pictureBox1.Width;

            int min_val = Math.Min(height, width);
            return min_val;
        }

        private void trackBar1_Scroll(object sender, EventArgs e)
        {
            int angle = trackBar1.Value;
            lblPointerAnle.Text = "Pointer angle, deg: " + angle.ToString();
        }

        /// <summary>
        /// Return value of target line in degrees
        /// </summary>
        /// <returns>Return value in degrees</returns>
        public int GetPointerAngle()
        {
            int angle = trackBar1.Value;
            return angle;
        }

        public void SetRadarRotation(int rotation_deg)
        {
            RadarRotaton = rotation_deg;
        }

        public void UpdateStartStopLines(int startAngle, int stopAngle)
        {
            StartLineAngle = startAngle;
            StopLineAngle = stopAngle;
        }

        private void btnAnglePlus_Click(object sender, EventArgs e)
        {
            if (trackBar1.Value < trackBar1.Maximum)
                trackBar1.Value++;
            lblPointerAnle.Text = "Pointer angle, deg: " + trackBar1.Value.ToString();
        }

        private void btnAngleMinus_Click(object sender, EventArgs e)
        {
            if (trackBar1.Value > trackBar1.Minimum)
                trackBar1.Value--;
            lblPointerAnle.Text = "Pointer angle, deg: " + trackBar1.Value.ToString();
        }
    }
}
