using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

/// <summary>
/// Name:       Device
/// Purpose:    To act as a container for our device class,
///             so that we can pass device information around
///             easily.
/// </summary>
public class Device
{
    //TODO: Fix or remove getters/setters
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

    public string description;
    //{
    //    get
    //    {
    //        return description;
    //    }
    //    set
    //    {
    //        description = value;
    //    }
    //}

	public Device()
	{
        deviceName = null;
        description = null;
	}
}
