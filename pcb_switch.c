
#include "pcb.h"

#define SWITCH_REGISTER2(i) \
        __asm ("mov %0, r" #i : "=r"(oldPcb->mR[i])); \
        __asm ("mov r" #i ", %0" : : "r"(newPcb->mR[i]))

#define SWITCH_REGISTER(i) \
        __asm ("mov %0, r" #i : "=r"(((unsigned int*)oldPcb->mSP)[-1-i])); \
        __asm ("mov r" #i ", %0" : : "r"(((unsigned int*)newPcb->mSP)[-1-i]))

void pcb_switch_to(struct pcb_s* oldPcb, struct pcb_s* newPcb)
{
    __asm ("push {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12}");
    __asm ("add sp, #52");
    __asm ("mov %0, sp" : "=r"(oldPcb->mSP));
    __asm ("mov %0, lr" : "=r"(oldPcb->mPC));

    __asm ("mov lr, %0" : : "r"(newPcb->mPC));
    __asm ("mov sp, %0" : : "r"(newPcb->mSP));
    __asm ("sub sp, #52");
    __asm ("pop {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12}");
}
