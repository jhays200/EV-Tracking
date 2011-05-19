<%@ WebHandler Language="C#" Class="Handler" %>

using System;
using System.Web;
using System.Xml;
using System.Collections.Generic;

public class Handler : IHttpHandler
{
    public void ProcessRequest(HttpContext context)
    {
        context.Response.ContentType = "text/xml";        
        XmlWriter update = XmlWriter.Create(context.Response.OutputStream);
        update.WriteStartDocument();
        update.WriteStartElement("chart");

        string[] tempDeviceSensor = ((string)context.Request.Params["deviceName"]).Split(',');
        string deviceName = tempDeviceSensor[0];
        string sensorName = tempDeviceSensor[1];

        bool realTime;

        DateTime startDate = DateTime.Now;
        DateTime endDate = DateTime.Now;

        if (tempDeviceSensor[2] == "0")
        {
            realTime = true;
        }
        else
        {
            realTime = false;

            startDate = DateTime.Parse(tempDeviceSensor[2]);
            endDate = DateTime.Parse(tempDeviceSensor[3]);
        }
        
        List<SensorData> dataCollection;
        List<string[]> sensorData = new List<string[]>();

        dataCollection = PersistanceLayer.GetSensorData(deviceName, sensorName, 100, true, DateTime.Now - TimeSpan.FromMinutes(30), DateTime.Now);

        if (dataCollection.Count > 1)
        {
            dataCollection = SensorData.telemetryWindow(dataCollection, (DateTime.Now - TimeSpan.FromMinutes(30)).ToUniversalTime(), DateTime.Now.ToUniversalTime(), 30);
        }
        
        //For the first update write all the params
        //TODO: Pull this from database
        if (context.Request.Params["update"] == null)
        {            
            update.WriteStartElement("axis_ticks");
            update.WriteAttributeString("value_ticks", "true");
            update.WriteAttributeString("category_ticks", "true");
            update.WriteAttributeString("major_thickness", "2");
            update.WriteAttributeString("minor_thickness", "1");
            update.WriteAttributeString("minor_count", "3");
            update.WriteAttributeString("major_color", "49B8A7");
            update.WriteAttributeString("minor_color", "BADBD6");
            update.WriteAttributeString("position", "outside");
            update.WriteEndElement();

            update.WriteStartElement("chart_grid_h");
            update.WriteAttributeString("alpha", "50");
            update.WriteEndElement();

            update.WriteStartElement("chart_grid_v");
            update.WriteAttributeString("alpha", "50");
            update.WriteEndElement();

            update.WriteElementString("chart_type", "area");
           
            update.WriteStartElement("axis_category");
            update.WriteAttributeString("margin", "false");
            update.WriteEndElement();
            
            update.WriteStartElement("axis_value");
            update.WriteAttributeString("min", "-2");
            update.WriteAttributeString("max", "2");
            update.WriteAttributeString("steps", "2");
            update.WriteAttributeString("color", "BADBD6");
            update.WriteEndElement();

            update.WriteStartElement("draw");
            update.WriteStartElement("text");
            update.WriteAttributeString("h_align", "center");
            update.WriteAttributeString("v_align", "center");
            update.WriteAttributeString("y", "50");
            update.WriteAttributeString("size", "22");
            update.WriteAttributeString("alpha", "75");
            update.WriteRaw(sensorName);
            update.WriteEndElement();
            update.WriteEndElement();
        }        
        
        //TODO: Request update informat from database
        
        update.WriteStartElement("chart_data");

        //Write first row set with region data
        update.WriteStartElement("row");
        update.WriteElementString("null", String.Empty);
        for (int i = 0; i < 10; i++)
        {
            update.WriteElementString("string", " ");
        }
        update.WriteEndElement();

        foreach (SensorData data in dataCollection)
        {
            string[] temp = data.data.Split(',');
            sensorData.Add(temp);
        }

        if (dataCollection.Count == 1)
        {
            if (sensorData[0].Length >= 1)
            {
                update.WriteStartElement("row");
                update.WriteElementString("string", "X Axis");
                for (int i = 0; i < sensorData.Count; i++)
                {
                    update.WriteElementString("number", sensorData[0][0]);
                }
                update.WriteEndElement();
            }

            if (sensorData[1].Length >= 1)
            {
                update.WriteStartElement("row");
                update.WriteElementString("string", "Y Axis");
                for (int i = 0; i < sensorData.Count; i++)
                {
                    update.WriteElementString("number", sensorData[0][1]);
                }
                update.WriteEndElement();
            }

            if (sensorData[2].Length >= 1)
            {
                update.WriteStartElement("row");
                update.WriteElementString("string", "Z Axis");
                for (int i = 0; i < sensorData.Count; i++)
                {
                    update.WriteElementString("number", sensorData[0][2]);
                }
                update.WriteEndElement();
            }
        }
        else
        {
            if (sensorData[0].Length >= 1)
            {
                //Write data set 1
                update.WriteStartElement("row");
                update.WriteElementString("string", "X Axis");
                for (int i = 0; i < sensorData.Count; i++)
                {
                    update.WriteElementString("number", sensorData[i][0]);
                }
                update.WriteEndElement();
            }

            if (sensorData[0].Length >= 2)
            {
                //Write data set 2
                update.WriteStartElement("row");
                update.WriteElementString("string", "Y Axis");
                for (int i = 0; i < sensorData.Count; i++)
                {
                    update.WriteElementString("number", sensorData[i][1]);
                }
                update.WriteEndElement();
            }

            if (sensorData[0].Length >= 3)
            {
                //Write data set 3
                update.WriteStartElement("row");
                update.WriteElementString("string", "Z Axis");
                for (int i = 0; i < sensorData.Count; i++)
                {
                    update.WriteElementString("number", sensorData[i][2]);
                }
                update.WriteEndElement();
            }
        }

        //End chart_data
        update.WriteEndElement();

        //Write Update parameters
        update.WriteStartElement("update");
        if(!realTime)
            update.WriteAttributeString("url", context.Request.Url.AbsolutePath + "?update=" + DateTime.Now.ToFileTime() + "&deviceName=" + ((string)context.Request.Params["deviceName"]) + "," + startDate.ToString() + "," + endDate.ToString());
        else
            update.WriteAttributeString("url", context.Request.Url.AbsolutePath + "?update=" + DateTime.Now.ToFileTime() + "&deviceName=" + ((string)context.Request.Params["deviceName"]) + ",0,0" );
        update.WriteAttributeString("delay", "2.5");
        update.WriteAttributeString("mode", "data");
        update.WriteEndElement();

        //End chart
        update.WriteEndElement();

        update.WriteEndDocument();
        update.Close();
    }

    public bool IsReusable
    {
        get
        {
            return false;
        }
    }

}