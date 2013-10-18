#include "process.h"
#include "dispatcher.h"

void ping()
{
  int cpt = 1;

  while (cpt < 2)
  {
    cpt++;
    ctx_switch();
  }
  exit_process();
}

void pong()
{
  int cpt = 1;

  while (cpt < 3)
  {
    cpt += 2;
    ctx_switch();
  }
  exit_process();
}

//------------------------------------------------------------------------
int notmain ( void )
{
  create_process(ping, 0);
  create_process(pong, 0);

  ctx_switch();

  return 0;
}
