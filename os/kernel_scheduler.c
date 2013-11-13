
#define _C_KERNEL_SCHEDULER

#include "kernel_arm.h"
#include "kernel_scheduler.h"
#include "hw.h"

kernel_pcb_list_t kernel_round_robin_pcbs[KERNEL_RR_LEVELS];
kernel_pcb_list_t kernel_pause_pcb;

kernel_pcb_t * kernel_running_pcb;

void
kernel_scheduler_init()
{
    uint32_t i;

    for (i = 0; i < KERNEL_RR_LEVELS; i++)
    {
        kernel_pcb_list_init(kernel_round_robin_pcbs + i);
    }
    kernel_pcb_list_init(&kernel_pause_pcb);

    kernel_running_pcb = nullptr;
}

#define kernel_scheduler_chose_next() \
    { \
        uint32_t i = KERNEL_RR_LEVELS - 1; \
        while (kernel_round_robin_pcbs[i].mFirst == 0) \
        { \
            i--; \
        } \
        kernel_running_pcb = kernel_round_robin_pcbs[i].mFirst; \
    }


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
    __asm("mov %0, sp" : "=r"(kernel_running_pcb->mSP));

    kernel_pcb_list_rotatel(kernel_running_pcb->mSchedulerList);

    kernel_scheduler_chose_next();

    set_next_tick_and_enable_timer_irq();

    __asm("mov sp, %0" : : "r"(kernel_running_pcb->mSP));
    __asm("pop {r0 - r12, lr}");
    __asm("add sp, #8");

    __asm("ldr r0, [sp, #-4]");
    __asm("msr cpsr, r0");
    __asm("ldr r0, [sp, #-64]");

    __asm("ldr pc, [sp, #-8]");
}

void
kernel_scheduler_yield()
{
    __asm("str r0, [sp, #-64]");
    __asm("mrs r0, cpsr");
    __asm("push {r0}");
    __asm("push {lr}");
    __asm("srsdb sp!, #0x13");
    __asm("push {r0 - r12, lr}");
    __asm("mov %0, sp" : "=r"(kernel_running_pcb->mSP));

    kernel_scheduler_chose_next();

    __asm("mov sp, %0" : : "r"(kernel_running_pcb->mSP));
    __asm("pop {r0 - r12, lr}");
    __asm("add sp, #8");

    __asm("ldr r0, [sp, #-4]");
    __asm("msr cpsr, r0");
    __asm("ldr r0, [sp, #-64]");

    __asm("ldr pc, [sp, #-8]");
}

void __attribute__((noreturn))
kernel_scheduler_yield_noreturn()
{
    kernel_scheduler_chose_next();

    __asm("mov sp, %0" : : "r"(kernel_running_pcb->mSP));
    __asm("pop {r0 - r12, lr}");
    __asm("add sp, #8");

    __asm("ldr r0, [sp, #-4]");
    __asm("msr cpsr, r0");
    __asm("ldr r0, [sp, #-64]");

    __asm("ldr pc, [sp, #-8]");

    __builtin_unreachable();
}
