#ifndef _H_KERNEL_SCHEDULER
#define _H_KERNEL_SCHEDULER


// --------------------------------------------------------------- INCLUDE

#include "kernel_pcb_list.h"
#include "hw.h"


// --------------------------------------------------------------- GLOBAL VARS

/*
 * @infos: cycle head of all PCBs
 */
extern kernel_pcb_list_t kernel_ready_pcb;
extern kernel_pcb_list_t kernel_pause_pcb;

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
void
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
    DISABLE_IRQ()

/*
 * @infos: resume scheduler
 */
#define kernel_resume_scheduler() \
    ENABLE_IRQ()


#endif
