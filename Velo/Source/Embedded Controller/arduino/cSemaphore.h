///////////////////////////////////////////////////////////
//  cSemaphore.h
//  Implementation of the Class cSemaphore
//  Created on:      02-May-2010 5:18:37 PM
//  Original author: Shawn
///////////////////////////////////////////////////////////

#if !defined(EA_F9A1B0FB_017E_4ffd_AF0A_E17837244E30__INCLUDED_)
#define EA_F9A1B0FB_017E_4ffd_AF0A_E17837244E30__INCLUDED_

#include "cList.h"

class cSemaphore
{

public:
	cSemaphore(unsigned int capacity, unsigned int available);
	~cSemaphore();

	bool Release();
	void Request();

private:
	cList BlockedList;
	int AvailableResources;
	int MaxAvailableResources;

};
#endif // !defined(EA_F9A1B0FB_017E_4ffd_AF0A_E17837244E30__INCLUDED_)
