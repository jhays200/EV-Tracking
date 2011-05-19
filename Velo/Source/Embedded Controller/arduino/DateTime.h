///////////////////////////////////////////////////////////
//  DateTime.h
//  Implementation of the Class DateTime
//  Created on:      04-May-2010 9:24:30 PM
//  Original author: Dano
///////////////////////////////////////////////////////////

#if !defined(EA_1D94D9DF_7DB3_4a93_9F9F_DEBB9D78CB6B__INCLUDED_)
#define EA_1D94D9DF_7DB3_4a93_9F9F_DEBB9D78CB6B__INCLUDED_

enum TimeZone
{
	AST = -4,  //ATLANTIC STANDARD TIME
	CST = -6,  //CENTRAL STANDARD TIME
	EST = -5,  //EASTERN STANDARD TIME
	MST = -7,  //MOUNTAIN STANDARD TIME
	PST = -8,  //PACIFIC STANDARD TIME

	ADT = -3,  //ATLANTIC DAYLIGHT SAVING TIME
	CDT = -5,  //CENTRAL DAYLIGHT SAVING TIME
	EDT = -4,  //EASTERN DAYLIGHT SAVING TIME
	MDT = -6,  //MOUNTAIN DAYLIGHT SAVING TIME
	PDT = -7,  //PACIFIC DAYLIGHT SAVING TIME
};

/**
 * The DateTime class is used to store date and time internally so it can easily
 * be used in calculations.
 */
class DateTime
{
public:
	DateTime();
	~DateTime();

	char* ToString();
	bool ChangeTimeZone( TimeZone zome );
	bool SetTime( unsigned short int hour, unsigned short int min, unsigned short int sec, unsigned short int day, unsigned short int month, unsigned short int year, TimeZone zone );

    bool IsNull;
	unsigned short int hour;
	unsigned short int minute;
	unsigned short int second;
	unsigned short int day;
	unsigned short int month;
	unsigned short int year;
	TimeZone zone;
};

#endif // !defined(EA_1D94D9DF_7DB3_4a93_9F9F_DEBB9D78CB6B__INCLUDED_)
