#ifdef MUTEX_SECURE

#include "kernel_mutex_list.h"
#include "kernel_memory.h"

int kernel_mutex_list_contains ( kernel_mutex_list_t * list, sync_mutex_t * mutex )
{
	kernel_mutex_list_t * tmpList = list;

	if(list)
	{
		while(tmpList->mutex != mutex && tmpList->next != list)
		{
			tmpList = tmpList->next;
		}

		if(tmpList->mutex == mutex)
		{
			return 1;
		}
	}

	return 0;
}

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

	if(list)
	{
		while(tmpList->mutex != toDelete && tmpList->next != list)
		{
			tmpList = tmpList->next;
		}
		
		if(tmpList->mutex == toDelete)
		{
			kernel_mutex_list_t * maillonToDelete = tmpList;
			list = tmpList->next;
			tmpList->previous->next = tmpList->next;
			tmpList->next->previous = tmpList->previous;
			
			if(list->next == list)
			{
				list = 0;
			}
			
			kernel_deallocate_memory ( ( void * ) maillonToDelete );
		}
	}

	return list;
}
#endif
