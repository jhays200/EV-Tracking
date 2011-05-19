using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Configuration;
using System.Data.SqlClient;
using System.Web;
using System.Web.Configuration;
using System.Web.UI;
using System.Web.UI.WebControls;

public partial class Install : System.Web.UI.Page
{
    protected void Page_Load(object sender, EventArgs e)
    {

    }

    protected void WebSetup(object sender, EventArgs e)
    {
        SqlConnection conn = new SqlConnection("Data Source=" + TextBox_DBSource.Text + ";Initial Catalog=" + TextBox_CatelogName.Text + ";User Id= " + TextBox_UserName.Text + ";Password= " + TextBox_UserPass.Text + ";");

        Label exc_id = new Label();
        TextBox exc_msg = new TextBox();
        exc_msg.Width = 550;
        exc_msg.Height = 300;
        exc_msg.TextMode = TextBoxMode.MultiLine;

        try
        {
            conn.Open();
            conn.Close();
        }
        catch (SqlException exc)
        {
            exc_id.Text = "Error: ";
            exc_id.Text += exc.Number.ToString();
            exc_id.Text += " - ";
            exc_id.ForeColor = System.Drawing.Color.Red;
            exc_msg.Text = exc.Message;
            exc_msg.ForeColor = System.Drawing.Color.Red;

            PlaceHolder_ErrorName.Controls.Add(exc_id);
            PlaceHolder_Errors.Controls.Add(exc_msg);

            return;
        }

        Configuration mConf = System.Web.Configuration.WebConfigurationManager.OpenWebConfiguration("~");
        ConnectionStringsSection mConn = (ConnectionStringsSection)mConf.GetSection("connectionStrings");
        mConn.ConnectionStrings["VELOWEB"].ConnectionString = "Data Source=" + TextBox_DBSource.Text + ";Initial Catalog=" + TextBox_CatelogName.Text + ";User Id= " + TextBox_UserName.Text + ";Password= " + TextBox_UserPass.Text + ";";
        mConf.Save();
       

        StreamReader sqlIn;
        if (File.Exists(Server.MapPath("~/SqlScript/DBCreate.sql")))
        {
            sqlIn = new StreamReader(Server.MapPath("~/SqlScript/DBCreate.sql"));
        }
        else
        {
            exc_id.Text = "Error: ";
            exc_id.ForeColor = System.Drawing.Color.Red;
            exc_msg.Text = "The database script 'SqlScript/DBCreate.sql' is missing.";
            exc_msg.ForeColor = System.Drawing.Color.Red;

            PlaceHolder_ErrorName.Controls.Add(exc_id);
            PlaceHolder_Errors.Controls.Add(exc_msg);

            return;
        }


        string sqlCommand = "";

        try
        {
            while (!sqlIn.EndOfStream)
            {
                sqlCommand += sqlIn.ReadLine();
                sqlCommand += " ";
            }
            sqlIn.Close();
            sqlCommand = sqlCommand.Replace("[TricsWeb]", "[" + TextBox_CatelogName.Text + "]");
        }
        catch(IOException exc)
        {
            exc_id.Text = "Error: ";
            exc_id.ForeColor = System.Drawing.Color.Red;
            exc_msg.Text = exc.Message;
            exc_msg.ForeColor = System.Drawing.Color.Red;

            PlaceHolder_ErrorName.Controls.Add(exc_id);
            PlaceHolder_Errors.Controls.Add(exc_msg);

            return;
        }

        try
        {
            conn.Open();
            SqlCommand dbCreate = new SqlCommand(sqlCommand, conn);
            dbCreate.ExecuteNonQuery();
            conn.Close();
        }
        catch(SqlException exc)
        {
            exc_id.Text = "Error: ";
            exc_id.Text += exc.Number.ToString();
            exc_id.Text += " - ";
            exc_id.ForeColor = System.Drawing.Color.Red;
            exc_msg.Text = exc.Message;
            exc_msg.ForeColor = System.Drawing.Color.Red;

            PlaceHolder_ErrorName.Controls.Add(exc_id);
            PlaceHolder_Errors.Controls.Add(exc_msg);

            return;
        }

        exc_msg.Text = "Successfully connected to database, created tables, and stored settings!";
        exc_msg.ForeColor = System.Drawing.Color.Green;
        PlaceHolder_Errors.Controls.Add(exc_msg);
    }
}