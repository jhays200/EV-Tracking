#pragma once
#include "iUpdateStradegy.hpp"
#include "RCObjects/GPSdata.hpp"

class iGPSReader: virtual public iUpdateStradegy
{
public:
	iGPSReader(GPSdata * data);
	virtual ~iGPSReader() = 0;
	virtual void Update() = 0;
	GPSdata & GetGPSData();
private:
  GPSdata * m_data;
};