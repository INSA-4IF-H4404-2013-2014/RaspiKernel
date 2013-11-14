
#include "kernel_scheduler.h"
#include "kernel_action.h"
#include "hw.h"


void
main_process(void);

void __attribute__((noreturn))
kernel_main(void)
{
    kernel_scheduler_init();

    init_hw();

    kernel_pcb_t * pcb = kernel_pcb_create((void *) main_process, nullptr);

    kernel_pcb_enable_irq(pcb);
    kernel_pcb_start(pcb);

    kernel_scheduler_set_next_timer();

    kernel_scheduler_yield_noreturn();
}
