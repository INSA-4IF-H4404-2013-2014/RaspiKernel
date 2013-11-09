
#include "kernel_pcb_list.h"

void
kernel_pcb_list_remove(kernel_pcb_list_t * list, kernel_pcb_t * pcb)
{
    if (list->mFirst == pcb)
    {
        list->mFirst = pcb->mNextMeta;
        return;
    }

    kernel_pcb_t * parent = list->mFirst;

    while (parent->mNextMeta != pcb)
    {
        parent = parent->mNextMeta;
    }

    parent->mNextMeta = nullptr;

    if (pcb == list->mLast)
    {
        list->mLast = parent;
    }
}

