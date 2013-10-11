
#include "dispatcher.h"

void
ping()
{
  int cpt = 1;

  while (1) {
    cpt++;
    yield();
  }
}

void
pong()
{
  int cpt = 1;

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
	create_process((func_t)notmain);

	// create kernel processes
	create_process(ping);
	create_process(pong);

	while ( 1 )
	{
		yield();
	}

	return 0;
}
