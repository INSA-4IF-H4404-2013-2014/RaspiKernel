
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
    kernel_scheduler_disable();

    kernel_pcb_t * pcb = (kernel_pcb_t *) AllocateMemory(sizeof(struct pcb_s));

    pcb_init(pcb, (pcb_func_t)kernel_pcb_startup, STACK_SIZE);
    pcb_set_register(pcb, 0, (uint32_t)f);
    pcb_set_register(pcb, 1, (uint32_t)args);

    pcb_cycle_append(&kernel_current_pcb, pcb);

    kernel_scheduler_enable();

    return pcb;
}

uint32_t
kernel_pcb_start(kernel_pcb_t * pcb)
{
    kernel_scheduler_disable();

    if (pcb->mState != PCB_PAUSE)
    {
        return 0;
    }

    pcb->mState = PCB_READY;

    kernel_scheduler_enable();

    return 1;
}

uint32_t
kernel_pcb_pause(kernel_pcb_t * pcb)
{
    kernel_scheduler_disable();

    if (pcb->mState == PCB_READY)
    {
        pcb->mState = PCB_PAUSE;
        kernel_scheduler_enable();
        return 1;
    }

    if (pcb->mState != PCB_RUN)
    {
        kernel_scheduler_enable();
        return 0;
    }

    pcb->mState = PCB_PAUSE;

    // kernel_scheduler_switch_to

    return 1;
}

void
kernel_pcb_destroy(kernel_pcb_t * pcb)
{
    kernel_scheduler_disable();

    if (pcb->mState != PCB_RUN)
    {
        kernel_cycle_remove(&kernel_current_pcb, pcb);

        pcb_release(pcb);
        FreeAllocatedMemory((uint32_t*)pcb);

        kernel_scheduler_enable();

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

