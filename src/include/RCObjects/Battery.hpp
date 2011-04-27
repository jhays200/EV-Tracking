///////////////////////////////////////////////////////////
//  Battery.hpp
//  Implementation of the Class Battery
//  Created on:      20-Apr-2011 12:16:18 AM
//  Original author: jon
///////////////////////////////////////////////////////////

#if !defined(EA_A1B32339_E2D2_4cc2_97F0_D74F948F3818__INCLUDED_)
#define EA_A1B32339_E2D2_4cc2_97F0_D74F948F3818__INCLUDED_

class Battery
{

public:
	Battery();
	Battery(const Battery & copy);
	virtual ~Battery();
	double Getcurrent();
	double Getresist();
	float Gettemp();
	double Getvolt();
	Battery & operator=(const Battery & copy);
	void Setcurrent(double newVal);
	void Setresist(double newVal);
	void Settemp(float newVal);
	void Setvolt(double newVal);

private:
	double current;
	double resist;
	float temp;
	double volt;

};
#endif // !defined(EA_A1B32339_E2D2_4cc2_97F0_D74F948F3818__INCLUDED_)
