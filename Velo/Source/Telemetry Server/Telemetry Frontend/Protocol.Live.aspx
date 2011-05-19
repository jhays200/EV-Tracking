<%@ Page Language="C#" MasterPageFile="~/Telemetry.master" AutoEventWireup="true"
    CodeFile="Protocol.Live.aspx.cs" ValidateRequest="false" Inherits="Default2" Title="Untitled Page" %>

<asp:Content ID="cHead" ContentPlaceHolderID="head" runat="Server">
</asp:Content>
<asp:Content ID="cBody" ContentPlaceHolderID="body" runat="Server">
    <table style="margin:auto;text-align:center;vertical-align:middle;width:85%;">
        <tr>
            <td style="width:50%;">
                <img alt="Request" src="images/protocol.request.png" />
            </td>
            <td style="width:115px;">
            </td>
            <td style="width:50%;"
                <img alt="Responce" src="images/protocol.response.png" />
            </td>
        </tr>
        <tr>
            <td>
                <asp:TextBox ID="tbRequest" runat="server" TextMode="MultiLine" Height="250px" Width="100%">
<VeloMobile whitespace="true">
    <light ts="213211">750</light>
</VeloMobile></asp:TextBox>
            </td>
            <td>
                <asp:ImageButton ID="bParse" ImageUrl="~/images/content.parse.png" OnClick="bParse_Click"
                    runat="server" />
            </td>
            <td>
                <asp:TextBox ID="tbResponce" runat="server" TextMode="MultiLine" Height="250px" Width="100%" />
            </td>
        </tr>
    </table>
</asp:Content>
