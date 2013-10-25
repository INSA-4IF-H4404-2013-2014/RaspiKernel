#include "process.h"



void init_pcb(struct pcb_s* pcb, func_t f, void* args, unsigned int stack_size)
{
	pcb->sp = AllocateMemory(stack_size);
	pcb->sp = &((pcb->sp)[stack_size-1]);
	pcb->lr = (unsigned int) f;
	pcb->args = args;
	pcb->running = READY;
}

void free_pcb(struct pcb_s* pcb)
{
	FreeAllocatedMemory(pcb->sp);
}
