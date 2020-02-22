using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
using OxyPlot.WindowsForms;
using OxyPlot;
using OxyPlot.Series;
using OxyPlot.Axes;
using Accord.Math;
using Accord.Math.Optimization;
using Accord.Statistics.Models.Regression.Fitting;
using OxyPlot.Annotations;

namespace TDC_Testing_v1
{
    public partial class CalibrationControl : UserControl
    {
        public struct FunctionParamsStruct
        {
            public double a;
            public double b;
            public double BeginX;
            public double EndX;
        }

        // Current coefficients
        FunctionParamsStruct FunctionFarams;

        public Action UpdateLastFileName;
        public string CalibLastFileName = "";
        /// <summary>
        /// Min from position_bin
        /// </summary>
        double MinimalDelayBin = 0.0;

        double MinWidthBin = 0.0;
        double MaxWidthBin = 0.0;

        double MarkerWidthStart = 300;//x - start of the function fit

        List<DataRecordingClass.RecordingPoint> LoadedPoints;

        PlotView plot = new PlotView();
        LineSeries functionSeries;
        ScatterSeries dataSeries;

        public Action<FunctionParamsStruct> UpdateFunctionParams;
        public Action<FunctionParamsStruct> SendParamsToMCU;

        public CalibrationControl()
        {
            InitializeComponent();
            InitChart();
        }

        void ProcessFileData(string path)
        {
            LoadedPoints = new List<DataRecordingClass.RecordingPoint>();
            MinimalDelayBin = 10000;//not very good
            MinWidthBin = 10000;
            MaxWidthBin = 0;

            StreamReader reader = new StreamReader(path);
            reader.ReadLine();//skip header
            string line;
            while ((line = reader.ReadLine()) != null)
            {
                string[] values = line.Split(';');
                if (values.Length == 5)
                {
                    DataRecordingClass.RecordingPoint point = new DataRecordingClass.RecordingPoint();
                    point.position_bin = Convert.ToDouble(values[0]);
                    point.position_std_bin = Convert.ToDouble(values[1]);
                    point.width_bin = Convert.ToDouble(values[3]);
                    point.width_std_bin = Convert.ToDouble(values[4]);

                    //check if point have good signal
                    if ((point.position_std_bin > 0.01) && (point.position_std_bin < 20) && (point.width_std_bin > 0.1))
                    {
                        LoadedPoints.Add(point);
                        if (point.position_bin < MinimalDelayBin)
                            MinimalDelayBin = point.position_bin;
                        if (point.width_bin < MinWidthBin)
                            MinWidthBin = point.width_bin;
                        if (point.width_bin > MaxWidthBin)
                            MaxWidthBin = point.width_bin;
                    }
                }
            }
            lblPointsNumber.Text = $"Number of points: {LoadedPoints.Count}";
            lblMinDelay.Text = $"Min delay: {MinimalDelayBin} bin";
        }


        //GUI *********************************************************

        private void btnOpenLastFile_Click(object sender, EventArgs e)
        {
            UpdateLastFileName.Invoke();
            if (CalibLastFileName == "")
                return;

            string path = Application.StartupPath + $"\\{CalibLastFileName}";
            ProcessFileData(path);
            UpdateChart();
        }

        private void btnSelectFile_Click(object sender, EventArgs e)
        {
            string path = "";
            openFileDialog1.Filter = "CSV|*.csv";
            if (openFileDialog1.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                path = openFileDialog1.FileName;
                ProcessFileData(path);
                UpdateChart();

            }
            else
            {
                MessageBox.Show("Impossible to open file: " + path, "ERROR!", 0, System.Windows.Forms.MessageBoxIcon.Stop);
            }
        }

        void InitChart()
        {
            var model = new PlotModel { Title = "Calibration" };
            model.PlotType = PlotType.XY;

            var leftAxis = new LinearAxis();
            leftAxis.Position = AxisPosition.Left;
            leftAxis.Title = "Signal Delay, bin";
            model.Axes.Add(leftAxis);

            var downAxis = new LinearAxis();
            downAxis.Position = AxisPosition.Bottom;
            downAxis.Title = "Pulse width, bin";
            model.Axes.Add(downAxis);

            dataSeries = new ScatterSeries()
            {
                Title = "Data",
                MarkerType = MarkerType.Cross,
                MarkerStrokeThickness = 1,
                BinSize = 1,
                MarkerStroke = OxyColors.Blue,
                MarkerSize = 2,
            };

            functionSeries = new LineSeries()
            {
                Title = "Function",
                Color = OxyColors.Red,
            };

            model.Series.Add(dataSeries);
            model.Series.Add(functionSeries);

            var _lineAnnotation = new LineAnnotation
            {
                Text = "Fit Start",
                Type = LineAnnotationType.Vertical,
                X = 300
            };
            _lineAnnotation.MouseDown += (s, e) =>
            {
                if (e.ChangedButton != OxyMouseButton.Left)
                    return;

                _lineAnnotation.StrokeThickness *= 5;
                model.InvalidatePlot(false);
                e.Handled = true;
            };

            // Handle mouse movements (note: this is only called when the mousedown event was handled)
            _lineAnnotation.MouseMove += (s, e) =>
            {
                MarkerWidthStart = _lineAnnotation.InverseTransform(e.Position).X;
                _lineAnnotation.X = MarkerWidthStart;
                model.InvalidatePlot(false);
                e.Handled = true;
            };
            _lineAnnotation.MouseUp += (s, e) =>
            {
                _lineAnnotation.StrokeThickness /= 5;
                model.InvalidatePlot(false);
                e.Handled = true;
            };
            model.Annotations.Add(_lineAnnotation);

            plot.Model = model;
            plot.Dock = System.Windows.Forms.DockStyle.Fill;
            plot.Location = new System.Drawing.Point(0, 0);
            plot.TabIndex = 0;
            plot.Model.Background = OxyColor.FromRgb(255, 255, 255);        

            panel1.Controls.Add(plot);
        }

        void UpdateChart()
        {
            if (LoadedPoints.Count == 0)
                return;
            foreach (var ax in plot.Model.Axes)
                ax.Maximum = ax.Minimum = Double.NaN;
            plot.Model.ResetAllAxes();

            dataSeries.Points.Clear();
            for (int i = 0; i < LoadedPoints.Count; i++)
            {
                DataRecordingClass.RecordingPoint point = LoadedPoints[i];
                if (chkRemoveDelayOffset.Checked)
                    point.position_bin = point.position_bin - MinimalDelayBin;//y axis
                dataSeries.Points.Add(new ScatterPoint(point.width_bin, point.position_bin));
            }
            plot.InvalidatePlot(true);

            /*
            plot.Model.ResetAllAxes();
            foreach (var axis in plot.Model.Axes)
                axis.Reset();
                */


            plot.Refresh();
        }

        void DrawFunction()
        {
            if (FunctionFarams.EndX < 0.1)
                return;

            functionSeries.Points.Clear();
            for (double x = FunctionFarams.BeginX; x < FunctionFarams.EndX; x += 10)
            {
                double y = Math.Exp((FunctionFarams.a - x) / FunctionFarams.b);
                functionSeries.Points.Add(new DataPoint(x, y));
            }
            plot.Refresh();
        }

        void FitFunction(double StartWidth, double StopWidth)
        {
            //Select points by given range
            List<DataRecordingClass.RecordingPoint> tmpPoints = new List<DataRecordingClass.RecordingPoint>();
            foreach (var item in LoadedPoints)
            {
                if ((item.width_bin >= StartWidth) && (item.width_bin <= StopWidth))
                    tmpPoints.Add(item);
            }


            double[,] pointsData = new double[tmpPoints.Count, 2];
            
            for (int i = 0; i < tmpPoints.Count; i++)
            {
                pointsData[i, 0] = tmpPoints[i].width_bin;//X
                pointsData[i, 1] = tmpPoints[i].position_bin - MinimalDelayBin;//Y
            }

            // Extract inputs and outputs
            double[][] inputs = pointsData.GetColumn(0).ToJagged();
            double[] outputs = pointsData.GetColumn(1);

            // Create a Nonlinear regression using 
            var nls = new NonlinearLeastSquares()
            {
                NumberOfParameters = 2,

                // Initialize to some values
                StartValues = new[] {400.0, 50.0},

                Function = (w, x) => Math.Exp((w[0] - x[0]) / w[1]),

                //https://www.wolframalpha.com/input/?i=diff+ax²+%2B+bx+%2B+c+w.r.t.+b
                Gradient = (w, x, r) =>
                {
                    r[0] = Math.Exp(w[0] / w[1] - x[0] / w[1]) / w[1];
                    r[1] = -((w[0] - x[0]) * Math.Exp(w[0] / w[1] - x[0] / w[1]))/ (w[1] * w[1]);
                },

                Algorithm = new LevenbergMarquardt()
                {
                    MaxIterations = 500,
                    Tolerance = 1e-4
                }
            };

            var regression = nls.Learn(inputs, outputs);

            FunctionFarams.a = regression.Coefficients[0];
            FunctionFarams.b = regression.Coefficients[1];
            FunctionFarams.BeginX = pointsData[0, 0];
            FunctionFarams.EndX = pointsData[pointsData.Length / 2 - 1, 0];


            richTextBoxResults.Clear();
            richTextBoxResults.Text += $"Begin X: {FunctionFarams.BeginX:0.0}\r\n";
            richTextBoxResults.Text += $"End X: {FunctionFarams.EndX:0.0}\r\n";
            richTextBoxResults.Text += $"Coeff A: {FunctionFarams.a:0.0000} +- {regression.StandardErrors[0]:0.0}\r\n";
            richTextBoxResults.Text += $"Coeff B: {FunctionFarams.b:0.0000} +- {regression.StandardErrors[1]:0.0}\r\n";
        }//end

        private void button1_Click(object sender, EventArgs e)
        {
            UpdateChart();   
        }

        private void btnFitFunction_Click(object sender, EventArgs e)
        {
            FitFunction(MarkerWidthStart, MaxWidthBin);
            DrawFunction();
            UpdateFunctionParams?.Invoke(FunctionFarams);
        }

        private void btnSendCoeffsToMCU_Click(object sender, EventArgs e)
        {
            SendParamsToMCU?.Invoke(FunctionFarams);
        }
    }//end of class
}
