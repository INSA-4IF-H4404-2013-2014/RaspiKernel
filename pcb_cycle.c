
#include "pcb_cycle.h"
#include "allocateMemory.h"

struct pcb_s*
pcb_cycle_previous(struct pcb_s* pcb)
{
    struct pcb_s* current = pcb;

    while (current->mNext != pcb)
    {
        current = pcb_cycle_next(current);
    }

    return current;
}

struct pcb_s *
pcb_cycle_next_ready(struct pcb_s * current_pcb)
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

struct pcb_s *
pcb_cycle_by_pid(struct pcb_s * pcb_head, uint32_t pid)
{
    if (pcb_head->mPID == pid)
    {
        return pcb_head;
    }

    struct pcb_s * current = pcb_head->mNext;

    while (current != pcb_head)
    {
        if (current->mPID == pid)
        {
            return current;
        }

        current = pcb_cycle_next(current);
    }

    // this PID doesn't exist
    return nullptr;
}

void
pcb_cycle_append(struct pcb_s ** pcb_cycle, struct pcb_s * pcb)
{
    if (*pcb_cycle == 0)
    {
        (*pcb_cycle) = pcb;
    }
    else
    {
        pcb->mNext = (*pcb_cycle)->mNext;
        (*pcb_cycle)->mNext = pcb;
    }
}

struct pcb_s *
pcb_cycle_rm_current(struct pcb_s ** pcb_cycle)
{
    struct pcb_s * current = *pcb_cycle;

    if (current->mNext == current)
    {
        *pcb_cycle = 0;
    }
    else
    {
        struct pcb_s * previous = pcb_cycle_previous(current);

        *pcb_cycle = current->mNext;

        previous->mNext = current->mNext;
    }

    current->mNext = current;

    return current;
}
