
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

    if (pid == kernel_running_pcb->mPID)
    {
        kernel_pcb_self_pause();

        // kernel_pcb_self_pause call kernel_resume_scheduler()

        return 1;
    }

    kernel_pcb_t * pcb = kernel_pcb_global_by_pid(pid);

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

    kernel_pcb_t * pcb = kernel_pcb_list_search(&kernel_pause_pcb, pid);

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
    return kernel_running_pcb->mPID;
}

void
process_exit()
{
    kernel_pause_scheduler();

    kernel_pcb_destroy(kernel_running_pcb);

    __builtin_unreachable();
}
