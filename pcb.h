#ifndef _H_PCB
#define _H_PCB

#define STACK_SIZE 1024 * 32
#define REGISTER_COUNT 13

typedef void (*func_t)(void *);

typedef enum {PCB_PAUSE, PCB_READY, PCB_RUN} pcb_state;

typedef struct pcb_s
{
	// State
	pcb_state mState;

	// Process ID
	unsigned int mPID;

	// stack head
	unsigned int mStack;

	// PC = program counter
	unsigned int mPC;

	// SP = stack counter
	unsigned int mSP;

	// registers
	unsigned int mR[REGISTER_COUNT];

	// next pcb
	struct pcb_s * mNext;
} _pcb_s;

void init_pcb(struct pcb_s* pcb, func_t f, unsigned int stack_size);

void pcb_switch_to(struct pcb_s* oldPcb, struct pcb_s* newPcb);

#endif

