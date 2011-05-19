using System;
using System.Collections;
using System.Collections.Generic;
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

public partial class _Default : System.Web.UI.Page
{
    protected override void OnInit(EventArgs e)
    {
        DDL_DeviceSelect.DataSource = PersistanceLayer.GetDevices();
        DDL_DeviceSelect.DataBind();
        base.OnInit(e);
    }

    /// <summary>
    /// Name:       Page_Load
    /// Purpose:    To handle the page load event and display device
    ///             sensor information if a device has been selected
    ///             to display
    /// </summary>
    protected void Page_Load(object sender, EventArgs e)
    {
        if (!string.IsNullOrEmpty(Request.QueryString["device"]))
        {
        
            List<Sensor> deviceSensors = PersistanceLayer.GetSensors(Request.QueryString["device"]);

            //Check to make sure we don't have a null list returned, meaning there are no sensors
            //for this device.
            if (deviceSensors != null)
            {
                Session["displayDevice"] = "";
                Session["displaySensorName"] = new List<string>();
                Session["displayCount"] = 0;
                Session["displayDevice"] = Request.QueryString["device"];
                //For every sensor we'll now process and display a graph.
                foreach (Sensor mSensor in deviceSensors)
                {
                    //So far only XMLSWFGraphs are working but there will be else if statements
                    //below this one once we implement other graph types, maps, etc
                    if (mSensor.displayType == "XMLSWFGraph")
                    {
                        //Here we create a session control or append to it, defining sensors that
                        //will be associated to this device. They will be caught in XMLSWFGraph.ascx
                        //And processed out.
                        ((List<string>)Session["displaySensorName"]).Add(mSensor.sensorName);
                        Session["startDate"] = "0";
                        Session["endDate"] = "0";
                        //Now we actually load the controls, this is what will invoke XMLSWFGraph.asc
                        displays.Controls.Add(LoadControl("XMLSWFGraph.ascx"));
                    }
                }
            }
            //If we did get a null list put up an appropriate error message.
            else
            {
                Label errMessage = new Label();
                errMessage.Text = Request.QueryString["device"] + " Has no sensors to display.";
                displays.Controls.Add(errMessage);
            }
        }
        else
        {
        }
    }

    /// <summary>
    /// Name:       ChangeDevice   
    /// Purpose:    Handles the changeDevice event sent by the device drop down list.
    ///             It will redirect the user to the same page with a query string
    ///             indicating the device to be displayed now.
    /// </summary>
    protected void changeDevice(object sender, EventArgs e)
    {
        Response.Redirect("Devices.aspx?device=" + DDL_DeviceSelect.SelectedItem.Text);
    }
}
