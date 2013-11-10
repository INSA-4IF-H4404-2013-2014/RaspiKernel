
#include "kernel_pcb_list.h"
#include "kernel_scheduler.h"
#include "kernel_action.h"
#include "api_sync_sem.h"

void
sync_sem_init(sync_sem_t * semaphore, uint32_t coins)
{
    semaphore->mCoins = coins;
    kernel_pcb_list_init(&semaphore->mFifo);
}

void
sync_sem_post(sync_sem_t * semaphore, uint32_t coins)
{
    kernel_pause_scheduler();

    while (kernel_pcb_list_first(&semaphore->mFifo))
    {
        if (!coins)
        {
            kernel_resume_scheduler();
            return;
        }

        kernel_pcb_t * pcb;

        kernel_pcb_list_popf(&semaphore->mFifo, pcb);
        kernel_pcb_list_pushb(pcb->mSchedulerList, pcb);

        coins--;
    }

    semaphore->mCoins += coins;

    kernel_resume_scheduler();
}

void
sync_sem_wait(sync_sem_t * semaphore)
{
    kernel_pause_scheduler();

    if (semaphore->mCoins > 0)
    {
        semaphore->mCoins--;

        kernel_resume_scheduler();
        return;
    }

    kernel_pcb_t * pcb;

    kernel_pcb_list_popf(kernel_running_pcb->mSchedulerList, pcb);
    kernel_pcb_list_pushb(&semaphore->mFifo, pcb);

    kernel_scheduler_yield();

    // kernel_scheduler_yield() call kernel_resume_scheduler();
}

