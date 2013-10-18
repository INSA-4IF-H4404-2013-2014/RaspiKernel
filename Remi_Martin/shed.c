#include "shed.h"
#include "process.h"
#include "list.h"
#include "dispatcher.h"

void create_process(func_t f, void * args)
{
  pcb_s * pcb = 0;
  init_pcb(&pcb, f, STACK_SIZE, args);
  next_running = insert(next_running, pcb);
}

void start_current_process()
{
  ((func_t)next_running->previous->pcb->mPC) (next_running->pcb->args);
}
