///////////////////////////////////////////////////////////
//  cKernel.cpp
//  Implementation of the Class cKernel
//  Created on:      02-May-2010 5:18:14 PM
//  Original author: Shawn
///////////////////////////////////////////////////////////

#include "cKernel.h"

cKernel::cKernel()
{

}

cKernel::~cKernel()
{

}

bool cKernel::Initialize(void)
{
    //Start and save the scheduler
    Processes.Spawn((void*)Kernel.Processes.Scheduler, (unsigned short)0xF);
}