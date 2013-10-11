#include "list.h"
#include "allocateMemory.h"

Tmaillon * insert ( Tmaillon * list, struct _pcb_s * pcb )
{
	Tmaillon * newMaillon = (Tmaillon * ) AllocateMemory ( sizeof ( Tmaillon) );
	newMaillon->pcb = pcb;
	if ( list )
	{
		newMaillon->next = list;
		newMaillon->previous = list->previous;
		list->previous = newMaillon;
		newMaillon->previous->next = newMaillon;
	}
	else
	{
		newMaillon->next = newMaillon;
		newMaillon->previous = newMaillon;
		list = newMaillon;
	}
	
	return list;
}
