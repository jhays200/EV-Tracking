///////////////////////////////////////////////////////////
//  cPowerMode.h
//  Implementation of the Class cPowerMode
//  Created on:      05-May-2010 3:28:36 AM
//  Original author: Shawn
///////////////////////////////////////////////////////////
#if !defined(EA_8F91A5EE_E4E0_4ad7_BFAA_6EF07206F0AA__INCLUDED_)
#define EA_8F91A5EE_E4E0_4ad7_BFAA_6EF07206F0AA__INCLUDED_

//TODO: Move to settings file
#define Settings_Acceleration 2
#define Settings_Deceleration 8
#define Settings_MaxWattage 300
#define Settings_MinMotorPWM 1000
#define Settings_MaxMotorPWM 2000
#define Settings_MinThrottle 100
#define Settings_MaxThrottle 600

class cPowerMode
{

public:
	cPowerMode();
	virtual ~cPowerMode();

	void Update();
	void Stop();

    Servo motor;
    volatile unsigned int CurrentPower = Settings_MinMotorPWM;
    volatile unsigned int Throttle = 0;

};
#endif // !defined(EA_8F91A5EE_E4E0_4ad7_BFAA_6EF07206F0AA__INCLUDED_)
