///////////////////////////////////////////////////////////
//  cSpeed.h
//  Implementation of the Class cSpeed
//  Created on:      05-May-2010 3:28:58 AM
//  Original author: shawn.mcginnis
///////////////////////////////////////////////////////////

#if !defined(EA_DBB8DA43_62AF_434c_83B7_A9C6B975B2E8__INCLUDED_)
#define EA_DBB8DA43_62AF_434c_83B7_A9C6B975B2E8__INCLUDED_

#include "cDigital.h"
#define WHEELSPEED_INT 0

/**
 * The Speed class will be the interface between internal software and the
 * hardware speed sensor.
 */
class cSpeed : public cDigital
{

public:
	cSpeed();
	virtual ~cSpeed();

	virtual bool Update();
    void* Read();

private:
    unsigned int rpm;
    float mph;
};
#endif // !defined(EA_DBB8DA43_62AF_434c_83B7_A9C6B975B2E8__INCLUDED_)
