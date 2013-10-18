#include "list.h"
#include "allocateMemory.h"
#include "process.h"

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

Tmaillon * remove ( Tmaillon * toDelete )
{
	Tmaillon * list = 0;

	if(toDelete)
	{
		if(toDelete->next != toDelete)
		{
			list = toDelete->next;
			toDelete->previous->next = toDelete->next;
			toDelete->next->previous = toDelete->previous;
		}

		FreeAllocatedMemory ( toDelete->pcb->mSP );
		FreeAllocatedMemory ( (uint32_t *) toDelete->pcb );
		FreeAllocatedMemory ( (uint32_t *) toDelete );
	}

	return list;
}

