///////////////////////////////////////////////////////////
//  cMemory.cpp
//  Implementation of the Class cMemory
//  Created on:      02-May-2010 5:18:21 PM
//  Original author: Shawn
///////////////////////////////////////////////////////////

#include "cMemory.h"

/**
 * Constructor
 */
cMemory::cMemory()
:Sema(1,0)
{
	page = CreateBlock( (void*)MEMORY_START, (size_t)MEMORY_SIZE );
}

/**
 * Destructor
 */
cMemory::~cMemory()
{

}

/**
 * Allocate new memory
 */
void* cMemory::Allocate(unsigned int size)
{
	Sema.Request();

	mBlock* loc = page;
	mBlock* newblock;

	//find a mem->stat == 'F' segment that fits the size reqirements
	while( loc && ( loc->stat == 'A' || ( loc->stat == 'F' && loc->size < size ) ) )
	{
		loc = loc->next;
	}
	if( !loc || size > loc->size )
	{
		Sema.Release();
		return 0;
	}

	//If the location is the size of the block
	//or the location is less then the size of the what’s needed without room to allocate another block
	if(    loc->size == size
		|| loc->size < (size + (unsigned int)sizeof(mBlock)) )
	{
		//Set the block to 'A'llocated
		loc->stat = 'A';
	}
	else
	{
		//The new 'F'ree block is located starting at the current location
		//plus the size of the block being allocated.
		newblock = (mBlock*)((unsigned int)loc
				 + (unsigned int)sizeof(mHeader)
				 + (unsigned int)size);

		//The size of the new 'F'ree block is the size of what remains after
		newblock->size = loc->size - size - (unsigned int)sizeof(mHeader);
		//The new 'F'ree block needs to be flagged as free
		newblock->stat = 'F';
		//And the new 'F'ree block's next pointer 
		newblock->next = loc->next;

		//Now to deal with the location itself
		//The 'A'llocated block size changed to the size of what was requested
		loc->size = size;
		//It's also 'A'llocated so flag it as so.
		loc->stat = 'A';
		//Now we need to keep track of where we go from this, which is to the new next block
		loc->next = newblock;	
	}

	Sema.Release();

	//Finally we need to return the location of where the user will store the data.
	return (void*)&loc->data;
}

/**
 * Free memory
 */
bool cMemory::Free(void* block)
{
	Sema.Request();

	//From the location of the data back up the size of the header
	mBlock* mem = (mBlock*)((unsigned int)block - (unsigned int)sizeof(mHeader));

	//If the block isnt 'A'llocated break
	if(mem->stat != 'A')
	{
		Sema.Release();
		return true;
	}
	//Set the block to a free block
	mem->stat = 'F';

	Sema.Release();
	return false;
}

/**
 * Initialize the memory block
 */
mBlock* cMemory::CreateBlock(void* location, unsigned int size)
{
	Sema.Request();

	mBlock* mem = (mBlock*)location;

	mem->size = size - (unsigned int)sizeof(mHeader);
	mem->stat = 'F';
	mem->next = 0;
	
	Sema.Release();
	
	return mem;
}