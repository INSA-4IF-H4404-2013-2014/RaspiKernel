
#include "kernel_scheduler.h"
#include "kernel_pcb_cycle.h"
#include "kernel_action.h"
#include "kernel_process.h"
#include "allocateMemory.h"
#include "hw.h"

uint32_t
process_create(process_func_t f, void * args)
{
    return kernel_pcb_create((void *) f, args)->mPID;
}

uint32_t
process_start(uint32_t pid)
{
    struct pcb_s * pcb = pcb_cycle_by_pid(kernel_current_pcb, pid);

    if (pcb == 0)
    {
        return 0;
    }

    return kernel_pcb_start(pcb);
}

uint32_t
process_get_pid()
{
    return kernel_current_pcb->mPID;
}

void
process_exit()
{
    kernel_pcb_destroy(kernel_current_pcb);

    __builtin_unreachable();
}
