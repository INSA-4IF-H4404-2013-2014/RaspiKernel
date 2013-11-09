
#include "kernel_scheduler.h"
#include "kernel_cycle.h"
#include "kernel_action.h"
#include "allocateMemory.h"
#include "api_process.h"

static void
kernel_pcb_startup(process_func_t f, void * args);


kernel_pcb_t *
kernel_pcb_create(void * f, void * args)
{
    kernel_pcb_t * pcb = (kernel_pcb_t *) AllocateMemory(sizeof(kernel_pcb_t));

    kernel_pcb_init(pcb, (uint32_t)kernel_pcb_startup, STACK_SIZE);
    kernel_pcb_set_rN(pcb, 0, f);
    kernel_pcb_set_rN(pcb, 1, args);

    kernel_pcb_list_pushb(&kernel_pause_pcb, pcb);

    return pcb;
}

uint32_t
kernel_pcb_start(kernel_pcb_t * pcb)
{
    if (pcb->mState != PCB_PAUSE)
    {
        return 0;
    }

    pcb->mState = PCB_READY;

    kernel_pcb_list_remove(&kernel_pause_pcb, pcb);
    kernel_pcb_list_pushb(&kernel_ready_pcb, pcb);

    return 1;
}

uint32_t
kernel_pcb_pause_other(kernel_pcb_t * pcb)
{
    if (pcb->mState != PCB_READY)
    {
        return 0;
    }

    pcb->mState = PCB_PAUSE;

    kernel_pcb_list_remove(&kernel_ready_pcb, pcb);
    kernel_pcb_list_pushb(&kernel_pause_pcb, pcb);

    return 1;
}

void
kernel_pcb_self_pause()
{
    kernel_pcb_t * current;

    kernel_pcb_list_popf(&kernel_ready_pcb, current);

    current->mState = PCB_PAUSE;

    kernel_pcb_list_pushb(&kernel_pause_pcb, current);

    kernel_scheduler_yield();
}

void
kernel_pcb_destroy(kernel_pcb_t * pcb)
{
    if (pcb->mState != PCB_RUN)
    {
        kernel_cycle_remove(&kernel_ready_pcb.mFirst, pcb);

        kernel_pcb_release(pcb);
        FreeAllocatedMemory((uint32_t*)pcb);

        return;
    }

    kernel_pcb_list_popf(&kernel_ready_pcb, pcb);

    kernel_pcb_release(pcb);
    FreeAllocatedMemory((uint32_t*)pcb);

    kernel_scheduler_yield_noreturn();
}

static void
kernel_pcb_startup(process_func_t f, void *args)
{
    f(args);

    kernel_pcb_destroy(kernel_ready_pcb.mFirst);
}

