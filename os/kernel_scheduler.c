
#include "kernel_scheduler.h"
#include "kernel_pcb_cycle.h"
#include "hw.h"

struct pcb_s * kernel_current_pcb = 0;

void
kernel_scheduler_handler()
{
    kernel_pause_scheduler();

    __asm ("push {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12}");
    __asm ("add sp, #52");
    __asm ("mov %0, sp" : "=r"(kernel_current_pcb->mSP));
    __asm ("mov %0, lr" : "=r"(kernel_current_pcb->mPC));
    // bouge la tete de pile pour ne pas ecraser la sauvegarde des registres qu on vient juste de faire lors de l appel de  pcb_cyce_next_ready
    __asm ("sub sp, #52");

    kernel_current_pcb = pcb_cycle_next_ready(kernel_current_pcb);
    set_next_tick_and_enable_timer_irq();

     // pas besoin de remanipuler la pile car current_pcb est globale
    __asm ("mov lr, %0" : : "r"(kernel_current_pcb->mPC));
    __asm ("mov sp, %0" : : "r"(kernel_current_pcb->mSP));
    __asm ("sub sp, #52");
    __asm ("pop {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12}");

    kernel_resume_scheduler();

    //return de bourrin parce que naked le fait pas
    __asm ("mov pc, lr");
}

void
kernel_scheduler_switch_to(kernel_pcb_t * old_pcb, kernel_pcb_t * new_pcb)
{
    __asm ("push {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12}");
    __asm ("add sp, #52");
    __asm ("mov %0, sp" : "=r"(old_pcb->mSP));
    __asm ("mov %0, lr" : "=r"(old_pcb->mPC));

    kernel_current_pcb = new_pcb;
    new_pcb->mState = PCB_RUN;

    __asm ("mov lr, %0" : : "r"(new_pcb->mPC));
    __asm ("mov sp, %0" : : "r"(new_pcb->mSP));
    __asm ("sub sp, #52");
    __asm ("pop {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12}");

    kernel_resume_scheduler();

    __asm ("mov pc, lr");
}

void __attribute__((noreturn))
kernel_scheduler_jump(kernel_pcb_t * pcb)
{
    kernel_current_pcb = pcb;
    pcb->mState = PCB_RUN;

    __asm ("mov lr, %0" : : "r"(pcb->mPC));
    __asm ("mov sp, %0" : : "r"(pcb->mSP));
    __asm ("sub sp, #52");
    __asm ("pop {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12}");

    kernel_resume_scheduler();

    __asm ("mov pc, lr");

    __builtin_unreachable();
}
