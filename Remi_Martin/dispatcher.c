#include "process.h"
#include "dispatcher.h"
#include "shed.h"

/*
#define SWITCH_REGISTER(i) \
        __asm ("mov %0, r" #i : "=r"(current_pcb->mR[i])); \
        __asm ("mov r" #i ", %0" : : "r"(pcb->mR[i]))
*/

void ctx_switch(pcb_s * oldPcb, pcb_s * newPcb)
{
  if(oldPcb != newPcb)
  {
    oldPcb->state = PCB_READY;
  }

  //Saving old context
  __asm volatile ("push {r0-r12}");
  __asm volatile ("mov %0, sp" : "=r"(oldPcb->mSP));
  __asm volatile ("mov %0, lr" : "=r"(oldPcb->mPC));

  //TODO : gerer les args ?

  //Restoring new context
  __asm volatile ("mov lr, %0" : : "r"(newPcb->mPC));
  __asm volatile ("mov sp, %0" : : "r"(newPcb->mSP));
  __asm volatile ("pop {r0-r12}");

  if(newPcb->state == PCB_NEW)
  {
    newPcb->state = PCB_RUNNING;
    start_current_process();
  }

  newPcb->state = PCB_RUNNING;
}

