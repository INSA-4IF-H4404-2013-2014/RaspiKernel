
#include "kernel_pcb_cycle.h"
#include "allocateMemory.h"

kernel_pcb_t*
kernel_cycle_previous(kernel_pcb_t* pcb)
{
    kernel_pcb_t* current = pcb;

    while (current->mNext != pcb)
    {
        current = kernel_cycle_next(current);
    }

    return current;
}

kernel_pcb_t *
kernel_cycle_next_ready(kernel_pcb_t * pcb)
{
    kernel_pcb_t * next_pcb = kernel_cycle_next(pcb);

    while (next_pcb->mState != PCB_READY)
    {
        if (next_pcb == pcb)
        {
            break;
        }

        next_pcb = kernel_cycle_next(next_pcb);
    }

    return next_pcb;
}

kernel_pcb_t *
kernel_cycle_by_pid(kernel_pcb_t * pcb_head, uint32_t pid)
{
    if (pcb_head->mPID == pid)
    {
        return pcb_head;
    }

    kernel_pcb_t * current = pcb_head->mNext;

    while (current != pcb_head)
    {
        if (current->mPID == pid)
        {
            return current;
        }

        current = kernel_cycle_next(current);
    }

    // this PID doesn't exist
    return nullptr;
}

void
kernel_cycle_append(kernel_pcb_t ** kernel_cycle, kernel_pcb_t * pcb)
{
    if (*kernel_cycle == 0)
    {
        (*kernel_cycle) = pcb;
    }
    else
    {
        pcb->mNext = (*kernel_cycle)->mNext;
        (*kernel_cycle)->mNext = pcb;
    }
}

void
kernel_cycle_remove(kernel_pcb_t ** kernel_cycle, kernel_pcb_t * pcb)
{
    kernel_pcb_t * current = *kernel_cycle;

    if (current == pcb)
    {
        if (current->mNext == current)
        {
            *kernel_cycle = 0;
            return;
        }

        *kernel_cycle = current->mNext;
    }

    kernel_pcb_t * previous = kernel_cycle_previous(pcb);

    previous->mNext = pcb->mNext;

    pcb->mNext = pcb;
}
