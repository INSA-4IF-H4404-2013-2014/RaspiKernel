#include "shed.h"
#include "process.h"
#include "list.h"
#include "dispatcher.h"

void create_process(func_t f, void * args)
{
  pcb_s * pcb = 0;
  init_pcb(pcb, f, STACK_SIZE, args);
  next_running = insert(next_running, pcb);
}

void yield()
{
	if(next_running)
	{
		pcb_s * newPcb = next_running->pcb;
		pcb_s * oldPcb = next_running->previous->pcb;
		next_running = next_running->next;
		ctx_switch(oldPcb, newPcb);
	}
}

void start_current_process()
{
  ((func_t)next_running->pcb->mPC) (next_running->pcb->args);
}
