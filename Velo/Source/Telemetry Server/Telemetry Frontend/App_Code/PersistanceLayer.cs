using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Data.SqlClient;

/// <summary>
/// Name:       PersistanceLayer
/// Purpose:    To povide a static interface between the database and the web application.
///             It maintains a complete abstraction between our database and our code.
/// </summary>
public static class PersistanceLayer
{
    static PersistanceLayer()
	{
	}

    /// <summary>
    /// Name:       GetDisplayInfo
    /// </summary>
    /// <returns>
    /// Returns a string of display types
    /// </returns>
    static public string GetDisplayInfo(string displayName)
    {
        SqlConnection conn = new SqlConnection(System.Configuration.ConfigurationManager.ConnectionStrings["VELOWEB"].ConnectionString);

        try
        {
            conn.Open();
            SqlCommand deviceQuery = new SqlCommand("SELECT displayType FROM Display WHERE displayName = '" + displayName + "'", conn);
            SqlDataReader deviceReader = deviceQuery.ExecuteReader();

            if (deviceReader.Read())
            {
                if (!deviceReader.IsDBNull(0))
                    return deviceReader.GetString(0);
                else
                    return null;
            }
            else
                return null;
        }
        catch
        {
            return null;
        }
        finally
        {
            conn.Close();
        }
    }

    /// <summary>
    /// Name:       DisplayType
    /// </summary>
    /// <returns>
    /// Returns a list of strings, the names of the display types available to the user.
    /// </returns>
    static public List<string> GetDisplays()
    {
        SqlConnection conn = new SqlConnection(System.Configuration.ConfigurationManager.ConnectionStrings["VELOWEB"].ConnectionString);

        try
        {
            conn.Open();
            SqlCommand deviceQuery = new SqlCommand("SELECT displayName FROM Display", conn);
            SqlDataReader deviceReader = deviceQuery.ExecuteReader();

            if (deviceReader.Read())
            {
                List<string> tempList = new List<string>();
                if (!deviceReader.IsDBNull(0))
                    tempList.Add(deviceReader.GetString(0));

                while (deviceReader.Read())
                {
                    if (!deviceReader.IsDBNull(0))
                        tempList.Add(deviceReader.GetString(0));
                }

                return tempList;
            }
            else
                return null;
        }
        catch
        {
            return null;
        }
        finally
        {
            conn.Close();
        }
    }

    /// <summary>
    /// Name:       GetDeviceInfo
    /// Purpose:    Pulls device information for the given device sent in through deviceName.
    /// </summary>
    /// <param name="deviceName">
    /// The device name that we will be pulling information for and returning.
    /// </param>
    /// <returns>
    /// Returns a device class populated with the devices name and description and
    /// returns null if the device does not exist. Should never happen.
    /// </returns>
    static public Device GetDeviceInfo(string deviceName)
    {
        SqlConnection conn = new SqlConnection(System.Configuration.ConfigurationManager.ConnectionStrings["VELOWEB"].ConnectionString);

        try
        {
            conn.Open();
            SqlCommand deviceQuery = new SqlCommand("SELECT deviceName, descript FROM Devices WHERE deviceName = '" + deviceName + "'", conn);
            SqlDataReader deviceReader = deviceQuery.ExecuteReader();

            if (deviceReader.Read())
            {
                Device deviceInfo = new Device();
                if (!deviceReader.IsDBNull(0))
                    deviceInfo.deviceName = deviceReader.GetString(0);
                if (!deviceReader.IsDBNull(1))
                    deviceInfo.description = deviceReader.GetString(1);

                return deviceInfo;
            }
            else
                return null;
        }
        catch
        {
            return null;
        }
        finally
        {
            conn.Close();
        }
    }

    /// <summary>
    /// Name:       GetDevices
    /// Purpose:    Pulls all devices in the database and puts them into a 
    ///             list Device classes.
    /// </summary>
    /// <returns>
    /// Returns a list of Device classes or null if there are no devices.
    /// </returns>
    static public List<string> GetDevices()
    {
        List<string> deviceList = new List<string>();
        SqlConnection conn = new SqlConnection(System.Configuration.ConfigurationManager.ConnectionStrings["VELOWEB"].ConnectionString);
        try
        {
            conn.Open();
            SqlCommand deviceQuery = new SqlCommand("SELECT deviceName FROM Devices", conn);
            SqlDataReader deviceReader = deviceQuery.ExecuteReader();

            if (deviceReader.Read())
            {
                if (!deviceReader.IsDBNull(0))
                        deviceList.Add(deviceReader.GetString(0));
                else
                    return null;

                while (deviceReader.Read())
                {
                    if (!deviceReader.IsDBNull(0))
                        deviceList.Add(deviceReader.GetString(0));
                }
                return deviceList;
            }
            else
                return null;
        }
        catch
        {
            return null;
        }
        finally
        {
            conn.Close();
        }
    }

    /// <summary>
    /// Name:       GetSensors 
    /// Purpose:    Retrieves all sensors associated to deviceName
    /// </summary>
    /// <param name="deviceName">
    /// deviceName contains the device name we will be pulling sensors for.
    /// </param>
    /// <returns>
    /// Returns a list of Sensor classes to the user, or null if there are no sensors.
    /// </returns>
    static public List<Sensor> GetSensors(string deviceName)
    {
        //TODO: BUG here with sensor display types etc or in manage.aspx.cs
        List<Sensor> deviceList = new List<Sensor>();
        SqlConnection conn = new SqlConnection(System.Configuration.ConfigurationManager.ConnectionStrings["VELOWEB"].ConnectionString);
        try
        {
            conn.Open();
            SqlCommand deviceQuery = new SqlCommand("SELECT deviceName, sensorName, valueCount, valueName, descript, displayType, Sensors.displayName FROM Sensors RIGHT OUTER JOIN Display on(Sensors.displayName = Display.displayName) WHERE deviceName = '" + deviceName + "'", conn);
            SqlDataReader deviceReader = deviceQuery.ExecuteReader();

            string mdeviceName = "";
            string sensorName = "";
            int valueCount = 0;
            string valueName = "";
            string descript = "";
            string displayType = "";

            if (deviceReader.Read())
            {
                if (!deviceReader.IsDBNull(0))
                    mdeviceName = deviceReader.GetString(0);
                if (!deviceReader.IsDBNull(1))
                    sensorName = deviceReader.GetString(1);
                if (!deviceReader.IsDBNull(2))
                    valueCount = deviceReader.GetInt32(2);
                if (!deviceReader.IsDBNull(3))
                    valueName = deviceReader.GetString(3);
                if (!deviceReader.IsDBNull(4))
                    descript = deviceReader.GetString(4);
                if (!deviceReader.IsDBNull(5))
                    displayType = deviceReader.GetString(5);

                deviceList.Add(new Sensor(sensorName, mdeviceName, valueCount, valueName, descript, displayType));

                while (deviceReader.Read())
                {
                    if (!deviceReader.IsDBNull(0))
                        mdeviceName = deviceReader.GetString(0);
                    if (!deviceReader.IsDBNull(1))
                        sensorName = deviceReader.GetString(1);
                    if (!deviceReader.IsDBNull(2))
                        valueCount = deviceReader.GetInt32(2);
                    if (!deviceReader.IsDBNull(3))
                        valueName = deviceReader.GetString(3);
                    if (!deviceReader.IsDBNull(4))
                        descript = deviceReader.GetString(4);
                    if (!deviceReader.IsDBNull(5))
                        displayType = deviceReader.GetString(5);

                    deviceList.Add(new Sensor(sensorName, mdeviceName, valueCount, valueName, descript, displayType));
                }
                return deviceList;
            }
            else
                return null;
        }
        catch(Exception e)
        {
            return null;
        }
        finally
        {
            conn.Close();
        }
    }

    /// <summary>
    /// Name:       InsertSensorData
    /// Purpose:    Provides an abstraction for inserting sensor data into the database.
    ///             This sensor data is actual telemetry data that will be coming from
    ///             the parser.
    /// </summary>
    /// <param name="deviceID">
    /// The device identifier name that the sensor data is associated to
    /// </param>
    /// <param name="sensorID">
    /// The sensor identifier name that the sensor data is associated to
    /// </param>
    /// <param name="sensorValue">
    /// The sensor value or values that are being passed in
    /// </param>
    /// <param name="timeStamp">
    /// Timestamp at which the data was received or parsed
    /// </param>
    static public void InsertSensorData(string deviceID, string sensorID, string sensorValue, DateTime timeStamp)
    {
        SqlConnection conn = new SqlConnection(System.Configuration.ConfigurationManager.ConnectionStrings["VELOWEB"].ConnectionString);
        try
        {
            conn.Open();

            SqlCommand existanceCheck = new SqlCommand("SELECT errorCount FROM Sensors WHERE deviceName = '" + deviceID + "' AND sensorName LIKE '" + sensorID + "'", conn);
            SqlDataReader existanceReader = existanceCheck.ExecuteReader();
            if (existanceReader.Read())
            {
                //TODO: Instead of just inserting, do range checks etc.
                existanceReader.Close();

                SqlCommand cmd = new SqlCommand("INSERT INTO SensorData(deviceName, sensorName, data, dateReceived) VALUES (@deviceID, @sensorID, @sensorValue, @timeStamp)", conn);
                cmd.Parameters.AddWithValue("@deviceID", deviceID);
                cmd.Parameters.AddWithValue("@sensorID", sensorID);
                cmd.Parameters.AddWithValue("@sensorValue", sensorValue);
                cmd.Parameters.AddWithValue("@timeStamp", timeStamp.ToUniversalTime());
                cmd.ExecuteNonQuery();
            }
            else
            {
                throw new Exception("Unable to find the existance of deviceName: '" + deviceID + "' AND sensorName: '" + sensorID + "'");
            }

            conn.Close();
        }
        finally
        {
            conn.Close();
        }
    }

    /// <summary>
    /// Name:       GetSensorData
    /// Purpose:    Retrieves a list of SensorData classes which will contain
    ///             telemetry data for a sensor.
    /// </summary>
    /// <param name="deviceID">
    /// The device identifier name that the sensor data will be pulled from.
    /// </param>
    /// <param name="sensorID">
    /// The sensor identifier name that the sensor data will be pulled from.
    /// </param>
    /// <param name="quantity">
    /// The number of SensorData classes to be returned
    /// </param>
    /// <param name="descending">
    /// If this is true we will return the list in descending order, if it is
    /// false we will return the list in ascending order.
    /// </param>
    /// <returns>
    /// A sorted list is returned or null if there is no sensor data for the
    /// desired device.
    /// </returns>
    static public List<SensorData> GetSensorData(string deviceID, string sensorID, int quantity, bool descending, DateTime start, DateTime end)
    {
        SqlConnection conn = new SqlConnection(System.Configuration.ConfigurationManager.ConnectionStrings["VELOWEB"].ConnectionString);
        try
        {
            conn.Open();
            List<SensorData> returnList = new List<SensorData>();
            SensorData temp;

            SqlCommand sensorCommand = new SqlCommand("SELECT TOP " + quantity + " deviceName, sensorName, dateReceived, data, error FROM SensorData WHERE deviceName = @deviceID AND sensorName = @sensorID AND  dateReceived < @end AND  dateReceived > @start ORDER BY dateReceived " + ((descending) ? "DESC" : "ASC"), conn);
            sensorCommand.Parameters.AddWithValue("@deviceID", deviceID);
            sensorCommand.Parameters.AddWithValue("@sensorID", sensorID);
            sensorCommand.Parameters.AddWithValue("@start", start.ToUniversalTime());
            sensorCommand.Parameters.AddWithValue("@end", end.ToUniversalTime());
        
            SqlDataReader sensorReader = sensorCommand.ExecuteReader();

            if (sensorReader.Read())
            {
                temp = new SensorData();
                if (!sensorReader.IsDBNull(0))
                    temp.deviceID = sensorReader.GetString(0);
                if (!sensorReader.IsDBNull(1))
                    temp.sensorID = sensorReader.GetString(1);
                if (!sensorReader.IsDBNull(2))
                    temp.timeStamp = sensorReader.GetDateTime(2);
                if (!sensorReader.IsDBNull(3))
                    temp.data = sensorReader.GetString(3);
                if (!sensorReader.IsDBNull(4))
                    temp.errorcount = sensorReader.GetInt32(4);
                returnList.Add(temp);

                while (sensorReader.Read())
                {
                    temp = new SensorData();
                    if (!sensorReader.IsDBNull(0))
                        temp.deviceID = sensorReader.GetString(0);
                    if (!sensorReader.IsDBNull(1))
                        temp.sensorID = sensorReader.GetString(1);
                    if (!sensorReader.IsDBNull(2))
                        temp.timeStamp = sensorReader.GetDateTime(2);
                    if (!sensorReader.IsDBNull(3))
                        temp.data = sensorReader.GetString(3);
                    if (!sensorReader.IsDBNull(4))
                        temp.errorcount = sensorReader.GetInt32(4);
                    returnList.Add(temp);
                }
                conn.Close();
                return returnList;
            }
            else
            {
                conn.Close();
                return null;
            }
        }
        catch(SqlException ex)
        {
            conn.Close();
            return null;
        }
    }
}
