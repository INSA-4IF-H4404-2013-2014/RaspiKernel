
#include "kernel_process.h"
#include "hw.h"



//------------------------------------------------------------------------

void
main_process(void);


//------------------------------------------------------------------------

void
ping(uint32_t * args)
{
    uint32_t cpt = *args;

    while (1) {
        cpt++;
    }
}

void
pong(uint32_t * args)
{
    uint32_t cpt = *args;
    uint32_t i;

    for (i = 0; i < 16; i++)
    {
        cpt *= cpt;
    }
}


//------------------------------------------------------------------------
int
kernel_main(void)
{
    // create kernel process
    process_create((process_func_t)0, (void *)0);

    // create the main process
    uint32_t main_process_PID = process_create((process_func_t) main_process, 0);
    process_start(main_process_PID);

    // create kernel processes
    uint32_t ping_start = 17;
    uint32_t pong_start = 33;

    uint32_t ping_pid = process_create((process_func_t)ping, &ping_start);
    uint32_t pong_pid = process_create((process_func_t)pong, &pong_start);

    process_start(ping_pid);
    process_start(pong_pid);

    init_hw();

    ENABLE_IRQ();

    while ( 1 )
    {
        //process_yield();
    }

    return 0;
}
