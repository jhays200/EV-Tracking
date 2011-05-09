#pragma once
#include "iUpdateStradegy.hpp"
#include "RCObjects/GPSdata.hpp"

class iGPSReader: public iUpdateStradegy
{
public:
	iGPSReader(GPSdata * data);
	virtual ~iGPSReader(){}
	virtual void Update() = 0;
	GPSdata & GetGPSData();
private:
  GPSdata * m_data;
};