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

		pcb_s * e = toDelete->pcb;
		unsigned int d = e->mSP;
		unsigned int f = (unsigned int) e->mSP;
		unsigned int a = (toDelete->pcb)->mSP;		
		b = (memory_element_t *)a;
		c =  (memory_element_t )a;

		FreeAllocatedMemory ( (memory_element_t *) toDelete->pcb->mSP );
		FreeAllocatedMemory ( ( uint32_t ) toDelete->pcb );
		FreeAllocatedMemory ( ( uint32_t ) toDelete );
	}

	return list;
}

