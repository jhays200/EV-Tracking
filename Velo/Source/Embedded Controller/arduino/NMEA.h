#ifndef NMEA_h
#define NMEA_h

#include "WProgram.h"
#include "WConstants.h"
#include <inttypes.h>
#include "DateTime.h"

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
	DateTime timestamp;
	int gpsQuality;
	int sateliteCount;
	bool Status;
	float Latitude;
	float Longitude;
	float Speed;
	float Heading;
	float Direction;
	float Declination;
	
	bool ParseGPGGA(char*); //Global Positioning System Fix Data
	bool ParseGPGSA(char*); //GPS DOP and Active Satellites
	bool ParseGPGSV(char*); //GPS Satellites in View
	bool ParseGPRMC(char*); //Recommended Minimum Specific GPS/TRANSIT Data
};

#endif
