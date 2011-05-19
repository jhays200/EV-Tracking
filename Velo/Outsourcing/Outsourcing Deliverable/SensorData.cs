using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Telemetry
{
    public class SensorData
    {
        public string deviceID;
        public string sensorID;
        public string data;
        public DateTime timeStamp;
        public int errorcount;

        public SensorData()
        {
        }

        public static Comparison<SensorData> timeComparison = delegate(SensorData s1, SensorData s2)
        {
            return s1.timeStamp.CompareTo(s2.timeStamp);
        };

        public static List<SensorData> telemetryWindow(List<SensorData> inData, DateTime startDate, DateTime endDate, int dataCount)
        {
            List<SensorData> outData = new List<SensorData>(dataCount);
            if (dataCount > 0)
            {
                if (inData.Count < 2)
                    throw new ArgumentException("Too few points", "inData");
                double[] x = new double[inData.Count], y = new double[inData.Count];
                DateTime origin = inData.Min(s => s.timeStamp);
                for (int i = 0; i < inData.Count; i++)
                {
                    SensorData s = inData[i];
                    x[i] = (s.timeStamp - origin).TotalSeconds;
                    y[i] = double.Parse(s.data);
                }
                Array.Sort(x, y);
                Spline spline = new Spline(x, y);
                if (dataCount > 1)
                {
                    double step = (endDate - startDate).TotalSeconds / (dataCount - 1);

                    for (int i = 0; i < dataCount; i++)
                    {
                        SensorData s = new SensorData();
                        s.timeStamp = startDate + TimeSpan.FromSeconds(i * step);
                        s.data = spline[(s.timeStamp - origin).TotalSeconds].ToString();
                        outData.Add(s);
                    }
                }
                else
                {
                    SensorData s = new SensorData();
                    s.timeStamp = startDate + TimeSpan.FromSeconds((endDate - startDate).TotalSeconds /2);
                    s.data = spline[(s.timeStamp - origin).TotalSeconds].ToString();
                    outData.Add(s);
                }
            }
            return outData;
        }
    }

    public class Spline
    {
        struct Coef
        {
            public double A;
            public double B;
            public double C;
            public double D;
            public double X;
        }

        Coef[] coef;
        public Spline(double[] x, double[] y)
        {
            if (x.Length != y.Length)
                throw new ArgumentException("Array lengths must be equal");
            if(x.Length<2)
                throw new ArgumentException("Spline needs at least two points to be built");
            if (x.Length < 3)
            {
                //Take the average in the the case of 2 points - we really need 3 points
                Array.Resize(ref x, 3);
                x[2] = x[1];
                x[1] = (x[0] + x[2]) / 2.0;
                Array.Resize(ref y, 3);
                y[2] = y[1];
                y[1] = (y[0] + y[2]) / 2.0;
            }

            int count = x.Length;

            double[] alpha = new double[count - 1], beta = new double[count - 1];
            coef = new Coef[count];
            int i = 0;
            for (i = 0; i < count; i++)
            {
                coef[i].X = x[i];
                coef[i].A = y[i];
            }

            double h_i, h_i1, lkA, lkB, lkC, lkF, lkz;
            for (i = 1; i < count - 1; i++)
            {
			    h_i = x[i] - x[i - 1];
			    h_i1 = x[i + 1] - x[i];
			    lkA = h_i;
			    lkC = 2 * (h_i + h_i1);
			    lkB = h_i1;
			    lkF = 6 * ((y[i + 1] - y[i]) / h_i1 - (y[i] - y[i - 1]) / h_i);
			    lkz = (lkA * alpha[i - 1] + lkC);
			    alpha[i] = -lkB / lkz;
                beta[i] = (lkF - lkA * beta[i - 1]) / lkz;
            }

            for (i = count - 2; i >= 0; i--)
                coef[i].C = alpha[i] * coef[i + 1].C + beta[i];

            for (i = count - 1; i >= 1; i--)
            {
       			h_i = x[i] - x[i - 1];
                coef[i].D = (coef[i].C - coef[i - 1].C) / h_i;
                coef[i].B = h_i * (2 * coef[i].C + coef[i - 1].C) / 6 + (y[i] - y[i - 1]) / h_i;
            }
        }

        public double this[double x]
        {
            get 
            {
                int count = coef.Length;
                int node = 0;
                if (x > coef[0].X)
                {
                    node = count - 1;
                    if (x < coef[count - 1].X)
                    {
                        int i = 0, k;
                        while (i + 1 < node)
                        {
                            k = i + (node - i) / 2;
                            if (x <= coef[k].X)
                                node = k;
                            else
                                i = k;
                        }
                    }
                }

                Coef S = coef[node];
                double dx = x - S.X;
                return S.A + (S.B + (S.C / 2 + S.D * dx / 6) * dx) * dx;
            }
        }

    }
}
