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

	// next pcb
	struct pcb_s * mNext;
} _pcb_s;

void init_pcb(struct pcb_s* pcb, func_t f, unsigned int stack_size);

void pcb_switch_to(struct pcb_s* oldPcb, struct pcb_s* newPcb);

void pcb_set_register(struct pcb_s* pcb, unsigned int registerId, unsigned int value);

/* ARM documentation on multiple pushes/pops
 * The registers are stored in sequence, the lowest-numbered register to the
 * lowest memory address (start_address), through to the highest-numbered
 * register to the highest memory address (end_address)
 */
#define pcb_set_register(pcb,registerId,value) \
    ((unsigned int *)((pcb)->mSP))[- REGISTER_COUNT + (registerId)] = (unsigned int)(value)


#endif

