#ifndef _cList_H
#define _cList_H

#include "cContext.h"

class cList
{
public:
	cContext* First; // Pointer
	cContext* Last; // Pointer
	
	cList();
	~cList();
	cContext*	Pop		( unsigned int pid );
	cContext*	Pop		( void );
	bool		Push	( cContext* element );
};

#endif
