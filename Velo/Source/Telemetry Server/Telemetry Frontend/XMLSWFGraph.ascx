<%@ Control Language="C#" AutoEventWireup="true" CodeFile="XMLSWFGraph.ascx.cs" Inherits="XMLSWFGraph" %>
<embed
    type="application/x-shockwave-flash"
    pluginspage="http://www.macromedia.com/go/getflashplayer"
    width="400" height="250" 
    devicefont="false" play="true" quality="high"
    allowscriptaccess="sameDomain" allowfullscreen="true" menu="true"
    name="charts" scale="noScale" wmode="opaque"
    <% string update = "flashvars=library_path=charts_library&amp;xml_source=XMLSWFGraph.ashx?deviceName=" + (string)Session["displayDevice"] + "," + ((System.Collections.Generic.List<string>)Session["displaySensorName"])[(int)Session["displayCount"]] + "," + Session["startDate"] + "," + Session["endDate"]; %>
    <% Session["displayCount"] = (int)Session["displayCount"] + 1; %>
    <%=update %>
    src="charts.swf" bgcolor="#212629"
/>