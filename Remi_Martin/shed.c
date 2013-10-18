#include "shed.h"
#include "process.h"
#include "list.h"
#include "dispatcher.h"
#include "hw.h"

int create_process(int stack_size, func_t f, void * args)
{
  pcb_s * pcb = 0;
  init_pcb(&pcb, f, stack_size, args);
  next_running = insert(next_running, pcb);
  return 0;
}

void start_current_process()
{
  ((func_t)next_running->previous->pcb->mPC) (next_running->pcb->args);
}

void start_sched()
{
	init_hw();
	ENABLE_IRQ();
}
