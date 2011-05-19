///////////////////////////////////////////////////////////
//  cCamera.h
//  Implementation of the Class cCamera
//  Created on:      05-May-2010 3:27:50 AM
//  Original author: Shawn
///////////////////////////////////////////////////////////

#if !defined(EA_D8510D81_B4FD_4e24_9A91_43DAD158F633__INCLUDED_)
#define EA_D8510D81_B4FD_4e24_9A91_43DAD158F633__INCLUDED_

#include "cDigital.h"

/**
 * The Camera  class will be the interface between internal software and the
 * hardware camera.
 */
class cCamera : public cDigital
{

public:
	cCamera();
	~cCamera();
	virtual bool Update();
};
#endif // !defined(EA_D8510D81_B4FD_4e24_9A91_43DAD158F633__INCLUDED_)
