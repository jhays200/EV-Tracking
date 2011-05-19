///////////////////////////////////////////////////////////
//  cGPS.cpp
//  Implementation of the Class cGPS
//  Created on:      05-May-2010 3:28:23 AM
//  Original author: shawn.mcginnis
///////////////////////////////////////////////////////////

#include "cGPS.h"

cGPS::cGPS()
{
    //GPS Serial Line
    Serial3.begin(38200);
}


cGPS::~cGPS()
{

}

bool cGPS::Update()
{
    for( int i = Serial3.available() ; i > 0 ; --i )
    {
        if( gps.Parse(Serial3.read()) )
        {      
            //TODO: Messaging.Send()
            i = -1;
            Serial2.print("\nGPS Date: ");
            Serial2.print(gps.utc.hour,DEC);
            Serial2.print(":");
            Serial2.print(gps.utc.min,DEC);
            Serial2.print(":");
            Serial2.print(gps.utc.sec,DEC);
            Serial2.print(" ");
            Serial2.print(gps.utc.month,DEC);
            Serial2.print("-");
            Serial2.print(gps.utc.day,DEC);
            Serial2.print("-20");
            Serial2.print(gps.utc.year,DEC);
            Serial2.print(" UTC\n");

            delay(50);

            Serial2.print("Location: ");
            Serial2.printFloat(gps.latitude,8);
            Serial2.print(", ");
            Serial2.printFloat(gps.longitude,8);
            Serial2.print("\n");

            delay(50);

            Serial2.print("   Speed: ");
            Serial2.print(gps.speed);
            Serial2.print("mph\n");

            delay(50);

            Serial2.print(" Heading: ");
            Serial2.print(gps.direction);
            Serial2.print("deg ");
            Serial2.print(gps.declination);
            Serial2.print("dec");
        }
    }
    return false;
}