
#include "kernel_pcb.h"
#include "allocateMemory.h"

static kernel_pcb_t * kernel_all_pcb = nullptr;


void
kernel_pcb_init(kernel_pcb_t * pcb, uint32_t f, uint32_t stack_size)
{
    static uint32_t id = 0;

    pcb->mPID = id++;
    pcb->mStack = (uint32_t *) AllocateMemory(stack_size);
    pcb->mSP = pcb->mStack + (stack_size - 1);
    pcb->mSP[0] = 0;
    pcb->mSP -= 16 * 4;
    pcb->mNext = pcb;

    kernel_pcb_set_pc(pcb, f);

    pcb->mGlobalNext = kernel_all_pcb;
    kernel_all_pcb = pcb;
}

kernel_pcb_t *
kernel_pcb_global_by_pid(uint32_t pid)
{
    kernel_pcb_t * it_pcb = kernel_all_pcb;

    while (it_pcb)
    {
        if (it_pcb->mPID == pid)
        {
            return it_pcb;
        }

        it_pcb = it_pcb->mGlobalNext;
    }

    return nullptr;
}

void
kernel_pcb_release(kernel_pcb_t * pcb)
{
    kernel_pcb_t ** it_pcb = &kernel_all_pcb;

    while (*it_pcb != pcb)
    {
        it_pcb = &(*it_pcb)->mGlobalNext;
    }

    *it_pcb = pcb->mGlobalNext;

    FreeAllocatedMemory(pcb->mStack);
}
