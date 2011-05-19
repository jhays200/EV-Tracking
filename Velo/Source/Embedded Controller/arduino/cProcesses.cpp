///////////////////////////////////////////////////////////
//  cProcesses.cpp
//  Implementation of the Class cProcesses
//  Created on:      02-May-2010 5:18:32 PM
//  Original author: Shawn
///////////////////////////////////////////////////////////

#include "cProcesses.h"
#include "cKernel.h"

/**
 * Constructor
 */
cProcesses::cProcesses()
{    
    //Create a context for main
    CurrentProcess = (cContext*)Kernel.Memory.Allocate(sizeof(cContext));
    
    ///Setup the Context
	CurrentProcess->pid = 1;
	CurrentProcess->state = ACTIVE;	
	CurrentProcess->priority = 0; 

    //Add it to the threads list
	Threads.Push( CurrentProcess ); 
}

/**
 * Destructor
 */
cProcesses::~cProcesses()
{ }

/**
 * Spawn New Thread
 */
unsigned int cProcesses::Spawn(void (*function)(), unsigned int priority)
{
    //Allocate stack space
    void* newstack = Kernel.Memory.Allocate(STACKSIZE);
	if( !newstack )
	{
		return 0;
	}

    //Allocate context space
	cContext* newcontext = (cContext*)Kernel.Memory.Allocate(sizeof(cContext));
	if( !newcontext )
	{
        //If it failed get rid of the stack space
		Kernel.Memory.Free( newstack );
		return 0;
	}

    void* sp = (void*)0x0000;//TODO: Math! ((u16)newstack + (u16)STACKSIZE - sizeof(sStackContext));

    //Setup the context
	newcontext->pid = ++PIDCount;
	newcontext->state = ACTIVE;
	newcontext->priority = priority;
    newcontext->stack.pointer = sp;

    //Add the context to the threads list
	Threads.Push( newcontext );	

	return newstack ? PIDCount : 0;
}

/**
 * Kill Current Thread
 */
void cProcesses::Kill()
{
    CurrentProcess->state = KILLED;
	CauseThreadSwitch();
}

/**
 * Thread Yield Processor. Timeout allows sleep timeout.
 */
void cProcesses::Yield(unsigned int milliseconds)
{
    //If you need to set a timeout
	if( milliseconds )
	{
        //Use the system clock and add the timeout
		CurrentProcess->timeout = Kernel.Clock.GetSC() + milliseconds;
		CurrentProcess->state = SUSPENDED;
	}
	CauseThreadSwitch();
}

/**
 * Thread Scheduler
 */
void cProcesses::Scheduler()
{
    cContext* cur;
	cContext* nxt;
	while(1)
	{
		DisableInterrupts();

		//Schedule the next set of threads
        cur = Threads.First;
		nxt = 0;
		while( cur )
		{	
			nxt = cur->next;			
			switch( cur->state )
			{
			case SUSPENDED:
                //Check to see if the thread is out of its suspended state
                if( cur->timeout <= Kernel.Clock.GetSC() )
                {
					cur->state = ACTIVE;
				    Schedule.Push( Threads.Pop( cur->pid ) );
                }
                break;

			case ACTIVE:
				Schedule.Push( Threads.Pop( cur->pid ) );
				break;

			case KILLED:
				Threads.Pop( cur->pid );
				Kernel.Memory.Free( cur->stack.start );
				Kernel.Memory.Free( cur );
				break;

			case BLOCKED:
				//TODO: Check timeout?
				break;

			case ORPHANED:
				//TODO: Something!
				break;

			default:
				break;
			}
			cur = nxt;
		}
		CauseThreadSwitch();
	}
}

/**
 * Disable Auto Thread Switch
 */
void cProcesses::DisableInterrupts( void )
{
    //TODO: Turn off timer.
	++InterruptFlag;
}

/**
 * Enable Timed Thread Switch
 */
void cProcesses::EnableInterrupts( bool force )
{
	--InterruptFlag;

	if( InterruptFlag < 1 || force )
	{
		InterruptFlag = 0;
		//TODO: Turn on Timer
	}
}