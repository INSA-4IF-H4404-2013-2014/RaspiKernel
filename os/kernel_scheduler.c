
#include "kernel_arm.h"
#include "kernel_scheduler.h"
#include "kernel_pcb_cycle.h"
#include "hw.h"

kernel_pcb_t * kernel_current_pcb = 0;

/* INTERUPTION ASSERTS
 *
 * lr_irq == PC{before interuption} + 4
 * lr_svc == original lr values before interuption
 * r0 - r12 == original registers values
 * SPSR = CPSR{before interuption}
 * kernel_arm_mode() == KERNEL_ARM_MODE_IRQ
 * kernel_pause_scheduler() already done !
 */
void __attribute__((naked))
kernel_scheduler_handler()
{
    // correct lr_irq to = PC{before interuption}
    __asm("sub lr, lr, #4");

    // str spsr, [sp_svc, #-4]! (push {spsr} in sp_svc)
    // str lr(lr_irq), [sp_svc, #-4]! (push {lr} in sp_svc)
    __asm("srsdb sp!, #0x13");

    // switch back to Supervisor mode
    kernel_arm_set_mode(KERNEL_ARM_MODE_SVC);

    __asm("push {r0 - r12, lr}");
    __asm("mov %0, sp" : "=r"(kernel_current_pcb->mSP));

    kernel_current_pcb->mState = PCB_READY;

    kernel_current_pcb = pcb_cycle_next_ready(kernel_current_pcb);
    set_next_tick_and_enable_timer_irq();

    kernel_current_pcb->mState = PCB_RUN;

    __asm("mov sp, %0" : : "r"(kernel_current_pcb->mSP));
    __asm("pop {r0 - r12, lr}");
    __asm("add sp, #8");

    kernel_resume_scheduler();

    __asm("ldr pc, [sp, #-8]");
}

void
kernel_scheduler_switch_to(kernel_pcb_t * old_pcb, kernel_pcb_t * new_pcb)
{
    //__asm("push {cpsr}");
    //__asm("push {lr}");
    __asm("srsdb sp!, #0x13");
    __asm("push {r0 - r12, lr}");
    __asm("mov %0, sp" : "=r"(old_pcb->mSP));

    kernel_current_pcb = new_pcb;
    new_pcb->mState = PCB_RUN;

    __asm("mov sp, %0" : : "r"(kernel_current_pcb->mSP));
    __asm("pop {r0 - r12, lr}");
    __asm("add sp, #8");

    kernel_resume_scheduler();

    __asm("ldr pc, [sp, #-8]");
}

void __attribute__((noreturn))
kernel_scheduler_jump(kernel_pcb_t * pcb)
{
    kernel_current_pcb = pcb;
    pcb->mState = PCB_RUN;

    __asm("mov sp, %0" : : "r"(kernel_current_pcb->mSP));
    __asm("pop {r0 - r12, lr}");
    __asm("add sp, #8");

    kernel_resume_scheduler();

    __asm("ldr pc, [sp, #-8]");

    __builtin_unreachable();
}
