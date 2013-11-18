#ifdef OS_RASP
	#include "../os/api_process.h"
	#include "../os/api_sync_sem.h"
	#include "../os/api_sync_mutex.h"

	#ifdef MUTEX_SECURE
		#define generic_mutex sync_mutex_t
		#define generic_mutex_lock(mutex) sync_mutex_lock_secure(mutex)
	#else
		#define generic_mutex sync_sem_t
		#define generic_mutex_lock(mutex) sync_mutex_lock(mutex)
	#endif

	#define generic_mutex_init(mutex) sync_mutex_init(mutex)
	#define generic_mutex_unlock(mutex) sync_mutex_unlock(mutex)

	#define generic_sem sync_sem_t
	#define generic_sem_init(sem, value) sync_sem_init(sem, value)
	#define generic_sem_post(sem) sync_sem_post(sem, 1)
	#define generic_sem_wait(sem) sync_sem_wait(sem)

	#define generic_thread_t uint32_t

	#define generic_thread_create(ptr, func, params) \
		*ptr = process_create(func, params);\
		process_start(*ptr);

#else
	#include <pthread.h>
	#include <sys/types.h>
	#include <sys/sem.h>

	#define generic_mutex pthread_mutex_t
	#define generic_mutex_init(mutex) pthread_mutex_init(mutex, NULL)
	#define generic_mutex_lock(mutex) pthread_mutex_lock(mutex)
	#define generic_mutex_unlock(mutex) pthread_mutex_unlock(mutex)

	#define generic_sem sem_t
	#define generic_sem_init(sem, value) sem_init(sem, 0, value)
	#define generic_sem_post(sem) sem_post(sem)
	#define generic_sem_wait(sem) sem_wait(sem)

	#define generic_thread_t pthread_t

	#define generic_thread_create(ptr, func, params) pthread_create(ptr, NULL, func, params)
#endif

