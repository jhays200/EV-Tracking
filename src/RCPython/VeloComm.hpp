#pragma once
#include <python2.7/Python.h>
#include <string>
#include "RCPersist/iReport.hpp"

class BMS;
class GPSdata;
class Motor;

class VeloComm: public iReport
{
public:
	VeloComm();
	~VeloComm();
	void SetBMSref(BMS * bms);
	void SetGPSref(GPSdata * gps);
	void SetMotorRef(Motor * motor);
	void Report();
	
private:
	//private static functions
	void AppendBMSstr(std::string & buff);
	void AppendGPSstr(std::string & buff);
	void AppendMotorStr(std::string & buff);
	void AppendBatteryStr(std::string & buff);
	
	//PyObject * pName;
	PyObject * pModule;
	
	//these should only be read from
	BMS * m_bms;
	GPSdata * m_gps;
	Motor * m_motor;
};