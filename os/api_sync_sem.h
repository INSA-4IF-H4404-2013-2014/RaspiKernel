#ifndef _H_API_SYNC_SEM
#define _H_API_SYNC_SEM

#include "kernel_pcb.h"


typedef struct sync_sem_s
{
    uint32_t mCoins;
    kernel_pcb_t * mFifoStart;
    kernel_pcb_t * mFifoEnd;
} sync_sem_t;


/*
 * @infos :
 */
void
sync_sem_init(sync_sem_t * semaphore);

void
sync_sem_post(sync_sem_t * semaphore, uint32_t coins);

void
sync_sem_wait(sync_sem_t * semaphore);

#endif
