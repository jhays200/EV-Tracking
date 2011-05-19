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
}

class DateTime
{
public:
	string ToString();
	bool SetTimeZone( TimeZone );
	bool SetTime( hour, min, sec, day, month, year, TimeZone );
private:
	int hour;
	int min;
	int sec;
	int day;
	int month;
	int year;
	int offset;

protected:
	
};