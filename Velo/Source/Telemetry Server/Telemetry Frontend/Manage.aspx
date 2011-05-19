<%@ Page Title="" Language="C#" MasterPageFile="~/Telemetry.master" AutoEventWireup="true" CodeFile="Manage.aspx.cs" Inherits="Manage" %>

<asp:Content ID="Content1" ContentPlaceHolderID="head" Runat="Server">
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="body" Runat="Server">
    <div class="leftdiv">
        <h2>Selected Device:</h2>
        <asp:DropDownList ID="DDL_DeviceSelect" AppendDataBoundItems="true" AutoPostBack="true" runat="server" 
            onselectedindexchanged="DDL_DeviceSelect_SelectedIndexChanged">
            <asp:ListItem>Choose Device</asp:ListItem>
        </asp:DropDownList>
        <a href="NewDevice"><h1>Add New Device</h1></a>
    </div>
    <div class="content">
        <br />
        <table style="width:1%; vertical-align:top" cellspacing="5px">
            <tr>
                <td align="center">
                    <asp:Label ID="LBL_DeviceName" runat="server" Text="Device Name"></asp:Label>
                </td>
                <td colspan="2" align="center">
        <asp:Label ID="LBL_DeviceDescription" runat="server" Text="Device Description"></asp:Label>
                </td>
            </tr>
            <tr>
                <td valign="top">
                    <asp:TextBox ID="TB_DeviceName" ReadOnly="true" AutoCompleteType="None" CssClass="mTextArea" runat="server"></asp:TextBox>
                </td>
                <td valign="top" rowspan="3" colspan="2">
        <asp:TextBox ID="TBX_DeviceDescription" runat="server" Height="100px" 
            Width="250px" TextMode="MultiLine"></asp:TextBox>
                </td>
            </tr>
            <tr>
                <td valign="top">
                    &nbsp;</td>
            </tr>
            <tr>
                <td valign="top">
                    &nbsp;</td>
            </tr>
            <tr>
                <td valign="top" align="center">
                    <asp:Label ID="LBL_DeviceSensors" runat="server" Text="Device Sensors"></asp:Label>
                </td>
                <td valign="top" align="center" colspan="2">
        <asp:Label ID="LBL_SensorDescription" runat="server" Text="Sensor Description"></asp:Label>
                </td>
            </tr>
            <tr>
                <td valign="top">
                    <asp:ListBox CssClass="mTextArea" ID="LBX_DeviceSensors" AutoPostBack="true" runat="server" Width="125px" 
                        onselectedindexchanged="LBX_DeviceSensors_SelectedIndexChanged"></asp:ListBox>
                </td>
                <td valign="top" colspan="2">
        <asp:TextBox ID="TBX_SensorDescription" runat="server" Height="62px" 
            Width="250px" TextMode="MultiLine"></asp:TextBox>
                </td>
            </tr>
            <tr>
                <td valign="top" align="center">
                    <asp:DropDownList ID="DropDownList_DisplayType" runat="server">
                    </asp:DropDownList>
                </td>
                <td valign="middle" align="right">
                    <asp:Label ID="LBL_DisplayType" runat="server" Text="Display Type"></asp:Label>
                </td>
                <td valign="top" align="right">
                    <asp:TextBox ID="TB_DisplayType" ReadOnly="true" AutoCompleteType="None" 
                        CssClass="mTextArea" runat="server" Width="150px"></asp:TextBox>
                </td>
            </tr>
            </table>
    </div>
</asp:Content>

