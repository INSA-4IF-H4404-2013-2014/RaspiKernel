#include "sched.h"

void create_process(func_t f, void* args)
{
	struct pcb_s* pcb = (struct pcb_s*) AllocateMemory(sizeof(struct pcb_s));
	
	if(current_process) // if a process already exists
	{
		pcb->next = current_process;
		pcb->previous = current_process->previous;
		current_process->previous = pcb;
		if(current_process->next == current_process)
		{
			current_process->next = pcb;
		}
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
	// Attribute the new current_process
	current_process = current_process->next;
	
	// Switch context
	ctx_switch();
}

void exit()
{
	if(current_process->next == current_process)
	{
		free_pcb(current_process);
		current_process = 0;
	}
	else
	{
		// Remove the current_process from the list of processes
		(current_process->previous)->next = current_process->next;
		(current_process->next)->previous = current_process->previous;
	
		// Free the stack associated to the current_process
		free_pcb(current_process);
	
		// Attribute the new current_process
		current_process = current_process->next;
	}
}
