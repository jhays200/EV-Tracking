///////////////////////////////////////////////////////////
//  BMS.cpp
//  Implementation of the Class BMS
//  Created on:      20-Apr-2011 12:18:57 AM
//  Original author: jon
///////////////////////////////////////////////////////////

#include "BMS.hpp"




BMS::BMS()
:/*avgBattCurrent(0.0), avgBatteryResist(0.0), avgBatteryVolt(0.0), 
avgBattTemp(0.0),*/ charge(0), m_batteries(), m_valid(true)
{

}


BMS::BMS(const BMS & copy)
:/*avgBattCurrent(copy.avgBattCurrent), avgBatteryResist(copy.avgBatteryResist), 
avgBatteryVolt(copy.avgBatteryVolt), avgBattTemp(copy.avgBattTemp), */
charge(copy.charge), m_batteries(copy.m_batteries), m_valid(copy.m_valid)
{

}


BMS::~BMS()
{

}

/*
double BMS::GetavgBattCurrent()
{

	return avgBattCurrent;
}


double BMS::GetavgBatteryResist()
{

	return avgBatteryResist;
}


double BMS::GetavgBatteryVolt()
{

	return avgBatteryVolt;
}*/


std::vector<Battery>& BMS::GetBatteries()
{

	return m_batteries;
}


short BMS::Getcharge()
{

	return charge;
}


bool BMS::IsValid()
{

	return m_valid;
}


BMS & BMS::operator=(const BMS & copy)
{
	
// 	avgBattCurrent = copy.avgBattCurrent;
// 	avgBatteryResist = copy.avgBatteryResist;
// 	avgBatteryVolt = copy.avgBatteryVolt;
// 	avgBattTemp = copy.avgBattTemp;
	charge = copy.charge;
	m_batteries = copy.m_batteries;
	m_valid = copy.m_valid;

	return  *this;
}

/*
void BMS::SetavgBattCurrent(double newVal)
{

	avgBattCurrent = newVal;
}


void BMS::SetavgBatteryResist(double newVal)
{

	avgBatteryResist = newVal;
}


void BMS::SetavgBatteryVolt(double newVal)
{

	avgBatteryVolt = newVal;
}
*/

void BMS::Setcharge(short newVal)
{

	charge = newVal;
}


void BMS::ToggleValid()
{
	m_valid = m_valid?false:true;
}