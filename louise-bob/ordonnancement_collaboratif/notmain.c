#include "process.h"
#include "dispatcher.h"


const unsigned int STACK_SIZE = 128;

//struct ctx_s ctx_A;
//struct ctx_s ctx_B;
struct ctx_s ctx_init;

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

void funcA()
{
	int cptA = 0;
	while(1) 
	{
		cptA ++;
		yield(&ctx_B );
	}
}

void funcB()
{
	int cptB = 1;
	while(1) 
	{
		cptB += 2;
		yield(&ctx_A);
	}
}

//------------------------------------------------------------------------
int notmain (void)
{
  init_ctx(&ctx_A, funcA, STACK_SIZE);
  init_ctx(&ctx_B, funcB, STACK_SIZE);

  current_ctx = &ctx_init;

  yield(&ctx_A);
  
  return 0;
}
