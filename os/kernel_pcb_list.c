
#include "kernel_pcb_list.h"

kernel_pcb_t *
kernel_pcb_list_search(kernel_pcb_list_t * list, uint32_t pid)
{
    kernel_pcb_t * it = list->mFirst;

    while (it)
    {
        if (it->mPID == pid)
        {
            return it;
        }

        it = it->mNext;
    }

    return nullptr;
}

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

    parent->mNext = pcb->mNext;

    if (pcb == list->mLast)
    {
        list->mLast = parent;
    }
}

