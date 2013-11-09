
#include "kernel_scheduler.h"
#include "kernel_action.h"


void
main_process(void);

void __attribute__((noreturn))
kernel_main(void)
{
    init_hw();

    kernel_pcb_t * pcb = kernel_pcb_create((void *) main_process, nullptr);

    kernel_pcb_start(pcb);
    kernel_scheduler_jump(pcb);
}
