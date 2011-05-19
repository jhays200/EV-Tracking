#include "NMEA.h"

/******************************************************************************
* Constants
*****************************************************************************/


/******************************************************************************
* Methods
*****************************************************************************/
//Constructor
NMEA::NMEA()
{
	c = 0;
	Checksum = 0;
	StrChecksum = 0;
	ChecksumIn = false;
	Status = false;
}


float ParseToFloat(char* field, unsigned int field_size, char stop_char, unsigned int parse_size )
{
	char* b = new char[field_size+1];
	unsigned int copied = 0;

	//Copy the chars until a stop.
	while( field[copied] && field[copied] != stop_char && copied <= field_size )
	{
		b[copied++] = field[copied];
	}

	//Check
	if( field_size < copied )
		return -1;

	//Place the null at the end of the string
	b[parse_size] = '\0';

	//Perform the conversion
	float value = atof(b);

	//Delete the buffer
	delete b;

	//Return the value
	return value;
}
int ParseToInt(char* field, unsigned int field_size, char stop_char, unsigned int parse_size )
{
	char* b = new char[field_size+1];
	unsigned int copied = 0;

	//Copy the chars until a stop.
	while( field[copied] && field[copied] != stop_char && copied <= field_size )
	{
		b[copied++] = field[copied];
	}

	//Check
	if( field_size < copied )
		return -1;

	//Place the null at the end of the string
	b[parse_size] = '\0';

	//Perform the conversion
	int value = atoi(b);

	//Delete the buffer
	delete b;

	//Return the value
	return value;
}

bool NMEA::Parse(char read)
{
	switch(read)
	{
	case '$':		
		//Null the pointers
		ChecksumIn = false;
		Checksum = 0;
		StrChecksum = 0;
		c = 0;
		break;

	default:
		sentence[c++] = read;
		if(ChecksumIn)
		{
			if(!StrChecksum)
				StrChecksum = 16 * ((read >= '0' && read <= '9') ? 
					( read - 48 ) : ( read - 65 + 10 ));
			else
				StrChecksum += ((read >= '0' && read <= '9') ? 
				( read - 48 ) : ( read - 65 + 10 ));
		}
		else if(read != ',')
			Checksum ^= read;
		break;

	case '*':		
		sentence[c++] = read;
		ChecksumIn = true;
		break;

	case '\r':		
		sentence[c++] = '\0';
		break;

	case '\n':
		if(Checksum == StrChecksum)
		{
			//Switch on hash value of NMEA sentance name EX GPGGA = 287(P+G+G+A)
			switch( sentence[1] + sentence[2] + sentence[3] + sentence[4] )
			{
			//TODO: Switch over to ENUMS in future to avoid magic numbers
			case 287:
				ParseGPGGA(sentence);
				break;
			case 299:
				ParseGPGSA(sentence);
				break;
			case 320:
				ParseGPGSV(sentence);
				break;
			case 306:
				ParseGPRMC(sentence);
				break;
			case 296:
				//GPRMB Not Implemented;
				break;
			default:
				/*Serial.print("Parse Failed: ");
				Serial.print(sentence[0]);
				Serial.print(sentence[1]);
				Serial.print(sentence[2]);
				Serial.print(sentence[3]);
				Serial.print(sentence[4]);
				Serial.print(sentence[5]);
				Serial.println( sentence[2] + sentence[3] + sentence[4] + sentence[5] , DEC );*/
				break;
			}
		}
		else
		{
			//TODO: Report bad checksum here
		}
		break;
	}

	//VS2008 code - Have to return something in VS2008
	return false;
}

//Global Positioning System Fix Data
bool NMEA::ParseGPGGA(char* s) //287
{
	while(*s != ',')
		s++;
	s++;

	char tempBuffer[10];
	int tempNum(0);

	int degrees;
	float minutes;

	//Hours
	tempBuffer[0] = *s++;
	tempBuffer[1] = *s++;
	tempBuffer[2] = 0;

	timestamp.hour = atoi(tempBuffer);

	//Minutes
	tempBuffer[0] = *s++;
	tempBuffer[1] = *s++;
	tempBuffer[2] = 0;

	timestamp.minute = atoi(tempBuffer);

	//Seconds
	tempBuffer[0] = *s++;
	tempBuffer[1] = *s++;
	tempBuffer[2] = 0;

	timestamp.second = atoi(tempBuffer);

	s++;

	//latitude - Degrees
	tempBuffer[0] = *s++;
	tempBuffer[1] = *s++;
	tempBuffer[2] = 0;

	degrees = atoi(tempBuffer);

	//latitude - Minutes
	tempNum = 0;
	while(*s != ',')
	{
		tempBuffer[tempNum] = *s++;
		tempNum++;
	}
	tempBuffer[tempNum] = 0;

	//TODO: This will cause small rounding errors here
	minutes = atof(tempBuffer);
	s++;

	if(*s++ != 'N')
	{
		degrees *= -1;
		minutes *= -1;
	}

	s++;
	//TODO: Verify this formulas accuracy
    Latitude = minutes/60 + degrees;

	//Longitude - Degrees
	tempBuffer[0] = *s++;
	tempBuffer[1] = *s++;
	tempBuffer[2] = 0;

    Direction = atoi(tempBuffer);

	//Longitude - Minutes
	tempNum = 0;
	while(*s != ',')
	{
		tempBuffer[tempNum] = *s++;
		tempNum++;
	}
	tempBuffer[tempNum] = 0;

	//TODO: This will cause small rounding errors here
	minutes = atof(tempBuffer);
	s++;

	if(*s++ != 'N')
	{
		degrees *= -1;
		minutes *= -1;
	}

	s++;
	//TODO: Verify this formulas accuracy
	Latitude = minutes/60 + degrees;

	tempBuffer[0] = *s++;
	tempBuffer[1] = 0;

	gpsQuality = atoi(tempBuffer);

	s++;

	tempBuffer[0] = *s++;
	tempBuffer[1] = *s++;
	tempBuffer[2] = 0;

	sateliteCount = atoi(tempBuffer);

	s++;

	//EMBEDDED CODE
	//Serial.println(s);
	return false;
}

//GPS DOP and Active Satellites
bool NMEA::ParseGPGSA(char* s) //299
{
	//EMBEDDED CODE
	//Serial.println(s);
	return false;
}

//GPS Satellites in View
bool NMEA::ParseGPGSV(char* s) //320
{
	//EMBEDDED CODE
	//Serial.println(s);
	return false;
}

//Recommended Minimum Specific GPS/TRANSIT Data
bool NMEA::ParseGPRMC(char* sentence) //306
{
	//char buffer[16];

	//int index = 0;
	//char * token;

	////timestamp time hh
	//token = strtok (sentence, ",* ");
	//timestamp.hour = ParseToInt( &token[0], 2 );
	////timestamp time mm
	//timestamp.minute = ParseToInt( &token[2], 2 );
	////timestamp time ss.s
	//timestamp.second = ParseToInt( &token[4], 2 );
	//
	////latitude dddmm.mmmmm
	//token = strtok (NULL, ",");
	//timestamp.hour = ParseToInt( &token[0], 11 );



	//	case 2: // Status flag already used.
	//		break;
	//	case 3:  // LAT
	//		if( strlen(token) == 11 ) //dddmm.mmmmm
	//		{
	//			memcpy(buffer, &token[0],3);
	//			buffer[3] = '\0';
	//			latitude = atof(buffer);

	//			memcpy(buffer, &token[3],8);
	//			buffer[8] = '\0';
	//			latitude += atof(buffer)/60;
	//		}
	//		else if( strlen(token) == 10 ) //ddmm.mmmmm			
	//		{
	//			memcpy(buffer, &token[0],2);
	//			buffer[2] = '\0';
	//			latitude = atof(buffer);

	//			memcpy(buffer, &token[2],8);
	//			buffer[8] = '\0';
	//			latitude += atof(buffer)/60;
	//		}
	//		break;
	//	case 4:  // LAT N/S
	//		if( token[0] == 'S' )
	//			latitude *= -1;
	//		break;
	//	case 5:  // LONG
	//		if( strlen(token) == 11 ) //dddmm.mmmmm
	//		{
	//			memcpy(buffer, &token[0],3);				
	//			buffer[3] = '\0';
	//			Longitude = atof(buffer);

	//			memcpy(buffer, &token[3],8);
	//			buffer[8] = '\0';
	//			Longitude += atof(buffer)/60;
	//		}
	//		else if( strlen(token) == 10 ) //ddmm.mmmmm
	//		{
	//			memcpy(buffer, &token[0],2);
	//			buffer[2] = '\0';
	//			Longitude = atof(buffer);

	//			memcpy(buffer, &token[2],8);
	//			buffer[8] = '\0';
	//			Longitude += atof(buffer)/60;
	//		}
	//		break;
	//	case 6:  // LONG E/W
	//		if( token[0] == 'W' )
	//			Longitude *= -1;
	//		break;
	//	case 7:  // Speed over ground
	//		if( strlen(token) == 6 )
	//		{
	//			memcpy(buffer, &token[0],6);
	//			buffer[6] = '\0';
	//			Speed = atof(buffer) * 1.15077945;
	//		}
	//		break;
	//	case 8:  // Course over ground
	//		if( strlen(token) == 5 )
	//		{
	//			memcpy(buffer, &token[0],5);
	//			buffer[5] = '\0';
	//			Heading = atof(buffer);
	//		}
	//		break;
	//	case 9:  // Date ddmmyy
	//		if( strlen(token) == 6 )
	//		{
	//			memcpy(buffer, &token[0],2);
	//			buffer[2] = '\0';
	//			timestamp.day = atoi(buffer);

	//			memcpy(buffer, &token[2],2);
	//			buffer[2] = '\0';
	//			timestamp.month = atoi(buffer);

	//			memcpy(buffer, &token[4],2);
	//			buffer[2] = '\0';
	//			timestamp.year = atoi(buffer);
	//		}
	//		break;
	//	case 10:  // Magnetic Variation
	//		if( strlen(token) == 5 )
	//		{
	//			memcpy(buffer, &token[0],5);
	//			buffer[5] = '\0';
	//			Declination = atof(buffer);
	//		}
	//		break;
	//	case 11:  // Magnetic Variation Direction
	//		if( token[0] == 'E' )
	//			Declination *= -1;
	//		break;
	//	}
	//	token = strtok (NULL, ",");
	//	index++;
	//}
	
	return true;
}