#ifndef _H_KERNEL_SCHEDULER
#define _H_KERNEL_SCHEDULER


// --------------------------------------------------------------- INCLUDE

#include "hw.h"


// --------------------------------------------------------------- PROCESS TYPES

extern struct pcb_s * kernel_current_pcb;


#define kernel_scheduler_begin() DISABLE_IRQ()
#define kernel_scheduler_end() ENABLE_IRQ()



#endif
