
#include "process.h"
#include "hw.h"

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

void
start_sched()
{
    init_hw();

    //set_next_tick_and_enable_timer_irq();
    ENABLE_IRQ();
}

//------------------------------------------------------------------------
int
kernel_main(void)
{
    // create kernel process
    process_create((process_func_t)0, (void *)0);

    // create kernel processes
    uint32_t ping_start = 17;
    uint32_t pong_start = 33;

    uint32_t ping_pid = process_create((process_func_t)ping, &ping_start);
    uint32_t pong_pid = process_create((process_func_t)pong, &pong_start);

    process_start(ping_pid);
    process_start(pong_pid);

    start_sched();

    while ( 1 )
    {
        //process_yield();
    }

    return 0;
}
