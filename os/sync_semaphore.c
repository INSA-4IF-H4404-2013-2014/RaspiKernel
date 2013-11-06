
#include "kernel_scheduler.h"
#include "sync_semaphore.h"

void
sync_sem_init(sync_sem_t * semaphore)
{
    semaphore->mCoins = 0;
    semaphore->mFifoStart = nullptr;
    semaphore->mFifoEnd = nullptr;
}

void
sync_sem_post(sync_sem_t * semaphore, uint32_t coins)
{
    kernel_pause_scheduler();

    while (coins)
    {
        if (semaphore->mFifoStart == nullptr)
        {
            break;
        }

        kernel_pcb_t * pcb = semaphore->mFifoStart;

        pcb->mState = PCB_READY;
        semaphore->mFifoStart = pcb->mNextFifo;

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

        kernel_pause_scheduler();
        return;
    }

    kernel_pcb_t * current = kernel_current_pcb;

    if (semaphore->mFifoStart)
    {
        semaphore->mFifoEnd->mNextFifo = current;
    }
    else
    {
        semaphore->mFifoStart = current;
    }

    current->mNextFifo = nullptr;
    semaphore->mFifoEnd = current;

    kernel_resume_scheduler();
}
