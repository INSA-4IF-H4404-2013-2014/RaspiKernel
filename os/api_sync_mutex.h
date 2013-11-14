#ifndef _H_API_SYNC_MUTEX
#define _H_API_SYNC_MUTEX

#include "api_sync_sem.h"

//Boolean type
typedef enum {false, true} bool;

/*
 * @infos: mutex struct
 */
typedef struct sync_mutex_s
{
    kernel_pcb_list_t mProcessBlocked;
    bool mToken;
} sync_mutex_t;

/*
 * @infos: PCB struct linked with a possessed mutex list
 */
typedef struct kernel_pcb_mtx_s
{
	uint32_t mPID;
	
	//List of the mutex possessed by the current process
    sync_mutex_t *
} kernel_pcb_mtx_t;

kernel_pcb_list_t mGlobalProcessBlocked;


/*
 * @infos: initialises a <mutex>
 *
 * @param <mutex>: a uninitialized mutex
 */
#define sync_mutex_init(mutex) \
    sync_sem_init(mutex, 1)

/*
 * @infos: lock the <mutex>
 *
 * @param <mutex>: an initialised mutex
 */
#define sync_mutex_lock(mutex) \
    sync_sem_wait(mutex)

/*
 * @infos: consume one coin in a <semaphore>
 *         if this consumption do not create a deadlock
 *
 * @param <semaphore>: an initialised semaphore
 * @return: 0 if a coin has been taken, -1 else (deadlock prevention)
 */
int
sync_sem_wait_secure(sync_sem_t * semaphore)

/*
 * @infos: lock the <mutex> if this
 *         lock do not create a deadlock
 *
 * @param <mutex>: an initialised mutex
 * @return: 0 if the lock has been done, -1 else (deadlock prevention)
 */
#define sync_mutex_lock_secure(mutex) \
    sync_sem_wait_secure(mutex)

/*
 * @infos: unlock the <mutex>
 *
 * @param <mutex>: an initialised mutex
 */
#define sync_mutex_unlock(mutex) \
    sync_sem_post(mutex, 1)

#endif
