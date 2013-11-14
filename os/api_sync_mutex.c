#ifdef MUTEX_SECURE
#include "api_sync_mutex.h"

void
sync_mutex_init(sync_mutex_t * mutex)
{
	mutex->mProcessBlocked = kernel_pcb_list_init(&mutex->mProcessBlocked);
	mutex->mToken = true;
}

void
sync_mutex_lock(sync_mutex_t * mutex)
{
	kernel_pause_scheduler();

    if (mutex->mToken)
    {
        mutex->mToken = false;
		
		//Adds the mutex locked to the current process' PCB
		kernel_mutex_list_insert(mMutexPossessed, kernel_running_pcb);

        kernel_resume_scheduler();
        return;
    }

    kernel_pcb_pause(&mutex->mProcessBlocked, kernel_running_pcb);

    kernel_resume_scheduler();
}

int
sync_mutex_lock_secure(sync_mutex_t * mutex)
{
	//TODO : deadlocks algorithm
	
	sync_mutex_lock(sync_mutex_t * mutex);
	
	return 0;
}

 void
sync_mutex_unlock(sync_mutex_t * mutex)
{
    kernel_pause_scheduler();
	
	if(mutex->mProcessBlocked)
	{
		//Remove the mutex locked from the started process
		kernel_mutex_list_remove(kernel_running_pcb->mMutexPossessed, mutex);
		
		kernel_pcb_start(mutex->mProcessBlocked.mFirst);
		
		kernel_resume_scheduler();
		return;
	}

    mutex->token = true;

    kernel_resume_scheduler();
}
#endif
