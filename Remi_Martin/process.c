#include "process.h"
#include "allocateMemory.h"

pcb_s * current_pcb = 0;

void init_pcb(pcb_s * * pcb, func_t f, unsigned int stack_size, void * args)
{
  *pcb = (pcb_s *) AllocateMemory (sizeof(pcb_s));
  (*pcb)->state = PCB_NEW;
  (*pcb)->mPC = (unsigned int) f;
  (*pcb)->mSP = AllocateMemory(stack_size);
  (*pcb)->args = args;
}

