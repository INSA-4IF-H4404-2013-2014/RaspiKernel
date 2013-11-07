
#include "kernel_pcb_cycle.h"
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
pcb_cycle_next_ready(struct pcb_s * pcb)
{
    struct pcb_s * next_pcb = pcb_cycle_next(pcb);

    while (next_pcb->mState != PCB_READY)
    {
        if (next_pcb == pcb)
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

void
kernel_cycle_remove(kernel_pcb_t ** pcb_cycle, kernel_pcb_t * pcb)
{
    kernel_pcb_t * current = *pcb_cycle;

    if (current == pcb)
    {
        if (current->mNext == current)
        {
            *pcb_cycle = 0;
            return;
        }

        *pcb_cycle = current->mNext;
    }

    kernel_pcb_t * previous = pcb_cycle_previous(pcb);

    previous->mNext = pcb->mNext;

    pcb->mNext = pcb;
}
