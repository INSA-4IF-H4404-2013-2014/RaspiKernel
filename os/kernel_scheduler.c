
#include "kernel_scheduler.h"
#include "kernel_pcb_cycle.h"
#include "hw.h"

struct pcb_s * kernel_current_pcb = 0;

void __attribute__((naked))
kernel_scheduler_handler()
{
    kernel_scheduler_begin();

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

    kernel_scheduler_end();

    //return de bourrin parce que naked le fait pas
    __asm ("mov pc, lr");
}

void __attribute__((naked))
kernel_scheduler_switch_to(struct pcb_s* old_pcb, struct pcb_s* new_pcb)
{
    kernel_scheduler_begin();

    if (old_pcb)
    {
        __asm ("push {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12}");
        __asm ("add sp, #52");
        __asm ("mov %0, sp" : "=r"(old_pcb->mSP));
        __asm ("mov %0, lr" : "=r"(old_pcb->mPC));
    }

    __asm ("mov lr, %0" : : "r"(new_pcb->mPC));
    __asm ("mov sp, %0" : : "r"(new_pcb->mSP));
    __asm ("sub sp, #52");
    __asm ("pop {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12}");

    kernel_scheduler_end();

    __asm ("mov pc, lr");
}

