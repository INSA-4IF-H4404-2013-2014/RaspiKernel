#ifndef _H_KERNEL_SCHEDULER
#define _H_KERNEL_SCHEDULER


// --------------------------------------------------------------- INCLUDE

#include "kernel_pcb.h"
#include "hw.h"


// --------------------------------------------------------------- PROCESS TYPES

/*
 * @infos : cycle head of all PCBs
 */
extern kernel_pcb_t * kernel_current_pcb;

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
void __attribute__((naked))
kernel_scheduler_switch_to(kernel_pcb_t * old_pcb, kernel_pcb_t * new_pcb);

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
kernel_scheduler_jump(kernel_pcb_t * pcb);

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
