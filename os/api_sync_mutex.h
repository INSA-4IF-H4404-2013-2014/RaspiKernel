#ifndef _H_API_SYNC_MUTEX
#define _H_API_SYNC_MUTEX

#ifdef MUTEX_SECURE
//---------------------------------------------------------------- MUTEX SECURE
#include "api_sync_sem.h"
#include "kernel_mutex_list.h"
#include "kernel_forward.h"

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
 * @infos: initialises a <mutex>
 *
 * @param <mutex>: a uninitialized mutex
 */
void
sync_mutex_init(sync_mutex_t * mutex);

/*
 * @infos: lock the <mutex>
 *
 * @param <mutex>: an initialised mutex
 */
void
sync_mutex_lock(sync_mutex_t * mutex);

/*
 * @infos: lock the <mutex> if this
 *         lock do not create a deadlock
 *
 * @param <mutex>: an initialised mutex
 * @return: 0 if the lock has been done, -1 else (deadlock prevention)
 */
int
sync_mutex_lock_secure(sync_mutex_t * mutex);

/*
 * @infos: unlock the <mutex>
 *
 * @param <mutex>: an initialised mutex
 */
void
sync_mutex_unlock(sync_mutex_t * mutex);

/*
 * @infos: check if the lock of the <mutex> by the current running
 * process will create a deadlock
 *
 * @param <mutex>: an initialised mutex
 * @return: 0 if the mutex can be securely locked, -1 if locking the mutex
 *          will create a deadlock
 */
int
kernel_deadlock_check(sync_mutex_t * mutex);


int
private_kernel_deadlock_check(kernel_pcb_t * processBlocked, sync_mutex_t * mutexSeeked, bool first);

void
deadlock_detected();

#else
//-------------------------------------------------------------- MUTEX STANDARD

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
 * @infos: unlock the <mutex>
 *
 * @param <mutex>: an initialised mutex
 */
#define sync_mutex_unlock(mutex) \
    sync_sem_post(mutex, 1)

#endif
#endif
