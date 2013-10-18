#include "process.h"
#include "dispatcher.h"

void ping()
{
  int cpt = 1;

  while (cpt < 4)
  {
    cpt++;
  }
  exit_process();
}

void pong()
{
  int cpt = 1;

  while (cpt < 5)
  {
    cpt += 2;
  }
  exit_process();
}

//------------------------------------------------------------------------
int notmain ( void )
{
  create_process(STACK_SIZE, ping, 0);
  create_process(STACK_SIZE, pong, 0);

  start_sched();

  for ( ; ; )
  {
	
  }

  return 0;
}
