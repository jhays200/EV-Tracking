/******************************************************************************
	Linked List for Thread Context
******************************************************************************/
#include "cList.h"

cList::cList()
{
	First = 0;
	Last = 0;
}
cList::~cList()
{
	First = 0;
	Last = 0;
}

/**************************************************************
* Purpose:  Removes a element from the list
*   Entry:  The data of the element to remove
*    Exit:  Returns a int true on success
**************************************************************/
cContext* cList::Pop( void )
{
	cContext* temp;

	if( First == 0 )
	{
		return (cContext*)0;
	}

	temp = First;
	First = First->next;

	if( First )
		First->prev = 0;

	if( First == 0 )
		Last = 0;

	return temp;
}

cContext* cList::Pop( unsigned int pid )
{	
	cContext* cur;
	cContext* temp;

	cContext* rc;

	//Empty list throw error
	if( First == 0 || pid == 0 )
	{
		rc = (cContext*)0;
	}
	//If deleting head
	else if( First->pid == pid )
	{
		temp = First;
		First = First->next;

		if( First )
			First->prev = 0;

		rc = temp;
	}
	//If deleting tail
	else if( Last->pid == pid )
	{
		temp = Last;
		Last = Last->prev;

		if( Last )
			Last->next = 0;

		rc = temp;
	}
	else
	{
		cur = First;
		//Find the node
		while ( cur != 0 && cur->pid != pid )
		{
			cur = cur->next;
		}
		//Unless you cant find it
		if(cur == 0)
		{
			rc = (cContext*)0;
		}
		//If you can delete the node
		else
		{
			cur->prev->next = cur->next;
			cur->next->prev = cur->prev; 
			rc = cur;
		}
	}
	//Fix the tail ptr if nessasary
	if( First == 0 )
		Last = 0;

	return rc;
	
}

/**************************************************************
* Purpose:  Adds a value at the end of the list
*   Entry:  The value to add
*    Exit:  Returns true on success
**************************************************************/ 
bool cList::Push( cContext* element )
{	
	if( !element )
		return false;

	element->next = 0;
	element->prev = 0;

	if( First == 0 )
	{
		Last = element;
		First = element;
	}
	else
	{
		// Set the next pointer to the current node
		element->prev = Last;

		// Set the new node to the head
		Last->next = element;	
		Last = element;
		element->next = 0; 
	}

	return true;	
}
