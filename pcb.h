#ifndef _H_PCB
#define _H_PCB

#include "standart.h"


// ----------------------------------------------------------------- PCB DEFINES

#define STACK_SIZE 1024 * 32
#define REGISTER_COUNT 13


// ------------------------------------------------------------------- PCB TYPES

typedef void (*func_t)(void *);

typedef enum {PCB_PAUSE, PCB_READY, PCB_RUN} pcb_state;

typedef struct pcb_s
{
	// State
	pcb_state mState;

	// Process ID
	uint32_t mPID;

	// PC = program counter
	uint32_t mPC;

	// stack head
	uint32_t * mStack;

	// SP = stack counter
	uint32_t * mSP;

	// next pcb
	struct pcb_s * mNext;
} _pcb_s;


// --------------------------------------------------------------- PCB FUNCTIONS

void
pcb_init(struct pcb_s* pcb, func_t f, uint32_t stack_size);

void
pcb_release(struct pcb_s* pcb);

void
pcb_switch_to(struct pcb_s* oldPcb, struct pcb_s* newPcb);

/* ARM documentation on multiple pushes/pops
 * The registers are stored in sequence, the lowest-numbered register to the
 * lowest memory address (start_address), through to the highest-numbered
 * register to the highest memory address (end_address)
 */
#define pcb_set_register(pcb,registerId,value) \
    (pcb)->mSP[- REGISTER_COUNT + (registerId)] = (uint32_t)(value)

#endif
