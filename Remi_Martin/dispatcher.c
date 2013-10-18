#include "process.h"
#include "dispatcher.h"
#include "shed.h"

/*
#define SWITCH_REGISTER(i) \
        __asm ("mov %0, r" #i : "=r"(current_pcb->mR[i])); \
        __asm ("mov r" #i ", %0" : : "r"(pcb->mR[i]))
*/

void ctx_switch()
{
	if(next_running->previous->pcb->state == PCB_TERMINATED)
	{
		next_running = remove(next_running->previous);
	}
	else
	{
		if(next_running->previous->pcb->state == PCB_RUNNING)
		{
			//Saving old context
			__asm volatile ("push {r0-r12, lr}");
		}

		if(next_running->previous->pcb->state == PCB_TERMINATED)
		{
			next_running = remove(next_running->previous);
		}
		__asm volatile ("mov %0, sp" : "=r"(next_running->previous->pcb->mSP));
	}


	//Restoring new context
	if(next_running)
	{
		__asm volatile ("mov sp, %0" : : "r"(next_running->pcb->mSP));

		if(next_running->pcb->state == PCB_RUNNING)
		{
			__asm volatile ("pop {r0-r12, lr}");
		}
	
		if(next_running->pcb->state == PCB_NEW)
		{
			next_running->pcb->state = PCB_RUNNING;
			next_running = next_running->next;
			start_current_process();
		}

		next_running->pcb->state = PCB_RUNNING;
		next_running = next_running->next;
	}
}

void exit_process()
{
	next_running->previous->pcb->state = PCB_TERMINATED;
	ctx_switch();
}

