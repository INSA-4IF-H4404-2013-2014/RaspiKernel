#ifdef OS_RASP
	#include "../os/api_process.h"
	#include "../os/api_sync_mutex.h"

	#define generic_mutex sync_mutex_t
	#define generic_sem sync_sem_t
	#define generic_mutex_init(mutex) sync_mutex_init(mutex)
	#define generic_mutex_lock(mutex) sync_mutex_lock(mutex)
	#define generic_mutex_unlock(mutex) sync_mutex_unlock(mutex)

	#define generic_thread_t uint32_t
#else
	#include <pthread.h>
	#include <sys/types.h>
	#include <sys/sem.h>

	#define generic_mutex pthread_mutex_t
	#define generic_sem int
	#define generic_mutex_init(mutex) pthread_mutex_init(mutex, NULL)
	#define generic_mutex_lock(mutex) pthread_mutex_lock(mutex)
	#define generic_mutex_unlock(mutex) pthread_mutex_unlock(mutex)

	#define generic_thread_t pthread_t
#endif

