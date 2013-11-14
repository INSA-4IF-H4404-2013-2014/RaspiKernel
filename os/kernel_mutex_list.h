#ifndef _H_KERNEL_MUTEX_LIST
#define _H_KERNEL_MUTEX_LIST

#ifdef MUTEX_SECURE
#include "api_sync_mutex.h"

typedef struct kernel_mutex_list_s
{
	sync_mutex_t * mutex;
	struct kernel_mutex_list_t * previous;
	struct kernel_mutex_list_t * next;
} kernel_mutex_list_t;

kernel_mutex_list_t * kernel_mutex_list_insert ( kernel_mutex_list_t * list, sync_mutex_t * mutex );
kernel_mutex_list_t * kernel_mutex_list_remove ( kernel_mutex_list_t * list, sync_mutex_t * toDelete );

#endif
#endif