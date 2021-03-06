///////////////////////////////////////////////////////////
//  Motor.cpp
//  Implementation of the Class Motor
//  Created on:      20-Apr-2011 12:19:15 AM
//  Original author: jon
///////////////////////////////////////////////////////////

#include "Motor.hpp"
#include <string.h>

Motor::Motor()
	:/*m_currentAccross(0.0), m_dutyCycles(0.0),*/
	m_rpm(0.0), m_speed(0.0), m_temp(0.0)/*, m_valid(true)*/
{}


Motor::Motor(const Motor & copy)
	:/*m_currentAccross(copy.m_currentAccross), m_dutyCycles(copy.m_dutyCycles),*/
	m_rpm(copy.m_rpm), m_speed(copy.m_speed), m_temp(copy.m_temp)/*, m_valid(copy.m_valid)*/
{}


Motor::~Motor()
{}

/*
double Motor::GetCurrentAccross()
{
	return m_currentAccross;
}*/

/*
double Motor::GetDutyCycles()
{

	return m_dutyCycles;
}*/


double Motor::GetRpm()
{

	return m_rpm;
}


double Motor::GetSpeed()
{

	return m_speed;
}


double Motor::GetTemp(){

	return m_temp;
}


// bool Motor::IsValid(){
// 
// 	return m_valid;
// }


Motor & Motor::operator=(const Motor & copy)
{
	if(this != &copy)
	{
// 		m_currentAccross = copy.m_currentAccross;
// 		m_dutyCycles = copy.m_dutyCycles;
		m_rpm = copy.m_rpm;
		m_speed = copy.m_speed;
		m_temp = copy.m_temp;
// 		m_valid = copy.m_valid;
	}
	
	return  *this;
}


// void Motor::SetCurrentAccross(double newVal){
// 
// 	m_currentAccross = newVal;
// }


// void Motor::SetDutyCycles(double newVal){
// 
// 	m_dutyCycles = newVal;
// }


void Motor::SetRpm(double newVal){

	m_rpm = newVal;
}


void Motor::SetSpeed(double newVal){

	m_speed = newVal;
}


void Motor::SetTemp(double newVal){

	m_temp = newVal;
}


// void Motor::ToggleValid()
// {
// 	m_valid = m_valid?false:true;
// }

// class Vehicle
// {
// 
// public:
// 	Motor *m_Motor;
// 	GPSdata *m_GPSdata;
// 
// 	Vehicle();
// 	virtual ~Vehicle();
// 	std::vector<Battery>* Getbatteries();
// 	BMS* GetBMS();
// 	Controller* GetController();
// 	ElectricMotor* GetmyMotor();
// 	Trip* GetTrip();
// 
// private:
// 	std::vector<Battery> batteries;
// 	BMS bms;
// 	Controller m_controller;
// 	Trip m_Trip;
// 	ElectricMotor myMotor;
// 
// };