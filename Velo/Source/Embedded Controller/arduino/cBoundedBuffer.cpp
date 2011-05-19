///////////////////////////////////////////////////////////
//  cBoundedBuffer.cpp
//  Implementation of the Class cBoundedBuffer
//  Created on:      02-May-2010 5:17:50 PM
//  Original author: Shawn
///////////////////////////////////////////////////////////

#include "cBoundedBuffer.h"

cBoundedBuffer::cBoundedBuffer()
:Mutex(1,0), Full(MAXITEMS,0), Empty(MAXITEMS,MAXITEMS)
{
	NextAdd = 0;
	NextRemove = 0;
}

cBoundedBuffer::~cBoundedBuffer()
{

}

void cBoundedBuffer::Add(char item)
{
	Empty.Request();
	Mutex.Request();
	Buffer[NextAdd] = item;
	NextAdd = ++NextAdd % MAXITEMS;
	Mutex.Release(); 
	Full.Release();
}

char cBoundedBuffer::Remove()
{
    Full.Request(); 
	Mutex.Request();
	char ret_val = 0;
	ret_val = Buffer[NextRemove];	
	NextRemove = ++NextRemove % MAXITEMS;
	Mutex.Release(); 
	Empty.Release();
	return ret_val;
}