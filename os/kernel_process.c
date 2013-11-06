
#include "kernel_scheduler.h"
#include "kernel_pcb_cycle.h"
#include "kernel_action.h"
#include "kernel_process.h"
#include "allocateMemory.h"
#include "hw.h"

uint32_t
process_create(process_func_t f, void * args)
{
    kernel_pause_scheduler();

    uint32_t pid = kernel_pcb_create((void *) f, args)->mPID;

    kernel_resume_scheduler();

    return pid;
}

uint32_t
process_pause(uint32_t pid)
{
    kernel_pause_scheduler();

    if (pid == kernel_current_pcb->mPID)
    {
        kernel_pcb_self_pause();

        // kernel_pcb_self_pause call kernel_resume_scheduler()

        return 1;
    }

    struct pcb_s * pcb = pcb_cycle_by_pid(kernel_current_pcb, pid);

    if (pcb == 0)
    {
        return 0;
    }

    uint32_t status = kernel_pcb_pause_other(pcb);

    kernel_resume_scheduler();

    return status;
}

uint32_t
process_start(uint32_t pid)
{
    kernel_pause_scheduler();

    struct pcb_s * pcb = pcb_cycle_by_pid(kernel_current_pcb, pid);

    if (pcb == 0)
    {
        return 0;
    }

    uint32_t status = kernel_pcb_start(pcb);

    kernel_resume_scheduler();

    return status;
}

uint32_t
process_get_pid()
{
    return kernel_current_pcb->mPID;
}

void
process_exit()
{
    kernel_pause_scheduler();

    kernel_pcb_destroy(kernel_current_pcb);

    __builtin_unreachable();
}
