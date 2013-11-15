#ifdef MUTEX_SECURE

#include "kernel_mutex_list.h"
#include "kernel_memory.h"

kernel_mutex_list_t * kernel_mutex_list_insert ( kernel_mutex_list_t * list, sync_mutex_t * mutex )
{
	kernel_mutex_list_t * newMaillon = (kernel_mutex_list_t * ) kernel_allocate_memory ( sizeof ( kernel_mutex_list_t) );
	newMaillon->mutex = mutex;
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

kernel_mutex_list_t * kernel_mutex_list_remove ( kernel_mutex_list_t * list, sync_mutex_t * toDelete )
{
	kernel_mutex_list_t * tmpList = list;
	kernel_mutex_list_t * maillonToDelete;

	if(list)
	{
		while(tmpList->mutex != toDelete && tmpList->next != list)
		{
			tmpList = tmpList->next;
		}
		
		if(tmpList->mutex == toDelete)
		{
			maillonToDelete = tmpList;
			list = tmpList->next;
			tmpList->previous->next = tmpList->next;
			tmpList->next->previous = tmpList->previous
			
			if(list->next = list)
			{
				list = 0;
			}
			
			FreeAllocatedMemory ( ( uint32_t ) maillonToDelete );
		}
	}

	return list;
}
#endif
