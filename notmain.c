
#include "process.h"

void
ping(uint32_t * args)
{
    uint32_t cpt = *args;

    while (1) {
        cpt++;
        process_yield();
    }
}

void
pong(uint32_t * args)
{
    uint32_t cpt = *args;

    process_exit();

    while (1) {
        cpt += 2;
        process_yield();
    }
}


//------------------------------------------------------------------------
int
notmain ( void )
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

    while ( 1 )
    {
        process_yield();
    }

    return 0;
}
