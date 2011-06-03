#pragma once
#include "iRCDatabase.hpp"

class RCDatabase: public iRCDatabase
{
public:
    RCDatabase(const char * host, const char * user, const char * password, const char * db);
	void GPSInsert(double latitude,double longitude,float speed);
	void BMSInsert(double charge);
	void EMCInsert(double rpm, double speed);
	void BatteryInsert(int battnum,double current,double resist,float temp,double volt);
};