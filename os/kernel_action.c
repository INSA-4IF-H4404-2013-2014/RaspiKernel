
#include "kernel_scheduler.h"
#include "kernel_action.h"
#include "allocateMemory.h"
#include "api_process.h"

static kernel_pcb_t * kernel_all_pcb = nullptr;


static void
kernel_pcb_startup(process_func_t f, void * args);


kernel_pcb_t *
kernel_pcb_create(void * f, void * args)
{
    static uint32_t id = 0;

    kernel_pcb_t * pcb = (kernel_pcb_t *) AllocateMemory(sizeof(kernel_pcb_t));

    pcb->mPID = id++;
    pcb->mStack = (uint32_t *) AllocateMemory(STACK_SIZE);
    pcb->mSP = pcb->mStack + (STACK_SIZE - 1);
    pcb->mSP[0] = 0;
    pcb->mSP -= 16 * 4;
    pcb->mSchedulerList = &kernel_round_robin_list;

    kernel_pcb_set_pc(pcb, kernel_pcb_startup);
    kernel_pcb_set_rN(pcb, 0, f);
    kernel_pcb_set_rN(pcb, 1, args);

    pcb->mGlobalNext = kernel_all_pcb;
    kernel_all_pcb = pcb;

    kernel_pcb_list_pushb(&kernel_pause_pcb, pcb);

    return pcb;
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

process_state_t
kernel_pcb_get_state(kernel_pcb_t * pcb)
{
    if (pcb == kernel_running_pcb)
    {
        return API_STATE_RUNNING;
    }

    if (pcb->mParentList == &kernel_round_robin_list)
    {
        return API_STATE_READY;
    }

    return API_STATE_PAUSE;
}

uint32_t
kernel_pcb_start(kernel_pcb_t * pcb)
{
    if (pcb->mParentList != &kernel_pause_pcb)
    {
        return 0;
    }

    kernel_pcb_list_remove(&kernel_pause_pcb, pcb);
    kernel_pcb_list_pushb(pcb->mSchedulerList, pcb);

    return 1;
}

uint32_t
kernel_pcb_pause_other(kernel_pcb_t * pcb)
{
    if (pcb->mParentList != pcb->mSchedulerList)
    {
        return 0;
    }

    kernel_pcb_list_remove(pcb->mSchedulerList, pcb);
    kernel_pcb_list_pushb(&kernel_pause_pcb, pcb);

    return 1;
}

void
kernel_pcb_self_pause()
{
    kernel_pcb_t * current;

    kernel_pcb_list_popf(&kernel_round_robin_list, current);
    kernel_pcb_list_pushb(&kernel_pause_pcb, current);

    kernel_scheduler_yield();
}

void
kernel_pcb_destroy(kernel_pcb_t * pcb)
{
    kernel_pcb_list_remove(pcb->mParentList, pcb);

    kernel_pcb_t ** it_pcb = &kernel_all_pcb;

    while (*it_pcb != pcb)
    {
        it_pcb = &(*it_pcb)->mGlobalNext;
    }

    *it_pcb = pcb->mGlobalNext;

    FreeAllocatedMemory(pcb->mStack);

    FreeAllocatedMemory((uint32_t*)pcb);

    if (pcb == kernel_running_pcb)
    {
        kernel_scheduler_yield_noreturn();
    }
}

static void
kernel_pcb_startup(process_func_t f, void *args)
{
    f(args);

    kernel_pause_scheduler();
    kernel_pcb_destroy(kernel_running_pcb);
}

