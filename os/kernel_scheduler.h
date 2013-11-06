#ifndef _H_KERNEL_SCHEDULER
#define _H_KERNEL_SCHEDULER


// --------------------------------------------------------------- INCLUDE

#include "kernel_pcb.h"
#include "hw.h"


// --------------------------------------------------------------- PROCESS TYPES

extern struct pcb_s * kernel_current_pcb;


void __attribute__((noreturn))
kernel_scheduler_jump(kernel_pcb_t * pcb);

#define kernel_pause_scheduler() DISABLE_IRQ()
#define kernel_resume_scheduler() ENABLE_IRQ()



#endif
