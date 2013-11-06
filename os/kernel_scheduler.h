#ifndef _H_KERNEL_SCHEDULER
#define _H_KERNEL_SCHEDULER


// --------------------------------------------------------------- INCLUDE

#include "kernel_pcb.h"
#include "hw.h"


// --------------------------------------------------------------- PROCESS TYPES

extern struct pcb_s * kernel_current_pcb;


void __attribute__((noreturn))
kernel_scheduler_jump(kernel_pcb_t * pcb);

#define kernel_scheduler_begin() DISABLE_IRQ()
#define kernel_scheduler_end() ENABLE_IRQ()

#define kernel_scheduler_disable() DISABLE_IRQ()
#define kernel_scheduler_enable() ENABLE_IRQ()



#endif
