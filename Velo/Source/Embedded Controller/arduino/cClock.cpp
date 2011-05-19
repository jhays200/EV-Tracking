///////////////////////////////////////////////////////////
//  cClock.cpp
//  Implementation of the Class cClock
//  Created on:      02-May-2010 5:18:01 PM
//  Original author: Shawn
///////////////////////////////////////////////////////////

#include "cClock.h"

/**
* Constructor
*/
cClock::cClock()
{ }

/**
* Destructor
*/
cClock::~cClock()
{ }

/**
* Get the number of milliseconds since the system started.
*/
unsigned int cClock::GetSC()
{
    //TODO: Return Timer Count in milliseconds
    return 0;
}

/**
* Set the Real Time Clocks Time / Date
*/
bool cClock::SetRTC(DateTime value)
{
    //Set Time
    //TODO: Add time to allow for execution time
    RTC.set(DS1307_SEC, value.second);
    RTC.set(DS1307_MIN, value.minute);
    RTC.set(DS1307_HR, value.hour);

    //Set Date
    RTC.set(DS1307_DATE, value.day);
    RTC.set(DS1307_MTH, value.month);
    RTC.set(DS1307_YR, value.year); 

    return false;
}

/**
* Get the Time / Date from the Real Time Clock
*/
DateTime cClock::GetRTC()
{    
    int rtcread[7];

    //Read the Real Time Clock
    RTC.get(rtcread, 1);

    //Set the time
    clock.second = rtcread[DS1307_SEC];
    clock.minute = rtcread[DS1307_MIN];
    clock.hour = rtcread[DS1307_HR];

    //Set the day
    clock.day = rtcread[DS1307_DATE];
    clock.month = rtcread[DS1307_MTH];
    clock.year = rtcread[DS1307_YR];

    return clock;
}
