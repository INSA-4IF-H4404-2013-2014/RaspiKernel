#ifndef _H_KERNEL_SCHEDULER
#define _H_KERNEL_SCHEDULER


// --------------------------------------------------------------- INCLUDE

#include "kernel_config.h"
#include "kernel_pcb_list.h"
#include "kernel_arm.h"


// --------------------------------------------------------------- GLOBAL VARS

/*
 * @infos: list all ready round robin PCBs by priority level.
 *  (the lowest value is the less important)
 *
 *  KERNEL_RR_LEVELS is defined in kernel_config.h
 */
extern kernel_pcb_list_t kernel_round_robin_pcbs[KERNEL_RR_LEVELS];


/*
 * @infos: list all manually paused PCBs
 */
extern kernel_pcb_list_t kernel_pause_pcb;

/*
 * @infos: list all ready collaborative PCBs
 */
extern kernel_pcb_list_t kernel_collabo_pcb;


/*
 * @infos: gets the default scheduler
 *
 * @return: a pointer on the default scheduler
 */
#define kernel_default_scheduler() \
    (kernel_round_robin_pcbs)


#ifndef _C_KERNEL_SCHEDULER
extern kernel_pcb_t * const kernel_running_pcb;
#endif


// --------------------------------------------------------------- FUNCTIONS

/*
 * @infos: init the kernel_scheduler
 */
void
kernel_scheduler_init();

/*
 * @infos: yield switch to another PCB
 *
 * @param <old_pcb>: PCB to save to
 * @param <new_pcb>: PCB to switch to
 *
 * @asserts
 *  - kernel_pause_scheduler() must be called before
 *  - <old_pcb->mState> != PCB_RUN
 */
void __attribute__((naked))
kernel_scheduler_yield();

/*
 * @infos: final yield of a PCB
 *
 * @param <pcb>: PCB to switch to
 *
 * @asserts
 *  - kernel_pause_scheduler() must be called before
 */
void __attribute__((noreturn))
kernel_scheduler_yield_noreturn();

/*
 * @infos: pause scheduler
 */
#define kernel_pause_scheduler() \
    kernel_arm_disable_irq()

/*
 * @infos: resume scheduler if we are not in collaborative mode
 */
#define kernel_resume_scheduler() \
	if(kernel_running_pcb->mSchedulerList != &kernel_collabo_pcb) \
	{ \
		kernel_arm_enable_irq(); \
	}


#endif
