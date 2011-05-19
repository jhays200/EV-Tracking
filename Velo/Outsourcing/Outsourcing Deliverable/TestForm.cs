using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace Telemetry
{
    public partial class TestForm : Form
    {
        public TestForm()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {

            //Generate 20 random points of Sensor data
            
            Random rnd = new Random();

            DateTime start = DateTime.Now;
            DateTime point = start;

            int inPoints = 20;
            List<SensorData> inData = new List<SensorData>(inPoints);
            for (int i = 0; i < inPoints; i++)
            {
                SensorData s = new SensorData();
                s.timeStamp = point;
                s.data = Math.Round((10 * rnd.NextDouble())).ToString();
                inData.Add(s);
                point += TimeSpan.FromSeconds(1.0 + rnd.Next(3));
            }

            DateTime end = inData[inData.Count - 1].timeStamp; //last measurement time

            // Generate 200 window points
            int pointCount = 200;
            List<SensorData> outData = SensorData.telemetryWindow(inData, start, end, pointCount);


            #region Drawing
            Bitmap bmp = new Bitmap(graph.Width, graph.Height);

            float seconds = (float)Math.Ceiling((end - start).TotalSeconds); //time interval in seconds
            float minVal = (float)Math.Floor(Math.Min(
                inData.Min(s => double.Parse(s.data)),
                outData.Min(s => double.Parse(s.data))
                ));
            float maxVal = (float)Math.Ceiling(Math.Max(
                inData.Max(s => double.Parse(s.data)),
                outData.Max(s => double.Parse(s.data))
                ));
            float vals = Math.Abs(maxVal - minVal);

            Graphics g = Graphics.FromImage(bmp);
            g.Clear(Color.White);

            for (float x = 0; x <= seconds; x++)
                for (float y = 0; y <= vals; y++)
                {
                    g.DrawLine(Pens.LightGray,
                        new PointF(x * (graph.Width / seconds), 0),
                        new PointF(x * (graph.Width / seconds), graph.Height));
                    g.DrawLine(Pens.LightGray,
                        new PointF(0, y * (graph.Height / vals)),
                        new PointF(graph.Width, y * (graph.Height / vals)));
                }

            foreach (SensorData s in inData)
            {
                float x = (float)(s.timeStamp - start).TotalSeconds * (graph.Width / seconds);
                float y = (-minVal + (float)double.Parse(s.data)) * (graph.Height / vals);
                g.FillEllipse(Brushes.Green, x - 4f, y - 4f, 8f, 8f);
            }

            using (Pen pen = new Pen(Color.Blue, 2f))
            {
                bool prev = false;
                float prev_x = 0, prev_y = 0;
                foreach (SensorData s in outData)
                {
                    float x = (float)(s.timeStamp - start).TotalSeconds * (graph.Width / seconds);
                    float y = (-minVal + (float)double.Parse(s.data)) * (graph.Height / vals);
                    if (prev)
                        g.DrawLine(pen,
                            new PointF(prev_x, prev_y),
                            new PointF(x, y));

                    prev_x = x;
                    prev_y = y;
                    prev = true;
                }
            }
            g.DrawRectangle(Pens.Black, 0, 0, graph.Width - 1, graph.Height - 1);

            graph.Image = bmp;
            #endregion
        }
    }
}
