using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Xml;

/// <summary>
/// Name:       meTRICS
/// Purpose:    To parse incoming telemetry data from devices and store it
///             and also to parse outgoing data and send it to devices in
///             the form of responses.
/// </summary>
public static class meTRICS
{
    static meTRICS()
    {
        //TODO: Add constructor logic here
    }

    //TODO: REFACTOR: Make this stream to stream
    public static void Parse(XmlDocument incoming, System.IO.Stream outstream)
    {
        //Create a XML Stream to the OutputStream
        XmlWriterSettings xwsOut = new XmlWriterSettings();
        xwsOut.Indent = true;
        XmlWriter outgoing = XmlWriter.Create(outstream);
        try
        {
            XmlNode xnWhitespace = incoming.SelectSingleNode("//@w | //@whitespace");
            bool bWhitespace = false;
            if (xnWhitespace != null && bool.TryParse(xnWhitespace.Value, out bWhitespace))
            {
                xwsOut.Indent = bWhitespace;
            }
            outgoing = XmlWriter.Create(outstream, xwsOut);

            //Begin the XML Responce
            outgoing.WriteStartDocument();
            outgoing.WriteStartElement(incoming.DocumentElement.Name);

            foreach (XmlNode item in incoming.DocumentElement.ChildNodes)
            {
                //DateTime Aquire
                DateTime dtItem = DateTime.Now;
                long timeStamp = 0;

                //Search for a datetime
                XmlNodeList xnlDate = item.SelectNodes("./@datetime | ./@d | ../@datetime | ../@d");

                //Search for a timestamp
                XmlNodeList xnlTime = item.SelectNodes("./@timestamp | ./@t | ../@timestamp | ../@t");

                //Check if we found a datetime and its parseable
                if (xnlDate.Count > 0 && DateTime.TryParse(xnlDate[xnlDate.Count - 1].Value, out dtItem))
                {
                    //Intentionally blank
                }
                //Otherwise use the timestamp and its parseable
                else if (xnlTime.Count > 0 && long.TryParse(xnlTime[xnlTime.Count - 1].Value, out timeStamp))
                {
                    dtItem = DateTime.Parse("1970-01-01 00:00:00").AddSeconds(timeStamp);
                }
                //Otherwise just use now.
                else
                {
                    dtItem = DateTime.Now;
                }

                //Process Acknowledgements or put them into the database                
                if (item.SelectSingleNode("./@p | ./@process") != null)
                {
                    //TODO: Spawn new Thread() for each subelement
                    outgoing.WriteStartElement(item.Name);
                    outgoing.WriteString(item.InnerXml);
                    outgoing.WriteEndElement();
                }
                else
                {
                    //Place the item into the datebase
                    try
                    {
                        PersistanceLayer.InsertSensorData(incoming.DocumentElement.Name, item.Name, item.InnerXml, dtItem);
                    }
                    catch (Exception ex)
                    {
                        outgoing.WriteStartElement(item.Name);
                        outgoing.WriteString(ex.Message);
                        outgoing.WriteEndElement();
                    }
                }
            }
            //TODO: Wait for all Threads()
        }
        catch (XmlException ex)
        {
            outgoing.WriteStartElement("Exception");
            outgoing.WriteAttributeString("type", "XmlException");
            outgoing.WriteString(ex.Message);
            outgoing.WriteEndElement();
        }
        catch (Exception ex)
        {
            outgoing.WriteStartElement("Exception");
            outgoing.WriteAttributeString("type", "Exception");
            //outgoing.WriteString(ex.Source + ": " + ex.Message + ex.StackTrace);
            outgoing.WriteString(ex.Source + ": " + ex.Message);
            outgoing.WriteEndElement();
        }
        outgoing.WriteEndDocument();
        outgoing.Close();
    }
}
