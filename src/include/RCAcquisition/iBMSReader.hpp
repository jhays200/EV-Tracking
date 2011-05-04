#pragma once
#include "iUpdateStradegy.hpp"
#include "RCObjects/BMS.hpp"

#include <vector>

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