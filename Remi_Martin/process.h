#ifndef _H_PROCESS
#define _H_PROCESS

#define STACK_SIZE 1024 * 32
#define REGISTER_COUNT 13

//Process states for the scheduler
typedef enum {NEW, READY, RUNNING, WAITING} processState;

typedef void (*func_t)();

#include "shed.h"

typedef struct _pcb_s
{
  processState state;

  void * args;

  // PC = program counter
  unsigned int mPC;

  // SP = stack pointer : contains the entire stack address
  unsigned int mSP;

  // registers
  // PLUS UTILISES !
  unsigned int mR[REGISTER_COUNT];
} pcb_s;

void init_pcb(pcb_s* pcb, func_t f, unsigned int stack_size, void * args);

#endif

