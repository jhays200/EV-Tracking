///////////////////////////////////////////////////////////
//  GPSdata.cpp
//  Implementation of the Class GPSdata
//  Created on:      20-Apr-2011 12:16:35 AM
//  Original author: jonathan.hays
///////////////////////////////////////////////////////////

#include "GPSdata.hpp"
GPSdata::GPSdata()
    : m_bearing(0),m_latitude(0.0),m_longitude(0.0),
    m_speed(0.0f), m_valid(true)
{
}


GPSdata::GPSdata(const GPSdata& copy)
    : m_bearing(copy.m_bearing),m_latitude(copy.m_latitude),
    m_longitude(copy.m_longitude),
    m_speed(copy.m_speed), m_valid(copy.m_valid)
{

}


GPSdata::GPSdata(float speed, double latitude, double longitude, int bearing)
    : m_bearing(bearing),m_latitude(latitude),m_longitude(longitude),
      m_speed(m_speed),m_valid(true)
{

}


GPSdata::~GPSdata()
{

}


int GPSdata::GetBearing() const {

	return m_bearing;
}


double GPSdata::GetLatitude() const {

	return m_latitude;
}


double GPSdata::GetLongitude() const {

	return m_longitude;
}


float GPSdata::GetSpeed() const {

	return m_speed;
}


bool GPSdata::IsValid(){

	return m_valid;
}


GPSdata & GPSdata::operator=(const GPSdata& copy)
{
	if(this != &copy)
	{
		m_bearing = copy.m_bearing;
		m_latitude = copy.m_latitude;
		m_longitude = copy.m_longitude;
		m_speed = copy.m_speed;
		m_valid = copy.m_valid;
	}
	
	return  *this;
}


void GPSdata::SetBearing(int newVal){

	m_bearing = newVal;
}


void GPSdata::SetData(float speed, double latitude, double longitude, int bearing)
{
	m_speed = speed;
	m_latitude = latitude;
	m_longitude = longitude;
	m_bearing = bearing;
	m_valid = true;
}


void GPSdata::SetLatitude(double newVal){

	m_latitude = newVal;
}


void GPSdata::SetLongitude(double newVal){

	m_longitude = newVal;
}


void GPSdata::SetSpeed(float newVal){

	m_speed = newVal;
}


void GPSdata::SetValid(bool valid)
{
	m_valid = valid;
}