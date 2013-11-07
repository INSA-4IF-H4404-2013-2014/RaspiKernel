
#include "kernel_pcb.h"
#include "allocateMemory.h"

void
kernel_pcb_init(kernel_pcb_t * pcb, pcb_func_t f, uint32_t stack_size)
{
    static uint32_t id = 0;

    pcb->mState = PCB_PAUSE;
    pcb->mPID = id++;
    pcb->mStack = (uint32_t *) AllocateMemory(stack_size);
    pcb->mSP = pcb->mStack + stack_size - 8; // <pcb_switch_to+372> add sp, sp, #8
    pcb->mSP -= 16 * 4;
    pcb->mNext = pcb;

    kernel_pcb_set_pc(pcb, f);
}

void
kernel_pcb_release(kernel_pcb_t * pcb)
{
    FreeAllocatedMemory(pcb->mStack);
}
