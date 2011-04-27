///////////////////////////////////////////////////////////
//  Trip.cpp
//  Implementation of the Class Trip
//  Created on:      20-Apr-2011 12:19:34 AM
//  Original author: jon
///////////////////////////////////////////////////////////

#include "Trip.hpp"


Trip::Trip(): m_distance(0)
{

}

// Trip::Trip(int tripID){
// 
// }


Trip::Trip(const Trip & copy)
	:m_distance(copy.m_distance), m_end_bms(copy.m_end_bms),
	m_end_t(copy.m_end_t), m_start_bms(copy.m_start_bms),
	m_start_t(copy.m_start_t)
{

}


Trip::~Trip(){

}


void Trip::EndTrip(){

}


int Trip::GetDistance()
{

	return m_distance;
}


time_t Trip::GetEnd_t(){

	return m_end_t;
}


time_t Trip::GetStart_t(){

	return m_start_t;
}


time_t Trip::GetStart_Time(){

	return m_start_t;
}


// int Trip::GetTripID(){
// 
// 	return m_tripID;
// }


Trip & Trip::operator=(const Trip & copy)
{
	if(this != &copy)
	{
		m_distance = copy.m_distance;
		m_end_bms = copy.m_end_bms;
		m_end_t = copy.m_end_t;
		m_start_bms = copy.m_start_bms;
		m_start_t = copy.m_start_t;
	}
	return  *this;
}


void Trip::SaveLocPoint(GPSdata location)
{
	m_start_loc = location;
}


void Trip::SetDistance(int newVal){

	m_distance = newVal;
}


void Trip::SetEnd_t(time_t newVal){

	m_end_t = newVal;
}


void Trip::SetStart_t(time_t newVal){

	m_start_t = newVal;
}


void Trip::StartTrip(){

}