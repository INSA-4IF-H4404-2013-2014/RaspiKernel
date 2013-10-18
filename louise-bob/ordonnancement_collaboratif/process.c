#include "process.h"
#include "allocateMemory.h"


void init_pcb(struct pcb_s* pcb, func_t f, void* args, unsigned int stack_size)
{
	pcb->sp = AllocateMemory(stack_size);
	//pcb->sp += (stack_size - 1) * 4;
	pcb->sp = &((pcb->sp)[stack_size-1]);
	pcb->lr = f;
	pcb->args = args;
	pcb->running = 0;
}
