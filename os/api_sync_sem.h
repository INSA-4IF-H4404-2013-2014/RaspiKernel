#ifndef _H_API_SYNC_SEM
#define _H_API_SYNC_SEM

#include "kernel_pcb.h"


/*
 * @infos: semaphore struct
 */
typedef struct sync_sem_s
{
    uint32_t mCoins;
    kernel_pcb_t * mFifoStart;
    kernel_pcb_t * mFifoEnd;
} sync_sem_t;


/*
 * @infos: initialises a <semaphore>
 *
 * @param <semaphore> : a non initialised semaphore
 * @param <coins> : number of initial coins
 */
void
sync_sem_init(sync_sem_t * semaphore, uint32_t coins);

/*
 * @infos: posts a given number of <coins> in a <semaphore>
 *
 * @param <semaphore> : an initialised semaphore
 * @param <coins> : number of coins to add
 */
void
sync_sem_post(sync_sem_t * semaphore, uint32_t coins);

/*
 * @infos: consume one coins in a <semaphore>
 *
 * @param <semaphore> : a non initialised semaphore
 */
void
sync_sem_wait(sync_sem_t * semaphore);

#endif
