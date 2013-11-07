
#include "kernel_scheduler.h"
#include "kernel_pcb_cycle.h"
#include "kernel_process.h"
#include "kernel_action.h"
#include "allocateMemory.h"

static void
kernel_pcb_startup(process_func_t f, void * args);


kernel_pcb_t *
kernel_pcb_create(void * f, void * args)
{
    kernel_pcb_t * pcb = (kernel_pcb_t *) AllocateMemory(sizeof(struct pcb_s));

    pcb_init(pcb, (pcb_func_t)kernel_pcb_startup, STACK_SIZE);
    kernel_pcb_set_rN(pcb, 0, f);
    kernel_pcb_set_rN(pcb, 1, args);

    pcb_cycle_append(&kernel_current_pcb, pcb);

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

    return 1;
}

uint32_t
kernel_pcb_pause_other(kernel_pcb_t * pcb)
{
    if (pcb->mState == PCB_READY)
    {
        pcb->mState = PCB_PAUSE;
        return 1;
    }

    return 0;
}

void
kernel_pcb_self_pause()
{
    kernel_pcb_t * current = kernel_current_pcb;
    kernel_pcb_t * next = pcb_cycle_next_ready(kernel_current_pcb);

    current->mState = PCB_PAUSE;

    kernel_scheduler_switch_to(current, next);
}

void
kernel_pcb_destroy(kernel_pcb_t * pcb)
{
    if (pcb->mState != PCB_RUN)
    {
        kernel_cycle_remove(&kernel_current_pcb, pcb);

        pcb_release(pcb);
        FreeAllocatedMemory((uint32_t*)pcb);

        return;
    }

    pcb->mState = PCB_PAUSE;

    kernel_current_pcb = pcb_cycle_next_ready(kernel_current_pcb);
    kernel_current_pcb->mState = PCB_RUN;

    kernel_cycle_remove(&kernel_current_pcb, pcb);

    pcb_release(pcb);
    FreeAllocatedMemory((uint32_t*)pcb);

    kernel_scheduler_jump(kernel_current_pcb);
}

static void
kernel_pcb_startup(process_func_t f, void *args)
{
    f(args);

    kernel_pcb_destroy(kernel_current_pcb);
}

