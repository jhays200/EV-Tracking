///////////////////////////////////////////////////////////
//  cBrake.h
//  Implementation of the Class cBrake
//  Created on:      05-May-2010 3:27:43 AM
//  Original author: shawn.mcginnis
///////////////////////////////////////////////////////////

#if !defined(EA_AA8289DD_E420_478d_B6DB_9517904FC703__INCLUDED_)
#define EA_AA8289DD_E420_478d_B6DB_9517904FC703__INCLUDED_

#include "cDigital.h"

/**
 * The Brake  class will be the interface between internal software and the
 * hardware brake.
 */
class cBrake : public cDigital
{

public:
	virtual bool Update();

};
#endif // !defined(EA_AA8289DD_E420_478d_B6DB_9517904FC703__INCLUDED_)
