
#include "kernel_config.h"
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
    pcb->mStack = (uint32_t *) AllocateMemory(KERNEL_STACK_SIZE);
    pcb->mSP = pcb->mStack + (KERNEL_STACK_SIZE - 1);
    pcb->mSP[0] = 0;
    pcb->mSP -= 16;
    pcb->mSchedulerList = kernel_default_scheduler();

    kernel_pcb_inherit_cpsr(pcb);
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

    if (pcb->mParentList >= kernel_round_robin_pcbs &&
        pcb->mParentList < (kernel_round_robin_pcbs + KERNEL_RR_LEVELS))
    {
        return API_STATE_READY;
    }

    return API_STATE_PAUSE;
}

void
kernel_pcb_set_scheduler(kernel_pcb_list_t * scheduler_list, kernel_pcb_t * pcb)
{
    if (pcb->mSchedulerList == scheduler_list)
    {
        return;
    }

    if (pcb->mSchedulerList != pcb->mParentList)
    {
        pcb->mSchedulerList = scheduler_list;
        return;
    }

    kernel_pcb_list_remove(pcb->mSchedulerList, pcb);

    pcb->mSchedulerList = scheduler_list;

    if (pcb != kernel_running_pcb)
    {
        kernel_pcb_list_pushb(scheduler_list, pcb);
        return;
    }

    kernel_pcb_list_pushf(scheduler_list, pcb);

    kernel_scheduler_yield();
}

void
kernel_pcb_start(kernel_pcb_t * pcb)
{
    kernel_pcb_list_remove(&kernel_pause_pcb, pcb);
    kernel_pcb_list_pushb(pcb->mSchedulerList, pcb);
}

void
kernel_pcb_pause(kernel_pcb_list_t * pause_list, kernel_pcb_t * pcb)
{
    kernel_pcb_list_remove(pcb->mSchedulerList, pcb);
    kernel_pcb_list_pushb(pause_list, pcb);

    if (pcb == kernel_running_pcb)
    {
        kernel_scheduler_yield();
    }
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

