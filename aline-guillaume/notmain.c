#include "process.h"
#include "switch.h"

struct ctx_s ctx_A;
struct ctx_s ctx_B;
struct ctx_s ctx_init;

void
ping()
{
  int cpt = 1;

  while (1) {
    cpt++;
    switch_to(&ctx_B);
  }
}

void
pong()
{
  int cpt = 1;

  while (1) {
    cpt += 2;
    switch_to(&ctx_A);
  }
}

//------------------------------------------------------------------------
int
notmain ( void )
{
  init_ctx(&ctx_A, ping, STACK_SIZE);
  init_ctx(&ctx_B, pong, STACK_SIZE);

  current_ctx = &ctx_init;

  switch_to(&ctx_A);

  return 0;
}
