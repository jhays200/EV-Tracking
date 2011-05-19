///////////////////////////////////////////////////////////
//  cClock.h
//  Implementation of the Class cClock
//  Created on:      02-May-2010 5:18:01 PM
//  Original author: Shawn
///////////////////////////////////////////////////////////

#if !defined(EA_4A964986_651B_48a3_B82A_4DE9E1662C93__INCLUDED_)
#define EA_4A964986_651B_48a3_B82A_4DE9E1662C93__INCLUDED_

#include "DateTime.h"
#include <DS1307.h>

/**
 * The Clock class will be the interface between internal software and the
 * hardware clock.
 */
class cClock
{
public:
	cClock();
	~cClock();

	unsigned int GetSC();
	bool SetRTC(DateTime value);
	DateTime GetRTC();

private:
    DateTime clock;
    DS1307 RTC;   
};
#endif // !defined(EA_4A964986_651B_48a3_B82A_4DE9E1662C93__INCLUDED_)
