<%@ WebHandler Language="C#" Class="Parser" %>

using System;
using System.Web;
using System.IO;
using System.Xml;
using System.Threading;


public class Parser : IHttpHandler
{
    public void ProcessRequest(HttpContext c)
    {
        switch (c.Request.ContentType)
        {
            case "metric/xml":
            case "metrics/xml":
                c.Response.ContentType = "metric/xml";

                try
                {
                    //Load the Request into a XmlDocument
                    XmlDocument incoming = new XmlDocument();
                    incoming.Load(c.Request.InputStream);

                    //Parse the document
                    meTRICS.Parse(incoming, c.Response.OutputStream);
                }
                catch
                {
                    //TODO: Respond to the error.
                    throw;
                }                
                break;

            case "metric/image":
            case "metrics/image":
                c.Response.ContentType = "metric/image";

                try
                {
                    string fname = @"C:\Documents and Settings\All Users\Desktop\Telemetry Files\Telemetry Server\Telemetry Frontend\" + c.Request.Headers["device"] + ".jpg";
                    FileStream fs = new FileStream(fname, FileMode.Create);
                    StreamReader sr = new StreamReader(c.Request.InputStream, System.Text.Encoding.UTF8);
                    StreamWriter sw = new StreamWriter(fs, System.Text.Encoding.UTF8);
                    sw.Write(sr.ReadToEnd());
                    sr.Close();
                    sw.Close();
                    fs.Close();
                }
                catch(Exception ex)
                {
                    StreamWriter sw = new StreamWriter(c.Response.OutputStream);
                    sw.WriteLine(ex.Message);
                    sw.Close();                    
                }
                break;
                
            case "text/html":
            default:
                c.Response.Redirect("Home.aspx");
                break;
        }
        if (c.Request.ContentType != "metric/xml")
        {
        }
        else
        {
            
        }
    }

    public bool IsReusable
    {
        get { return false; }
    }
}