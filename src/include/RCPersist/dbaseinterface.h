#pragma once
#include "RCPersist/mysqltest.h"
#include <string>
using std::string;
/*
	Class :: DBaseInterface
	Written By : Joshua "Tank" Dutton
	purpose: Allow the system to interface with the mysql database
*/
class DBaseInterface
{
	string server;
	string user;
	string database;
	string result;
	string password;
public:
	DBaseInterface();
	void BMSInsert(double avgBattCurrent,
	double avgBatteryResist,
	double avgBatteryVolt,
	double avgBattTemp);

	void GPSInsert(double latitude,
	double longitude,
	float speed);

	void ZillaInsert(	double currentAcross,
	double dutyCycles,
	double rpm,
	double speed,
	double temp);

	void BatteryInsert(int battnum,
		double current,
	double resist,
	float temp,
	double volt);
};

