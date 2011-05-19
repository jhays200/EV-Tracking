<%@ Page Language="C#" MasterPageFile="~/Telemetry.master" AutoEventWireup="true"
    CodeFile="Devices.aspx.cs" Inherits="_Default" Title="Untitled Page" %>

<%@ Register Src="XMLSWFGraph.ascx" TagName="LineGraph" TagPrefix="uc" %>
<%@ Register Src="GoogleMaps.ascx" TagName="GoogleMaps" TagPrefix="uc" %>

<asp:Content ID="Content1" ContentPlaceHolderID="head" runat="Server">

    <script type="text/javascript">
    $(function() {
        // Slider
        $('#slider').slider({
            range: true,
            values: [17, 67]
        });
    });
</script>
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="body" runat="Server">
    <div class="leftdiv">
        <h2>
            Change Device</h2>
        <asp:DropDownList ID="DDL_DeviceSelect" AutoPostBack="true" AppendDataBoundItems="true" OnSelectedIndexChanged="changeDevice" runat="server">
            <asp:ListItem>Choose Device</asp:ListItem>
        </asp:DropDownList>
        <h1>
            Velomobile</h1>
        <h2>
            Last Update:</h2>
        <h3>
            Febuary 2, 2010 8:21am</h3>
    </div>
    <div class="content">
        <!-- Slider -->
        <div id="slider"></div>
        <asp:PlaceHolder ID="displays" runat="server"></asp:PlaceHolder>
    </div>
</asp:Content>
