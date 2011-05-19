///////////////////////////////////////////////////////////
//  cSemaphore.cpp
//  Implementation of the Class cSemaphore
//  Created on:      02-May-2010 5:18:38 PM
//  Original author: Shawn
///////////////////////////////////////////////////////////
#include "cSemaphore.h"
#include "cKernel.h"

/**
 * Constructor: Initialize the Semaphore
 */
cSemaphore::cSemaphore(unsigned int capacity, unsigned int available)
{
	AvailableResources = available;
	MaxAvailableResources = capacity;
}

/**
 * Destructor
 */
cSemaphore::~cSemaphore()
{
    //Return any blocked processes
    while( BlockedList.First )
	{
		BlockedList.First->state = ORPHANED;
		Kernel.Processes.Threads.Push( BlockedList.Pop() );
	}
}

/**
 * Semaphore: Release a resource
 */
bool cSemaphore::Release()
{
    Kernel.Processes.DisableInterrupts();

    //Only allow another if there is one available
    if ( AvailableResources > MaxAvailableResources )
	{	
		Kernel.Processes.EnableInterrupts();
		return false;
	}

    //If there is an thread blocked then allow it active
	if( BlockedList.First )
	{
		BlockedList.First->state = ACTIVE;
		Kernel.Processes.Threads.Push( BlockedList.Pop() );
	}
	
    //Release a resource
	AvailableResources++;
	
	Kernel.Processes.EnableInterrupts();
	return true;
}
/**
 * Sepaphore: Request a resource
 */
void cSemaphore::Request()
{
    Kernel.Processes.DisableInterrupts();

    //If there is no resources available block the thread
	if( AvailableResources == 0 )
	{		
		Kernel.Processes.CurrentProcess->state = BLOCKED;
		BlockedList.Push( Kernel.Processes.Threads.Pop( Kernel.Processes.CurrentProcess->pid ) );
		CauseThreadSwitch();
	}

    //Remove an available resource
    AvailableResources--;

	Kernel.Processes.EnableInterrupts(); 
}