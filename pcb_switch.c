
#include "pcb.h"

#define SWITCH_REGISTER2(i) \
        __asm ("mov %0, r" #i : "=r"(oldPcb->mR[i])); \
        __asm ("mov r" #i ", %0" : : "r"(newPcb->mR[i]))

#define SWITCH_REGISTER(i) \
        __asm ("mov %0, r" #i : "=r"(((unsigned int*)oldPcb->mSP)[-1-i])); \
        __asm ("mov r" #i ", %0" : : "r"(((unsigned int*)newPcb->mSP)[-1-i]))

void pcb_switch_to(struct pcb_s* oldPcb, struct pcb_s* newPcb)
{
    __asm ("push {r0}");
    __asm ("push {r1}");
    __asm ("push {r2}");
    __asm ("push {r3}");
    __asm ("push {r4}");
    __asm ("push {r5}");
    __asm ("push {r6}");
    __asm ("push {r7}");
    __asm ("push {r8}");
    __asm ("push {r9}");
    __asm ("push {r10}");
    __asm ("push {r11}");
    __asm ("push {r12}");
    __asm ("add sp, #52");
    __asm ("mov %0, sp" : "=r"(oldPcb->mSP));
    __asm ("mov %0, lr" : "=r"(oldPcb->mPC));

    __asm ("mov lr, %0" : : "r"(newPcb->mPC));
    __asm ("mov sp, %0" : : "r"(newPcb->mSP));
    __asm ("sub sp, #52");
    __asm ("pop {r12}");
    __asm ("pop {r11}");
    __asm ("pop {r10}");
    __asm ("pop {r9}");
    __asm ("pop {r8}");
    __asm ("pop {r7}");
    __asm ("pop {r6}");
    __asm ("pop {r5}");
    __asm ("pop {r4}");
    __asm ("pop {r3}");
    __asm ("pop {r2}");
    __asm ("pop {r1}");
    __asm ("pop {r0}");
}
