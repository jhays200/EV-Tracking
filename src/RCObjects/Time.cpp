///////////////////////////////////////////////////////////
//  Time.cpp
//  Implementation of the Class Time
//  Created on:      20-Apr-2011 12:19:23 AM
//  Original author: jon
///////////////////////////////////////////////////////////

#include "Time.hpp"


Time::Time()
{
}

Time::~Time()
{
}


Time::Time(int tripID){

}


Time::Time(const Time & copy)
	:m_bms(copy.m_bms), m_gpsdata(copy.m_gpsdata),
	m_motor(copy.m_motor)/*, m_trip(copy.m_trip)*/
{

}


BMS* Time::GetBms()
{
	return &m_bms;
}


GPSdata* Time::GetGpsData(){

	return &m_gpsdata;
}


Motor* Time::GetMotor(){

	return &m_motor;
}


time_t Time::GetTime() const
{
	return  m_setTime;
}


// Trip* Time::GetTrip(){
// 
// 	return &m_trip;
// }


Time & Time::operator=(const Time & copy)
{
	if(this != &copy)
	{
		m_bms = copy.m_bms;
		m_gpsdata = copy.m_gpsdata;
		m_motor = copy.m_motor;
// 		m_trip = copy.m_trip;
	}
	
	return  *this;
}

void Time::SetTime()
{
	m_setTime = time(NULL);
}

time_t Time::CurrentTime() const
{
	return time(NULL);
}