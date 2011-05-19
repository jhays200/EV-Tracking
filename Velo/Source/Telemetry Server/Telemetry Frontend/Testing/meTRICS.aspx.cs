using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Xml;
using System.IO;

public partial class Testing_meTRICS : System.Web.UI.Page
{
    protected void Page_Load(object sender, EventArgs e)
    {
        MemoryStream outstream = new MemoryStream();

        //Load the document
        XmlDocument incoming = new XmlDocument();
        incoming.Load( Request.PhysicalApplicationPath + @"Testing\test_metrics.xml");

        //Parse
        meTRICS.Parse(incoming, outstream);

        outstream.Position = 0;

        //Load response
        XmlDocument outgoing = new XmlDocument();
        outgoing.Load(outstream);

        tbResponce.Text = outgoing.InnerXml;
    }
}
