///////////////////////////////////////////////////////////
//  cGPS.h
//  Implementation of the Class cGPS
//  Created on:      05-May-2010 3:28:22 AM
//  Original author: shawn.mcginnis
///////////////////////////////////////////////////////////

#if !defined(EA_E7EC9F3D_4D78_465b_9651_5B68FE7C4DB6__INCLUDED_)
#define EA_E7EC9F3D_4D78_465b_9651_5B68FE7C4DB6__INCLUDED_

#include "cDigital.h"

/**
 * The GPS  class will be the interface between internal software and the hardware
 * GPS.
 */
class cGPS : public cDigital
{

public:
	cGPS();
	virtual ~cGPS();

	virtual bool Update();

};
#endif // !defined(EA_E7EC9F3D_4D78_465b_9651_5B68FE7C4DB6__INCLUDED_)
