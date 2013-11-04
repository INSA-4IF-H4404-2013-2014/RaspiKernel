
#include "kernel_pcb.h"
#include "allocateMemory.h"

void
pcb_init(struct pcb_s* pcb, pcb_func_t f, uint32_t stack_size)
{
    static uint32_t id = 0;

    pcb->mState = PCB_PAUSE;
    pcb->mPID = id++;
    pcb->mStack = (uint32_t *) AllocateMemory(stack_size);
    pcb->mPC = (uint32_t) f;
    pcb->mSP = pcb->mStack + stack_size - 8; // <pcb_switch_to+372> add sp, sp, #8
    pcb->mNext = pcb;
}

void
pcb_switch_to(struct pcb_s* old_pcb, struct pcb_s* new_pcb)
{
    if (old_pcb)
    {
        __asm ("push {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12}");
        __asm ("add sp, #52");
        __asm ("mov %0, sp" : "=r"(old_pcb->mSP));
        __asm ("mov %0, lr" : "=r"(old_pcb->mPC));
    }

    __asm ("mov lr, %0" : : "r"(new_pcb->mPC));
    __asm ("mov sp, %0" : : "r"(new_pcb->mSP));
    __asm ("sub sp, #52");
    __asm ("pop {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12}");
}

void
pcb_release(struct pcb_s* pcb)
{
    FreeAllocatedMemory(pcb->mStack);
}
