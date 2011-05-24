#pragma once

class Motor;
class GPSdata;
class BMS;

class iReport
{
public:
	virtual ~iReport() {} //empty virual destructor
	virtual void SetBMSref(BMS * bms) = 0;
	virtual void SetGPSref(GPSdata * gps) = 0;
	virtual void SetMotorRef(Motor * motor) = 0;
	virtual void Report() = 0;
};