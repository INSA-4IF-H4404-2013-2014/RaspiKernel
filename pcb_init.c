
#include "pcb.h"
#include "allocateMemory.h"

void init_pcb(struct pcb_s* pcb, func_t f, uint32_t stack_size)
{
	static uint32_t id = 0;

	pcb->mState = PCB_READY;
	pcb->mPID = id++;
	pcb->mStack = (uint32_t) AllocateMemory(stack_size);
	pcb->mPC = (uint32_t) f;
	pcb->mSP = pcb->mStack + stack_size - 8; // <pcb_switch_to+372> add sp, sp, #8
	pcb->mNext = pcb;
}
