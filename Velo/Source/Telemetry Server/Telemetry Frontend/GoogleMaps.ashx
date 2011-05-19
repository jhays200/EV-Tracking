<%@ WebHandler Language="C#" Class="GoogleMaps" %>

using System;
using System.Web;
using System.Xml;

public class GoogleMaps : IHttpHandler
{    
    public void ProcessRequest (HttpContext context)
    {
        context.Response.ContentType = "text/xml";
        Random numbers = new Random();
        XmlWriterSettings settings = new XmlWriterSettings();
        settings.OmitXmlDeclaration = true;
        XmlWriter update = XmlWriter.Create(context.Response.OutputStream, settings);

        update.WriteStartElement("markers");

        System.Collections.Generic.List<SensorData> dataCollection;
        dataCollection = PersistanceLayer.GetSensorData("fuze", "location", 10, true, DateTime.Now - TimeSpan.FromMinutes(30), DateTime.Now);

        foreach( SensorData item in dataCollection )
        {
            update.WriteStartElement("marker");
            update.WriteAttributeString("lat", item.data.Split(',')[0].Trim() );
            update.WriteAttributeString("lng", item.data.Split(',')[1].Trim() );
            update.WriteEndElement();
        }
        update.WriteEndDocument();
        update.Close();
    }
 
    public bool IsReusable
    {
        get { return false; }
    }
}