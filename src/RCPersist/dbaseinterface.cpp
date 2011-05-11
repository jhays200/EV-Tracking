#include "RCPersist/dbaseinterface.h"
#include <iostream>
#include <cstdio>
using std::cin;
using std::cout;
#include <string>
using std::string;
#include <mysql/my_global.h>


/*
	
*/
DBaseInterface::DBaseInterface()
{
	char query[256];



	user = "root";

	server = "127.0.0.1";

	database = "jp";

	password = "maverick";

	RCDatabaseTest t(server.c_str(),user.c_str(),database.c_str(),
		password.c_str());
/*
	printf("Enter a query: ");
	std::cin.getline(query, 256);

	t.Query(query);

	result = t.Fetch();
	while(!result.empty())
	{
		printf("\n",result.c_str());
		result = t.Fetch();
	}*/

}

void DBaseInterface::BMSInsert(double avgBattCurrent,
	double avgBatteryResist,
	double avgBatteryVolt,
	double avgBattTemp)
{
	char buffer[256];
	RCDatabaseTest t(server.c_str(),user.c_str(),database.c_str(),
		password.c_str());

	string query = "INSERT INTO BMS (AvgVolts, AvgAmps, AvgResist, AvgTemp, trip_id) VALUES( ";
	sprintf(buffer,"%f",avgBatteryVolt);
	query += buffer;
	query += ", ";
	sprintf(buffer,"%f",avgBattCurrent);
	query += buffer;
	query += ", ";
			sprintf(buffer,"%f",avgBatteryResist);
		query += buffer;
	query += ", ";
// 			sprintf(buffer,"%i",charge);
// 		query += buffer;
// 	query += ", ";
					sprintf(buffer,"%f",avgBattTemp);
		query += buffer;
	query += ", ";
	query += "(select MAX(trip_id) from trip))";
	t.Query(query.c_str());
	cout << query;

	
}

void DBaseInterface::GPSInsert(
	double latitude,
	double longitude,
	float speed)
{
		char buffer[256];
	RCDatabaseTest t(server.c_str(),user.c_str(),database.c_str(),
		password.c_str());

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
	t.Query(query.c_str());
}

void DBaseInterface::ZillaInsert(	double currentAcross,
	double dutyCycles,
	double rpm,
	double speed,
	double temp)
{
		char buffer[256];
	RCDatabaseTest t(server.c_str(),user.c_str(),database.c_str(),
		password.c_str());

	string query = "INSERT INTO MOTOR_DATA (trip_id, Speed, AvgDutyCycles, RPM, CurrentAccross) VALUES((select MAX(trip_id) from trip), ";
	sprintf(buffer,"%f",speed);
	query += buffer;
	query += ", ";
	sprintf(buffer,"%f",dutyCycles);
	query += buffer;
	query += ", ";
			sprintf(buffer,"%f",rpm);
		query += buffer;
	query += ", ";
			sprintf(buffer,"%f",currentAcross);
		query += buffer;
	query += ");";
	t.Query(query.c_str());
}

	void DBaseInterface::BatteryInsert(int battnum,
		double current,
	double resist,
	float temp,
	double volt)
	{
				char buffer[256];
	RCDatabaseTest t(server.c_str(),user.c_str(),database.c_str(),
		password.c_str());

	string query = "INSERT INTO BATTERY (BMS_ID, Battery_ID, Volts, Amps, Resist, Temp)	VALUES((select max(bms_id) from bms), ";
	sprintf(buffer,"%i",battnum);
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
	t.Query(query.c_str());
	}
