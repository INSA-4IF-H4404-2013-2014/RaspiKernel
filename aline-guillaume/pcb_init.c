
#include "pcb.h"
#include "allocateMemory.h"

void init_pcb(struct pcb_s* pcb, func_t f, unsigned int stack_size)
{
	static unsigned int id = 0;

	pcb->mState = PCB_READY;
	pcb->mPID = id++;
	pcb->mStack = (unsigned int) AllocateMemory(stack_size);
	pcb->mPC = (unsigned int) f;
	pcb->mSP = pcb->mStack + stack_size;
	pcb->mNext = pcb;
}
