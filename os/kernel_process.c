
#include "kernel_scheduler.h"
#include "kernel_pcb_cycle.h"
#include "kernel_process.h"
#include "allocateMemory.h"
#include "hw.h"

static void
process_startup(process_func_t f, void *args) __attribute__ ((noreturn));

uint32_t
process_create(process_func_t f, void * args)
{
    struct pcb_s * newPcb = (struct pcb_s *) AllocateMemory(sizeof(struct pcb_s));

    pcb_init(newPcb, (pcb_func_t)process_startup, STACK_SIZE);
    pcb_set_register(newPcb, 0, (uint32_t)f);
    pcb_set_register(newPcb, 1, (uint32_t)args);

    pcb_cycle_append(&kernel_current_pcb, newPcb);

    return newPcb->mPID;
}

uint32_t
process_start(uint32_t pid)
{
    struct pcb_s * pcb = pcb_cycle_by_pid(kernel_current_pcb, pid);

    if (pcb == 0)
    {
        return 0;
    }

    if (pcb->mState != PCB_PAUSE)
    {
        // if pid == pcb->mPID -> pcb->mState == PCB_RUNNING
        return 0;
    }

    pcb->mState = PCB_READY;

    return 1;
}

uint32_t
process_get_pid()
{
    return kernel_current_pcb->mPID;
}

void
process_exit()
{
    struct pcb_s * next_pcb = pcb_cycle_next_ready(kernel_current_pcb);
    struct pcb_s * previous_pcb = pcb_cycle_rm_current(&kernel_current_pcb);

    next_pcb->mState = PCB_RUN;

    pcb_release(previous_pcb);
    FreeAllocatedMemory((uint32_t*)previous_pcb);

    pcb_switch_to(0, next_pcb);

    __builtin_unreachable();
}

static void
process_startup(process_func_t f, void *args)
{
    f(args);

    process_exit();
}
