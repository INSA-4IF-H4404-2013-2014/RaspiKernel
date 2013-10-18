#include "sched.h"

//struct ctx_s ctx_A;
//struct ctx_s ctx_B;
//struct ctx_s ctx_init;

/*
void ping()
{
  while (1)
  {
    yield(&ctx_B);
    yield(&ctx_B);
  }
}

void pong()
{
  while (1)
  {
    yield(&ctx_A);
    yield(&ctx_A);
    yield(&ctx_A);
  }
}
*/

void funcA()
{
	int cptA = 0;
	while(1) 
	{
		cptA ++;
		yield();
	}
	exit();
}

void funcB()
{
	int cptB = 1;
	while(1) 
	{
		cptB += 2;
		yield();
	}
	exit();
}

//------------------------------------------------------------------------
int notmain (void)
{
  create_process(funcA, 0);
  create_process(funcB, 0);

  yield();
  
  return 0;
}
