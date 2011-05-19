///////////////////////////////////////////////////////////
//  cKernel.h
//  Implementation of the Class cKernel
//  Created on:      02-May-2010 5:18:14 PM
//  Original author: Shawn
///////////////////////////////////////////////////////////
#if !defined(EA_79374196_83DE_42d9_B41E_A4A1884E8F91__INCLUDED_)
#define EA_79374196_83DE_42d9_B41E_A4A1884E8F91__INCLUDED_

#include "cProcesses.h"
#include "cMemory.h"
#include "cClock.h"

class cKernel
{
public:
	cKernel();
	~cKernel();

    cMemory Memory;
    cProcesses Processes;
    cClock Clock;

    bool Initialize(void);
};

extern cKernel Kernel;

#endif // !defined(EA_79374196_83DE_42d9_B41E_A4A1884E8F91__INCLUDED_)