
#include "dispatcher.h"

void
ping(int * args)
{
  int cpt = *args;

  while (1) {
    cpt++;
    yield();
  }
}

void
pong(int * args)
{
  int cpt = *args;

  while (1) {
    cpt += 2;
    yield();
  }
}


//------------------------------------------------------------------------
int
notmain ( void )
{
	// create kernel process
	create_process((func_t)0, (void *)0);

	// create kernel processes
	int ping_start = 17;
	int pong_start = 33;

	create_process((func_t)ping, &ping_start);
	create_process((func_t)pong, &pong_start);

	while ( 1 )
	{
		yield();
	}

	return 0;
}
