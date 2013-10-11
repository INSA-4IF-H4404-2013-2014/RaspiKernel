
#include "pcb.h"

#define SWITCH_REGISTER(i) \
        __asm ("mov %0, r" #i : "=r"(oldPcb->mR[i])); \
        __asm ("mov r" #i ", %0" : : "r"(newPcb->mR[i]))

void pcb_switch_to(struct pcb_s* oldPcb, struct pcb_s* newPcb)
{
  __asm ("mov %0, sp" : "=r"(oldPcb->mSP));
  __asm ("mov %0, lr" : "=r"(oldPcb->mPC));

  SWITCH_REGISTER(0);
  SWITCH_REGISTER(1);
  SWITCH_REGISTER(2);
  SWITCH_REGISTER(3);
  SWITCH_REGISTER(4);
  SWITCH_REGISTER(5);
  SWITCH_REGISTER(6);
  SWITCH_REGISTER(7);
  SWITCH_REGISTER(8);
  SWITCH_REGISTER(9);
  SWITCH_REGISTER(10);
  SWITCH_REGISTER(11);
  SWITCH_REGISTER(12);

  __asm ("mov lr, %0" : : "r"(newPcb->mPC));
  __asm ("mov sp, %0" : : "r"(newPcb->mSP));
}
