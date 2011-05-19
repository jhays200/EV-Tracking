///////////////////////////////////////////////////////////
//  cDigital.h
//  Implementation of the Class cDigital
//  Created on:      05-May-2010 3:28:14 AM
//  Original author: shawn.mcginnis
///////////////////////////////////////////////////////////

#if !defined(EA_DBDF59D0_734F_4bb6_A872_8BAE8C9F1528__INCLUDED_)
#define EA_DBDF59D0_734F_4bb6_A872_8BAE8C9F1528__INCLUDED_

#include "cSensor.h"

/**
 * The abstract base class for digital sensors, inherits from the Sensor class.
 */
class cDigital : public cSensor
{

public:
	cDigital();
	virtual ~cDigital();

private:

};
#endif // !defined(EA_DBDF59D0_734F_4bb6_A872_8BAE8C9F1528__INCLUDED_)
