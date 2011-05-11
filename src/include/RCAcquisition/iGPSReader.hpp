#pragma once
#include "iUpdateStradegy.hpp"
#include "RCObjects/GPSdata.hpp"

/*******************************************
 * Class: iGPSReader
 * Purpose: 
 * 	Generic interface that will be used to 
 * 	store data from any GPS
 *******************************************/
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