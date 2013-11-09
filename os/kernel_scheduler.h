#ifndef _H_KERNEL_SCHEDULER
#define _H_KERNEL_SCHEDULER


// --------------------------------------------------------------- INCLUDE

#include "kernel_pcb_list.h"
#include "hw.h"


// --------------------------------------------------------------- PROCESS TYPES

/*
 * @infos : cycle head of all PCBs
 */
extern kernel_pcb_list_t kernel_ready_pcb;
extern kernel_pcb_list_t kernel_pause_pcb;

/*
 * @infos : switch to another PCB. Sets :
 *      <kernel_current_pcb> = <new_pcb>
 *      <new_pcb->mState> = PCB_RUN
 *
 * @param <old_pcb> : PCB to save to
 * @param <new_pcb> : PCB to switch to
 *
 * @asserts
 *  - kernel_pause_scheduler() must be called before
 *  - <old_pcb->mState> != PCB_RUN
 */
void
kernel_scheduler_yield();

/*
 * @infos : jump to another PCB. Sets :
 *      <kernel_current_pcb> = <pcb>
 *      <new_pcb->mState> = PCB_RUN
 *
 * @param <pcb> : PCB to switch to
 *
 * @asserts
 *  - kernel_pause_scheduler() must be called before
 */
void __attribute__((noreturn))
kernel_scheduler_yield_noreturn();

/*
 * @infos : pause scheduler
 */
#define kernel_pause_scheduler() \
    DISABLE_IRQ()

/*
 * @infos : resume scheduler
 */
#define kernel_resume_scheduler() \
    ENABLE_IRQ()


#endif
