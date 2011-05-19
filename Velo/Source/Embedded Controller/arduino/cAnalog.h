///////////////////////////////////////////////////////////
//  cAnalog.h
//  Implementation of the Class cAnalog
//  Created on:      05-May-2010 3:27:32 AM
//  Original author: shawn.mcginnis
///////////////////////////////////////////////////////////

#if !defined(EA_52771BDA_CD56_4b7b_95E9_D83603D2709D__INCLUDED_)
#define EA_52771BDA_CD56_4b7b_95E9_D83603D2709D__INCLUDED_

#include "cSensor.h"

/**
 * The abstract base class used for analog sensors. Inherits from the Sensor class.
 */
class cAnalog : public cSensor
{
public:
    //Ctor/Dtor
	cAnalog(unsigned int what_pin, float scale_value);
	~cAnalog();

    //Scaling
	int GetMaximum();
	void SetMaximum(int newVal);
	int GetMinimum();
	void SetMinimum(int newVal);

    bool Update();
	float Scale();

protected:
    float scale;
    unsigned int pin;
	unsigned int maximum;
	unsigned int minimum;
    unsigned int reading;
};
#endif // !defined(EA_52771BDA_CD56_4b7b_95E9_D83603D2709D__INCLUDED_)
