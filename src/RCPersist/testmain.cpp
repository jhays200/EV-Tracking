#include <iostream>
#include <string>
#include "mysqltest.h"
#include <cstdio>
#include "RCPersist/dbaseinterface.h"
#include "classes.h"
using std::cin;
using std::cout;
using std::endl;


int main()
{
	
	DBaseInterface * dbase = new DBaseInterface();
	dbase->GPSInsert(100,
	200,
	30);


//	void GPSInsert(int direction,
//	double latitude,
//	double longitude,
//	float speed);
//
//	void ZillaInsert(	double currentAcross,
//	double dutyCycles,
//	double rpm,
//	double speed,
//	double temp);
//
//	void BatteryInsert(int battnum,
//		double current,
//	double resist,
//	float temp,
//	double volt);
//	return 0;
}