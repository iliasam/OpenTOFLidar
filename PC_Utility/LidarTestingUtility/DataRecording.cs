using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace TDC_Testing_v1
{
    class DataRecordingClass
    {
        public struct RecordingPoint
        {
            public double position_bin;//average
            public double position_std_bin;//std dev
            public int position_max_min_bin;

            public double width_bin;//average
            public double width_std_bin;//std dev
        }

        public bool RecordingEnabled = false;
        public string LastFileName = "";

        List<RecordingPoint> recordingPoints;

        //*********************************************************

        public void AddPoint(RecordingPoint point)
        {
            if (RecordingEnabled)
            {
                recordingPoints.Add(point);
            }
        }

        public void StartRecording()
        {
            recordingPoints = new List<RecordingPoint>();
            RecordingEnabled = true;
        }

        public void StopRecording()
        {
            RecordingEnabled = false;
            ProcessRecData();
        }

        public int GetRecordePoints()
        {
            if (recordingPoints == null)
                return 0;
            return recordingPoints.Count;
        }

        void ProcessRecData()
        {
            //sort by pulse width 
            List<RecordingPoint> SortedPoints = recordingPoints.OrderBy(o => o.width_bin).ToList();

            LastFileName = $"result_{ DateTime.Now.ToString("yyyy-MM-dd HH-mm-ss")}.csv";

            string save_path = Application.StartupPath + $"\\{LastFileName}";
            StreamWriter outfile = new StreamWriter(save_path);

            //header
            outfile.WriteLine("POS;POS_STD_DEV;POS_DIFF;WIDTH;WIDTH_STD_DEV");
            foreach (var item in SortedPoints)
            {
                string str = "";
                str += $"{item.position_bin:0.00};{item.position_std_bin:0.00};{item.position_max_min_bin};";
                str += $"{item.width_bin:0.00};{item.width_std_bin:0.00}";
                outfile.WriteLine(str);
            }
            outfile.Close();
        }



    }//end of class
}
