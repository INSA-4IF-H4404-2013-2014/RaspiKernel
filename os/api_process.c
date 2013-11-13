
#include "kernel_scheduler.h"
#include "kernel_action.h"
#include "api_process.h"

uint32_t
process_create(process_func_t f, void * args)
{
    kernel_pause_scheduler();

    uint32_t pid = kernel_pcb_create((void *) f, args)->mPID;

    kernel_resume_scheduler();

    return pid;
}

uint32_t
process_set_rr_priority(uint32_t pid, uint32_t priority)
{
    if (priority >= KERNEL_RR_LEVELS)
    {
        return 0;
    }

    kernel_pause_scheduler();

    kernel_pcb_t * pcb = kernel_pcb_global_by_pid(pid);

    if (pcb == 0)
    {
        kernel_resume_scheduler();
        return 0;
    }

    kernel_pcb_set_scheduler(kernel_round_robin_pcbs + priority, pcb);

    kernel_resume_scheduler();

    return 1;
}

uint32_t
process_set_collabo(uint32_t pid)
{
    kernel_pause_scheduler();

    kernel_pcb_t * pcb = kernel_pcb_global_by_pid(pid);

    if (pcb == 0)
    {
        kernel_resume_scheduler();
        return 0;
    }

    kernel_pcb_set_scheduler(kernel_collabo_pcb, pcb);

    kernel_resume_scheduler();

    return 1;
}

process_state_t
process_get_state(uint32_t pid)
{
    kernel_pause_scheduler();

    kernel_pcb_t * pcb = kernel_pcb_global_by_pid(pid);

    if (pcb == nullptr)
    {
        return API_STATE_UNKNOWN;
    }

    process_state_t state = kernel_pcb_get_state(pcb);

    kernel_resume_scheduler();

    return state;
}

uint32_t
process_pause(uint32_t pid)
{
    kernel_pause_scheduler();

    kernel_pcb_t * pcb = kernel_pcb_global_by_pid(pid);

    if (pcb == 0)
    {
        kernel_resume_scheduler();
        return 0;
    }

    if (pcb->mParentList != pcb->mSchedulerList)
    {
        /*
         * We don't want to pause a PCB that is not running
         * because it might be waiting on a sync object
         * (semaphore, mutex...)
         */
        kernel_resume_scheduler();
        return 0;
    }

    kernel_pcb_pause(&kernel_pause_pcb, pcb);

    kernel_resume_scheduler();

    return 1;
}

uint32_t
process_start(uint32_t pid)
{
    kernel_pause_scheduler();

    kernel_pcb_t * pcb = kernel_pcb_list_search(&kernel_pause_pcb, pid);

    if (pcb == 0)
    {
        kernel_resume_scheduler();
        return 0;
    }

    if (pcb->mParentList != &kernel_pause_pcb)
    {
        /*
         * We don't want to start a PCB that might be waiting
         * on a sync object (semaphore, mutex...)
         */
        kernel_resume_scheduler();
        return 0;
    }

    kernel_pcb_start(pcb);

    kernel_resume_scheduler();

    return 1;
}

uint32_t
process_get_pid()
{
    return kernel_running_pcb->mPID;
}

void
process_exit()
{
    kernel_pause_scheduler();

    kernel_pcb_destroy(kernel_running_pcb);

    __builtin_unreachable();
}
