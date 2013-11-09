
#include "kernel_pcb.h"
#include "allocateMemory.h"

void
kernel_pcb_init(kernel_pcb_t * pcb, uint32_t f, uint32_t stack_size)
{
    static uint32_t id = 0;

    pcb->mState = PCB_PAUSE;
    pcb->mPID = id++;
    pcb->mStack = (uint32_t *) AllocateMemory(stack_size);
    pcb->mSP = pcb->mStack + (stack_size - 1);
    pcb->mSP[0] = 0;
    pcb->mSP -= 16 * 4;
    pcb->mNext = pcb;

    kernel_pcb_set_pc(pcb, f);
}

void
kernel_pcb_release(kernel_pcb_t * pcb)
{
    FreeAllocatedMemory(pcb->mStack);
}
