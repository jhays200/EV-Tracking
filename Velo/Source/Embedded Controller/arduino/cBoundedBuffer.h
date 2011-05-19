///////////////////////////////////////////////////////////
//  cBoundedBuffer.h
//  Implementation of the Class cBoundedBuffer
//  Created on:      02-May-2010 5:17:50 PM
//  Original author: Shawn
///////////////////////////////////////////////////////////

#if !defined(EA_FF912297_D538_493c_840D_FA3A3EADE776__INCLUDED_)
#define EA_FF912297_D538_493c_840D_FA3A3EADE776__INCLUDED_

#define MAXITEMS 256

#include "cKernel.h"
#include "cSemaphore.h"

class cBoundedBuffer
{

public:
	cBoundedBuffer();
	virtual ~cBoundedBuffer();

	void Add(char item);
	char Remove();

private:
	cSemaphore Mutex;
	cSemaphore Full;
	cSemaphore Empty;
	char Buffer[MAXITEMS];
	unsigned int NextAdd;
	unsigned int NextRemove;

};
#endif // !defined(EA_FF912297_D538_493c_840D_FA3A3EADE776__INCLUDED_)
