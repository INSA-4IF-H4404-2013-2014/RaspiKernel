
#include "pcb_cycle.h"
#include "dispatcher.h"
#include "allocateMemory.h"

static struct pcb_s * current_pcb = 0;

static struct pcb_s *
cycle_next(struct pcb_s * current_pcb)
{
    struct pcb_s * next_pcb = pcb_cycle_next(current_pcb);

    while (next_pcb->mState != PCB_READY)
    {
        if (next_pcb == current_pcb)
        {
            break;
        }

        next_pcb = pcb_cycle_next(next_pcb);
    }

    return next_pcb;
}

uint32_t
process_create(func_t f, void * args)
{
    struct pcb_s * newPcb = (struct pcb_s *) AllocateMemory(sizeof(struct pcb_s));

    pcb_init(newPcb, f, STACK_SIZE);
    pcb_set_register(newPcb, 0, args);

    pcb_cycle_append(&current_pcb, newPcb);

    return newPcb->mPID;
}

void
process_yield()
{
    struct pcb_s * previous_pcb = current_pcb;
    struct pcb_s * next_pcb = cycle_next(previous_pcb);

    if (next_pcb == previous_pcb)
    {
        return;
    }

    previous_pcb->mState = PCB_READY;
    next_pcb->mState = PCB_RUN;
    current_pcb = next_pcb;

    pcb_switch_to(previous_pcb, next_pcb);
}

void
process_exit()
{
    struct pcb_s * previous_pcb = pcb_cycle_rm_current(&current_pcb);
    struct pcb_s * next_pcb = current_pcb;

    next_pcb->mState = PCB_RUN;

    FreeAllocatedMemory((uint32_t*)previous_pcb);

    pcb_switch_to(0, next_pcb);

    __builtin_unreachable();
}
