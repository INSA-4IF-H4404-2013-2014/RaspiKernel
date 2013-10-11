#include "process.h"
#include "dispatcher.h"

void ping()
{
  int cpt = 1;

  while (1) {
    cpt++;
    yield();
  }
}

void pong()
{
  int cpt = 1;

  while (1) {
    cpt += 2;
    yield();
  }
}

//------------------------------------------------------------------------
int notmain ( void )
{
  create_process(ping, 0);
  create_process(pong, 0);

  yield();

  return 0;
}
