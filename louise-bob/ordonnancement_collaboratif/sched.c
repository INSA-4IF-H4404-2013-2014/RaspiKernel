#include "sched.h"

void create_process(func_t f, void* args)
{
	struct pcb_s* pcb = (struct pcb_s*) AllocateMemory(sizeof(struct pcb_s));
	
	if(current_process) // if a process already exists
	{
		pcb->next = current_process;
		pcb->previous = current_process->previous;
		current_process->previous = pcb;
	}
	else // if no process is running
	{
		pcb->next = pcb;
		pcb->previous = pcb;
		current_process = pcb;
	}
	
	init_pcb(pcb, f, args, STACK_SIZE); // initialize the processus
}

void yield()
{
	current_process = current_process->next;
	
	//if(!current_process->running)
	//{
	//	start_current_process();
	//}
	//else
	//{
		ctx_switch(current_process->previous, current_process);
	//}
}

/*
void start_current_process()
{
	current_process->running = 1;
	__asm("mov lr, %0" : : "r"(current_process->lr));
}
*/
