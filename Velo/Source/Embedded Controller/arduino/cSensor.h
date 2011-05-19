///////////////////////////////////////////////////////////
//  cSensor.h
//  Implementation of the Class cSensor
//  Created on:      05-May-2010 3:28:51 AM
//  Original author: shawn.mcginnis
///////////////////////////////////////////////////////////

#if !defined(EA_89D90B21_FF81_4ed0_A3F0_82AFC527ED0D__INCLUDED_)
#define EA_89D90B21_FF81_4ed0_A3F0_82AFC527ED0D__INCLUDED_

#include "SensorID.h"
#include "DateTime.h"

/**
 * The abstract base class used for sensors.
 */
class cSensor
{
public:
	SensorID ID;

	cSensor();
	virtual ~cSensor();
	virtual bool Update() = 0;
	virtual void* Read() = 0;
	DateTime GetLastUpdate();
	void SetLastUpdate(DateTime newVal);

private:
	DateTime LastUpdate;
};
#endif // !defined(EA_89D90B21_FF81_4ed0_A3F0_82AFC527ED0D__INCLUDED_)
