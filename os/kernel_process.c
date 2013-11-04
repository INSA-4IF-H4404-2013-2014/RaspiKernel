
#include "kernel_pcb_cycle.h"
#include "kernel_process.h"
#include "allocateMemory.h"
#include "hw.h"

static struct pcb_s * current_pcb = 0;

static void
process_startup(process_func_t f, void *args) __attribute__ ((noreturn));

uint32_t
process_create(process_func_t f, void * args)
{
    struct pcb_s * newPcb = (struct pcb_s *) AllocateMemory(sizeof(struct pcb_s));

    pcb_init(newPcb, (pcb_func_t)process_startup, STACK_SIZE);
    pcb_set_register(newPcb, 0, (uint32_t)f);
    pcb_set_register(newPcb, 1, (uint32_t)args);

    pcb_cycle_append(&current_pcb, newPcb);

    return newPcb->mPID;
}

uint32_t
process_start(uint32_t pid)
{
    struct pcb_s * pcb = pcb_cycle_by_pid(current_pcb, pid);

    if (pcb == 0)
    {
        return 0;
    }

    if (pcb->mState != PCB_PAUSE)
    {
        // if pid == pcb->mPID -> pcb->mState == PCB_RUNNING
        return 0;
    }

    pcb->mState = PCB_READY;

    return 1;
}

uint32_t
process_get_pid()
{
    return current_pcb->mPID;
}

void
process_exit()
{
    struct pcb_s * next_pcb = pcb_cycle_next_ready(current_pcb);
    struct pcb_s * previous_pcb = pcb_cycle_rm_current(&current_pcb);

    next_pcb->mState = PCB_RUN;

    pcb_release(previous_pcb);
    FreeAllocatedMemory((uint32_t*)previous_pcb);

    pcb_switch_to(0, next_pcb);

    __builtin_unreachable();
}

static void
process_startup(process_func_t f, void *args)
{
    f(args);

    process_exit();
}


void __attribute__ ((naked)) ctx_switch ()
{
    DISABLE_IRQ();

    __asm ("push {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12}");
    __asm ("add sp, #52");
    __asm ("mov %0, sp" : "=r"(current_pcb->mSP));
    __asm ("mov %0, lr" : "=r"(current_pcb->mPC));
    // bouge la tete de pile pour ne pas ecraser la sauvegarde des registres qu on vient juste de faire lors de l appel de  pcb_cyce_next_ready
    __asm ("sub sp, #52");

    current_pcb = pcb_cycle_next_ready(current_pcb);
    set_next_tick_and_enable_timer_irq();

     // pas besoin de remanipuler la pile car current_pcb est globale
    __asm ("mov lr, %0" : : "r"(current_pcb->mPC));
    __asm ("mov sp, %0" : : "r"(current_pcb->mSP));
    __asm ("sub sp, #52");
    __asm ("pop {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12}");

    ENABLE_IRQ();

    //return de bourrin parce que naked le fait pas
    __asm ("mov pc, lr");
}

