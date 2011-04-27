///////////////////////////////////////////////////////////
//  BMS.hpp
//  Implementation of the Class BMS
//  Created on:      20-Apr-2011 12:18:57 AM
//  Original author: jon
///////////////////////////////////////////////////////////

#if !defined(EA_629F03A6_51E1_48a3_B460_9C88B3760963__INCLUDED_)
#define EA_629F03A6_51E1_48a3_B460_9C88B3760963__INCLUDED_

#include "Battery.hpp"
#include <vector>

class BMS
{

public:
	BMS();
	BMS(const BMS & copy);
	virtual ~BMS();
	double GetavgBattCurrent();
	double GetavgBatteryResist();
	double GetavgBatteryVolt();
	std::vector<Battery>* GetBatteries();
	short Getcharge();
	bool IsValid();
	BMS & operator=(const BMS & copy);
	void SetavgBattCurrent(double newVal);
	void SetavgBatteryResist(double newVal);
	void SetavgBatteryVolt(double newVal);
	void Setcharge(short newVal);
	void ToggleValid();

private:
	double avgBattCurrent;
	double avgBatteryResist;
	double avgBatteryVolt;
	double avgBattTemp;
	short charge;
	std::vector<Battery> m_batteries;
	bool m_valid;

};
#endif // !defined(EA_629F03A6_51E1_48a3_B460_9C88B3760963__INCLUDED_)
