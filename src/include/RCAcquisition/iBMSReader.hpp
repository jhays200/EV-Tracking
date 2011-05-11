#pragma once
#include "iUpdateStradegy.hpp"
#include "RCObjects/BMS.hpp"

#include <vector>

/*******************************************
 * Class: iBMSReader
 * Purpose: 
 * 	Generic interface that will be used to 
 * 	store data from any BMS
 *******************************************/
class iBMSReader: public iUpdateStradegy
{
public:
	iBMSReader(BMS * data);
	virtual ~iBMSReader(){}
	virtual void Update() = 0;
	
	std::vector<Battery> * GetBatteries();
	BMS & GetBMS();
private:
	BMS * m_data;
};