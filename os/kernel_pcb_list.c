
#include "kernel_pcb_list.h"

void
kernel_pcb_list_remove(kernel_pcb_list_t * list, kernel_pcb_t * pcb)
{
    if (list->mFirst == pcb)
    {
        list->mFirst = pcb->mNext;
        return;
    }

    kernel_pcb_t * parent = list->mFirst;

    while (parent->mNext != pcb)
    {
        parent = parent->mNext;
    }

    parent->mNext = nullptr;

    if (pcb == list->mLast)
    {
        list->mLast = parent;
    }
}

