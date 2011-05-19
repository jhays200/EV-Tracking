///////////////////////////////////////////////////////////
//  cMemory.h
//  Implementation of the Class cMemory
//  Created on:      02-May-2010 5:18:21 PM
//  Original author: Shawn
///////////////////////////////////////////////////////////

#if !defined(EA_2F856545_DC92_4008_8DA0_88193EA7490E__INCLUDED_)
#define EA_2F856545_DC92_4008_8DA0_88193EA7490E__INCLUDED_

#include "cSemaphore.h"

#define MEMORY_START 0x00800060
#define MEMORY_SIZE  0x0000FFA0

struct mBlock
{
	unsigned int	size;
	char	stat;
	mBlock*	next;
	void*	data;
};

struct mHeader
{
	unsigned int	size;
	char	stat;
	mBlock*	next;
};

class cMemory
{

public:
	cMemory();
	~cMemory();

	void Initialize();
	void* Allocate(unsigned int size);
	bool Free(void* block);

private:
    mBlock* CreateBlock(void* location, unsigned int size);

	mBlock* page;
    cSemaphore Sema;

};
#endif // !defined(EA_2F856545_DC92_4008_8DA0_88193EA7490E__INCLUDED_)
