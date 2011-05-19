///////////////////////////////////////////////////////////
//  cCruseControlMode.h
//  Implementation of the Class cCruseControlMode
//  Created on:      05-May-2010 3:27:59 AM
//  Original author: Shawn
///////////////////////////////////////////////////////////

#if !defined(EA_E925C637_928B_4a27_A7B1_857C048ED1EC__INCLUDED_)
#define EA_E925C637_928B_4a27_A7B1_857C048ED1EC__INCLUDED_

#include "cPowerMode.h"

/**
 * This class defines the power control scheme for cruise control
 */
class cCruseControlMode : public cPowerMode
{

public:
	cCruseControlMode();
	virtual ~cCruseControlMode();

};
#endif // !defined(EA_E925C637_928B_4a27_A7B1_857C048ED1EC__INCLUDED_)
