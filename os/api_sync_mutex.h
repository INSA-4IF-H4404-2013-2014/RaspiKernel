#ifndef _H_API_SYNC_MUTEX
#define _H_API_SYNC_MUTEX

#include "api_sync_sem.h"


/*
 * @infos: semaphore struct
 */
typedef sync_sem_t sync_mutex_t;


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
 * @param <mutex> : an initialised mutex
 */
#define sync_mutex_lock(mutex) \
    sync_sem_wait(mutex)

/*
 * @infos: unlock the <mutex>
 *
 * @param <mutex> : an initialised mutex
 */
#define sync_mutex_unlock(mutex) \
    sync_sem_post(mutex, 1)

#endif
