
#include "os/api_process.h"
#include "os/api_sync_sem.h"


static void
sub_process(sync_sem_t * sem_array)
{
    uint32_t i = 1;

    for ( ; ; )
    {
        sync_sem_wait(sem_array + 0);
        i += 2;
        sync_sem_post(sem_array + 1, 1);
    }
}

void
main_process(void)
{
    sync_sem_t sem_array[2];

    sync_sem_init(&sem_array[0], 0);
    sync_sem_init(&sem_array[1], 0);

    uint32_t i = 0;

    uint32_t PID = process_create((process_func_t) sub_process, sem_array);

    process_start(PID);

    for ( ; ; )
    {
        i += 2;
        sync_sem_post(sem_array + 0, 1);
        sync_sem_wait(sem_array + 1);
    }
}

