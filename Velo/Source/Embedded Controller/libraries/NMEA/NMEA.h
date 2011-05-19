/**
* Copyright 2010
* Shawn McGinnis <http://zxcdev.com>
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*   http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#ifndef NMEA_h
#define NMEA_h

//TODO: Commented out to run in VS2008
//#include "WProgram.h"
//#include "WConstants.h"
//#include <inttypes.h>

//HACK: Debugging
#include <iostream>
using std::cout;

struct dateTime
{
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int second;
};

class NMEA
{
public:
	NMEA();
	bool Parse(char);

private:
	//Working Items
	char sentence[82];
	int c;
	bool ChecksumIn;
	int Checksum;
	int StrChecksum;

	//Convert elements into values
	float ParseToFloat(char* s, unsigned int size);
	int   ParseToInt  (char* s, unsigned int size);

	//Data Elements
	dateTime timestamp;
	int gpsQuality;
	int sateliteCount;
	bool Status;
	float Latitude;
	float Longitude;
	float Speed;
	float Heading;
	float Declination;
	
	bool ParseGPGGA(char*); //Global Positioning System Fix Data
	bool ParseGPGSA(char*); //GPS DOP and Active Satellites
	bool ParseGPGSV(char*); //GPS Satellites in View
	bool ParseGPRMC(char*); //Recommended Minimum Specific GPS/TRANSIT Data
};

#endif
