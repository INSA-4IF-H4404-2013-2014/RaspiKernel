
#include "dispatcher.h"

void
ping(int * args)
{
    int cpt = *args;

    while (1) {
        cpt++;
        process_yield();
    }
}

void
pong(int * args)
{
    int cpt = *args;

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
	process_create((func_t)0, (void *)0);

	// create kernel processes
	int ping_start = 17;
	int pong_start = 33;

	process_create((func_t)ping, &ping_start);
	process_create((func_t)pong, &pong_start);

	while ( 1 )
	{
		process_yield();
	}

	return 0;
}
