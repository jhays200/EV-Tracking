#include "RCDatabase.hpp"
#include <stdlib.h>

RCDatabase::RCDatabase(const char * host, const char * user, const char * password, const char * db)
	:iRCDatabase(host,user,password,db)
{}

void RCDatabase::BMSInsert(double charge)
{
	char buffer[256];
	string query = "INSERT INTO BMS (Charge, trip_id) VALUES( ";
	/*sprintf(buffer,"%f",avgBatteryVolt);
	query += buffer;
	query += ", ";
	sprintf(buffer,"%f",avgBattCurrent);
	query += buffer;
	query += ", ";
			sprintf(buffer,"%f",avgBatteryResist);
		query += buffer;
	query += ", ";*/
 			sprintf(buffer,"%i",charge);
 		query += buffer;
 	/*query += ", ";
					sprintf(buffer,"%f",avgBattTemp);
		query += buffer;*/
	query += ", ";
	query += "(select MAX(trip_id) from trip))";
	
	Query(query.c_str());
}

void RCDatabase::GPSInsert(
	double latitude,
	double longitude,
	float speed)
{
		char buffer[256];

	string query = "INSERT INTO GPS_DATA (trip_id, Longitude, Lattitude, speed) VALUES((select MAX(trip_id) from trip),";
	sprintf(buffer,"%f",longitude);
	query += buffer;
	query += ", ";
	sprintf(buffer,"%f",latitude);
	query += buffer;
	query += ", ";
			sprintf(buffer,"%f",speed);
		query += buffer;
	query += ", ";
// 			sprintf(buffer,"%i",direction);
// 		query += buffer;
	query += ", ";
	query += ");";
	Query(query.c_str());
}

void RCDatabase::EMCInsert(
	double rpm,
	double speed)
{
		char buffer[256];

	string query = "INSERT INTO MOTOR_DATA (trip_id, Speed, RPM) VALUES((select MAX(trip_id) from trip), ";
	sprintf(buffer,"%f",speed);
	query += buffer;
	query += ", ";
	sprintf(buffer,"%f",rpm);
	query += buffer;
	query += ", ";
			sprintf(buffer,"%f",speed);
		query += buffer;
	query += ");";
	Query(query.c_str());
}

	void RCDatabase::BatteryInsert(int battnum,
		double current,
	double resist,
	float temp,
	double volt)
	{
				char buffer[256];

	string query = "INSERT INTO BATTERY (BMS_ID, Battery_ID, Volts, Amps, Resist, Temp)	VALUES((select max(bms_id) from bms), ";
	sprintf(buffer,"%d",battnum);
	query += buffer;
	query += ", ";
	sprintf(buffer,"%f",volt);
	query += buffer;
	query += ", ";
			sprintf(buffer,"%f",current);
		query += buffer;
	query += ", ";
			sprintf(buffer,"%f",resist);
		query += buffer;
	query += ", ";
					sprintf(buffer,"%f",temp);
		query += buffer;
	query += ");";
	Query(query.c_str());
	}
