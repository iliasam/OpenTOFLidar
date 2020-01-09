using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TDC_Testing_v1
{
    class DataProcesingClass
    {
        public double FindAverage(ref int[] arr)
        {
            int i;
            Int64 summ_avr = 0;
            for (i = 0; i < arr.Length; i++)
                summ_avr += (Int64)arr[i];

            double avr = (double)summ_avr / (double)arr.Length;
            return avr;
        }

        public double FindAverage(ref double[] arr)
        {
            int i;
            double summ_avr = 0;
            for (i = 0; i < arr.Length; i++)
                summ_avr += arr[i];

            double avr = summ_avr / (double)arr.Length;
            return avr;
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
    }
}
