<%@ Page Language="C#" AutoEventWireup="true" CodeFile="Install.aspx.cs" Inherits="Install" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title>Telemetry Installer</title>
</head>
<body>
    <form id="form1" runat="server">
        <div>
            <center>
                <span style="font-size: xx-large;">Database Setup</span>
                <table border="1px">
                    <tr>
                        <td>
                            <asp:Label runat="server" ID="Label_DBSource" Text="Database Source" />
                        </td>
                        <td>
                            <asp:TextBox runat="server" ID="TextBox_DBSource" />
                        </td>
                    </tr>
                    <tr>
                        <td>
                            <asp:Label runat="server" ID="Label_CatelogName" Text="Catelog Name" />
                        </td>
                        <td>
                            <asp:TextBox runat="server" ID="TextBox_CatelogName" />
                        </td>
                    </tr>
                    <tr>
                        <td>
                            <asp:Label runat="server" ID="Label_UserName" Text="User Name" />
                        </td>
                        <td>
                            <asp:TextBox runat="server" ID="TextBox_UserName" />
                        </td>
                    </tr>
                    <tr>
                        <td>
                            <asp:Label runat="server" ID="Label_UserPass" Text="User Password" />
                        </td>
                        <td>
                            <asp:TextBox runat="server" ID="TextBox_UserPass" />
                        </td>
                    </tr>
                </table>
                <asp:Button runat="server" ID="Button_Setup" Text="Setup" OnClick="WebSetup" />
                <br />
                <br />
                <asp:PlaceHolder ID="PlaceHolder_ErrorName" runat="server"></asp:PlaceHolder>
                <br />
                <asp:PlaceHolder ID="PlaceHolder_Errors" runat="server"></asp:PlaceHolder>
            </center>
        </div>
    </form>
</body>
</html>
