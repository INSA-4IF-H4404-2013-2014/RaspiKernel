
#include "pcb.h"
#include "allocateMemory.h"

void pcb_init(struct pcb_s* pcb, func_t f, uint32_t stack_size)
{
	static uint32_t id = 0;

	pcb->mState = PCB_READY;
	pcb->mPID = id++;
	pcb->mStack = (uint32_t) AllocateMemory(stack_size);
	pcb->mPC = (uint32_t) f;
	pcb->mSP = pcb->mStack + stack_size - 8; // <pcb_switch_to+372> add sp, sp, #8
	pcb->mNext = pcb;
}

void pcb_switch_to(struct pcb_s* oldPcb, struct pcb_s* newPcb)
{
    __asm ("push {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12}");
    __asm ("add sp, #52");
    __asm ("mov %0, sp" : "=r"(oldPcb->mSP));
    __asm ("mov %0, lr" : "=r"(oldPcb->mPC));

    __asm ("mov lr, %0" : : "r"(newPcb->mPC));
    __asm ("mov sp, %0" : : "r"(newPcb->mSP));
    __asm ("sub sp, #52");
    __asm ("pop {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12}");
}
