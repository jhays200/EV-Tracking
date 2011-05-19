using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

/// <summary>
/// The Sensor class is a storage class for information relating
/// to a sensor, NOT actual sensor data.
/// </summary>
public class Sensor
{
    //TODO: Fix or remove getters/setters
    public string sensorName;
    //{
    //    get
    //    {
    //        return sensorName;
    //    }
    //    set
    //    {
    //        sensorName = value;
    //    }
    //}

    public string deviceName;
    //{
    //    get
    //    {
    //        return deviceName;
    //    }
    //    set
    //    {
    //        deviceName = value;
    //    }
    //}

    public int valueCount;
    //{
    //    get
    //    {
    //        return valueCount;
    //    }
    //    set
    //    {
    //        valueCount = value;
    //    }
    //}

    public List<string> valueNames;
    //{
    //    get
    //    {
    //        return valueNames;
    //    }
    //    set
    //    {
    //        valueNames = value;
    //    }
    //}

    public string descript;
    //{
    //    get
    //    {
    //        return descript;
    //    }
    //    set
    //    {
    //        descript = value;
    //    }
    //}

    public string displayType;
    //{
    //    get
    //    {
    //        return displayType;
    //    }
    //    set
    //    {
    //        displayType = value;
    //    }
    //}


    public Sensor()
    {
        sensorName = null;
        deviceName = null;
        valueCount = 0;
        descript = null;
        valueNames = null;
        displayType = null;
    }

    public Sensor(string msensorName, string mdeviceName, int mvalueCount, string mvalueNames, string mdescript, string mdisplayType)
    {
        sensorName = msensorName;
        deviceName = mdeviceName;
        valueCount = mvalueCount;
        descript = mdescript;

        valueNames = new List<string>();

        if (!string.IsNullOrEmpty(mvalueNames))
        {
            if (valueCount == 1)
                valueNames.Add(mvalueNames);
            else
            {
                string[] temp = mvalueNames.Split(',');
                foreach( string name in temp )
                    valueNames.Add(name);
            }
        }
        displayType = mdisplayType;
    }
}
