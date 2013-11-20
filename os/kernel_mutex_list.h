#ifndef _H_KERNEL_MUTEX_LIST
#define _H_KERNEL_MUTEX_LIST

#ifdef MUTEX_SECURE
#include "api_sync_mutex.h"

typedef struct sync_mutex_s sync_mutex_t;


/*
 * @infos: Double linked list containing mutexes
 */
typedef struct kernel_mutex_list_s
{
	//The mutex
	sync_mutex_t * mutex;
	
	//Previous element
	struct kernel_mutex_list_s * previous;
	
	//Next element
	struct kernel_mutex_list_s * next;
} kernel_mutex_list_t;

/*
 * @infos: returns 1 if the list contains the specified object
 * @param The list to search in
 * @param The object to look for
 * @return 1 if the list contains the specified object
 */
int kernel_mutex_list_contains ( kernel_mutex_list_t * list, sync_mutex_t * mutex );

/*
 * @infos: pushes a mutex at the end of the given list
 * @param The mutex list
 * @param The mutex to insert
 * @return The updated list
 */
kernel_mutex_list_t * kernel_mutex_list_insert ( kernel_mutex_list_t * list, sync_mutex_t * mutex );

/*
 * @infos: remove a specified object from the given list
 * @param The list to search in
 * @param The object to look for
 * @return The updated list
 */
kernel_mutex_list_t * kernel_mutex_list_remove ( kernel_mutex_list_t * list, sync_mutex_t * toDelete );

#endif
#endif
