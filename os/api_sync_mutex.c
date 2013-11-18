#ifdef MUTEX_SECURE

#include "kernel_scheduler.h"
#include "kernel_action.h"
#include "api_sync_mutex.h"
#include "kernel_pcb_list.h"
#include "api_led.h"
#include "../generic/sleep.h"

void
sync_mutex_init(sync_mutex_t * mutex)
{
	mutex->mToken = true;
	kernel_pcb_list_init(&mutex->mProcessBlocked);
}

void
sync_mutex_lock(sync_mutex_t * mutex)
{
	kernel_pause_scheduler();

	if (mutex->mToken)
	{
		mutex->mToken = false;
	
		//Adds the mutex locked to the current process' PCB
		kernel_running_pcb->mMutexPossessed = kernel_mutex_list_insert(kernel_running_pcb->mMutexPossessed, mutex);

		kernel_resume_scheduler();
		return;
	}

	kernel_pcb_pause(&mutex->mProcessBlocked, kernel_running_pcb);

	kernel_resume_scheduler();
}

int
sync_mutex_lock_secure(sync_mutex_t * mutex)
{
	if(kernel_deadlock_check(mutex) == -1)
	{
		return -1;
	}
	
	sync_mutex_lock(mutex);
	
	return 0;
}

void
sync_mutex_unlock(sync_mutex_t * mutex)
{
	kernel_pause_scheduler();
	
	if(kernel_pcb_list_first(&mutex->mProcessBlocked))
	{
		//Remove the mutex locked from the started process
		kernel_running_pcb->mMutexPossessed = kernel_mutex_list_remove(kernel_running_pcb->mMutexPossessed, mutex);
	
		kernel_pcb_start(mutex->mProcessBlocked.mFirst);
	
		kernel_resume_scheduler();
		return;
	}

	mutex->mToken = true;

	kernel_resume_scheduler();
}

int
kernel_deadlock_check(sync_mutex_t * mutex)
{
	//No deadlock if the mutex is unlocked or if the current process owns no mutex
	if(mutex->mToken || kernel_running_pcb->mMutexPossessed == 0)
	{
		return 0;
	}
	
	return private_kernel_deadlock_check(kernel_running_pcb, mutex, true);
}

int
private_kernel_deadlock_check(kernel_pcb_t * processBlocked, sync_mutex_t * mutexSeeked, bool first)
{
	kernel_pcb_t * firstBlockedProcessCaused, * blockedProcessCaused;
	kernel_mutex_list_t * firstMutexPossessed, * mutexPossessed;

	//A deadlock is detected if a process different than the calling process owns the mutex this one want to lock,
	//and if there is a blocking path between these two processes
	if(!first && kernel_mutex_list_contains(processBlocked->mMutexPossessed, mutexSeeked))
	{
		deadlock_detected();
		return -1;
	}

	//Mutex possessed by the current process
	firstMutexPossessed = processBlocked->mMutexPossessed;
	mutexPossessed = firstMutexPossessed;

	//If the current process owns at least one mutex
	if(firstMutexPossessed)
	{
		//Iterating the mutex possessed list
		do
		{
			//List of process blocked by trying to lock the current mutex
			firstBlockedProcessCaused = mutexPossessed->mutex->mProcessBlocked.mFirst;
			blockedProcessCaused = firstBlockedProcessCaused;

			if(firstBlockedProcessCaused)
			{
				//Iterating the blocked proccess list
				do
				{
					//Recursive call
					if(private_kernel_deadlock_check(blockedProcessCaused, mutexSeeked, false) == -1)
					{
						return -1;
					}
					//Iterating to next blocked process
					blockedProcessCaused = blockedProcessCaused->mNext;
				}
				while(firstBlockedProcessCaused != blockedProcessCaused);
			}

			//Iterating to next possessed mutex
			mutexPossessed = mutexPossessed->next;
		}
		while(firstMutexPossessed != mutexPossessed);
	}

	return 0;
}

void deadlock_detected()
{
	int i;

	for(i = 0; i < 20; ++i)
	{
		led_on();
		generic_usleep(100000);
		led_off();
		generic_usleep(100000);
	}
	
}

#endif
