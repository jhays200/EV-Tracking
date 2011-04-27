///////////////////////////////////////////////////////////
//  Motor.h
//  Implementation of the Class Motor
//  Created on:      20-Apr-2011 12:19:15 AM
//  Original author: jon
///////////////////////////////////////////////////////////

#if !defined(EA_10C2CD2F_8413_431f_9B10_86B9F3D9C97D__INCLUDED_)
#define EA_10C2CD2F_8413_431f_9B10_86B9F3D9C97D__INCLUDED_

class Motor
{

public:
	Motor();
	Motor(const Motor & copy);
	virtual ~Motor();
	double GetCurrentAccross();
	double GetDutyCycles();
	double GetRpm();
	double GetSpeed();
	double GetTemp();
	bool IsValid();
	Motor & operator=(const Motor & copy);
	void SetCurrentAccross(double newVal);
	void SetDutyCycles(double newVal);
	void SetRpm(double newVal);
	void SetSpeed(double newVal);
	void SetTemp(double newVal);
	void ToggleValid();

private:
	double m_currentAccross;
	double m_dutyCycles;
	double m_rpm;
	double m_speed;
	double m_temp;
	bool m_valid;

};
#endif // !defined(EA_10C2CD2F_8413_431f_9B10_86B9F3D9C97D__INCLUDED_)
