#ifndef _cContext_H
#define _cContext_H

#include "typedef.h"

/**
 * Identifies the state of a Thread
 */
enum eThreadState
{
	KILLED,
	ACTIVE,
	BLOCKED,
	ORPHANED,
	SUSPENDED
};

/**
 * Stack Context
 */
struct sStackInfo
{
	void* pointer;
	void* start;
};

/**
 * Thread Context
 */
struct cContext
{
	unsigned int pid;
	enum eThreadState state;

	sStackInfo stack;

	unsigned short priority; 

	unsigned long timeout;
	unsigned long rts;

	cContext* next;
	cContext* prev;
};

#endif
