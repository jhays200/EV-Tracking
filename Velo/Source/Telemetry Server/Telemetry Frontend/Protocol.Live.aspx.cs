using System;
using System.Collections;
using System.Configuration;
using System.Data;
using System.Linq;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.HtmlControls;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
using System.Xml.Linq;
using System.Net;
using System.Text;
using System.IO;

public partial class Default2 : System.Web.UI.Page
{
    protected void Page_Load(object sender, EventArgs e)
    {

    }
    protected void bParse_Click(object sender, EventArgs e)
    {
        try
        {
            // Create a request using a URL that can receive a post. 
            WebRequest request = WebRequest.Create("http://trics.us/");

            // Set the Method property of the request to POST.
            request.Method = "POST";
            byte[] byteArray = Encoding.UTF8.GetBytes(tbRequest.Text);

            // Set the ContentType property of the WebRequest.
            request.ContentType = "metric/xml";

            // Set the ContentLength property of the WebRequest.
            request.ContentLength = byteArray.Length;

            // Get the request stream.
            Stream dataStream = request.GetRequestStream();

            // Write the data to the request stream.
            dataStream.Write(byteArray, 0, byteArray.Length);

            // Close the Stream object.
            dataStream.Close();

            // Get the response.
            WebResponse response = request.GetResponse();

            // Get the stream containing content returned by the server.
            dataStream = response.GetResponseStream();

            // Open the stream using a StreamReader for easy access.
            StreamReader reader = new StreamReader(dataStream);

            // Read the content.
            tbResponce.Text = reader.ReadToEnd();

            reader.Close();
            dataStream.Close();
            response.Close();
        }
        catch (Exception ex)
        {
            tbResponce.Text = ex.Message;
        }
    }
}
