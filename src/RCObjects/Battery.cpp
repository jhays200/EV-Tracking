///////////////////////////////////////////////////////////
//  Battery.cpp
//  Implementation of the Class Battery
//  Created on:      20-Apr-2011 12:16:18 AM
//  Original author: jon
///////////////////////////////////////////////////////////

#include "Battery.hpp"




Battery::Battery(){

}


Battery::Battery(const Battery & copy)
:current(copy.current), resist(copy.resist), temp(copy.temp), volt(copy.volt)
{

}


Battery::~Battery(){

}


double Battery::Getcurrent(){

	return current;
}


double Battery::Getresist(){

	return resist;
}


float Battery::Gettemp(){

	return temp;
}


double Battery::Getvolt(){

	return volt;
}


Battery & Battery::operator=(const Battery & copy)
{
	return  *this;
}


void Battery::Setcurrent(double newVal){

	current = newVal;
}


void Battery::Setresist(double newVal){

	resist = newVal;
}


void Battery::Settemp(float newVal){

	temp = newVal;
}


void Battery::Setvolt(double newVal){

	volt = newVal;
}