#include "process.h"
#include "dispatcher.h"
#include "shed.h"
#include "hw.h"


#define SWITCH_REGISTER(i) \
        __asm ("mov %0, r" #i : "=r"(current_pcb->mR[i])); \
        __asm ("mov r" #i ", %0" : : "r"(pcb->mR[i]))


void __attribute__((naked)) ctx_switch()
{
/*
	__asm volatile ("sub lr lr #4");
	__asm volatile ("srsdb sp! #13");
	__asm volatile ("cps #0x13");
*/
	__asm volatile ("push {r0-r12, lr}");

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

		__asm volatile ("mov %0, sp" : "=r"(next_running->previous->pcb->mSP));
	}


	//Restoring new context
	if(next_running)
	{
		__asm volatile ("mov sp, %0" : : "r"(next_running->pcb->mSP));

		__asm volatile ("pop {r0-r12, lr}");
	
		if(next_running->pcb->state == PCB_NEW)
		{
			next_running->pcb->state = PCB_RUNNING;
			next_running = next_running->next;
			start_current_process();
		}

		next_running->pcb->state = PCB_RUNNING;
		next_running = next_running->next;

		//Rearming timer
		set_next_tick_and_enable_timer_irq();
		ENABLE_IRQ();
	}
	__asm volatile ("pop {r0-r12, lr}");
}

void exit_process()
{
	next_running->previous->pcb->state = PCB_TERMINATED;
	ctx_switch();
}

