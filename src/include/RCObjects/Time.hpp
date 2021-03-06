///////////////////////////////////////////////////////////
//  Time.h
//  Implementation of the Class Time
//  Created on:      20-Apr-2011 12:19:23 AM
//  Original author: jon
///////////////////////////////////////////////////////////

#if !defined(EA_87F48A38_A33A_4246_9EF9_9B810133AE7B__INCLUDED_)
#define EA_87F48A38_A33A_4246_9EF9_9B810133AE7B__INCLUDED_

#include "BMS.hpp"
#include "GPSdata.hpp"
#include "Motor.hpp"
#include "Trip.hpp"

class Time
{

public:
	Time();
	virtual ~Time();

	Time(int tripID);
	Time(const Time & copy);
	BMS* GetBms();
	GPSdata* GetGpsData();
	Motor* GetMotor();
	time_t GetTime() const;
	//Trip* GetTrip();
	void SetTime();
	time_t CurrentTime() const;
	Time & operator=(const Time & copy);

private:
	BMS m_bms;
	GPSdata m_gpsdata;
	Motor m_motor;
	//Trip m_trip;
	time_t m_setTime;

};
#endif // !defined(EA_87F48A38_A33A_4246_9EF9_9B810133AE7B__INCLUDED_)
