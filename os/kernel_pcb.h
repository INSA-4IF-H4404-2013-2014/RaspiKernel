#ifndef _H_KERNEL_PCB
#define _H_KERNEL_PCB

#include "standart.h"


// ----------------------------------------------------------------- PCB DEFINES

#define STACK_SIZE 1024 * 32
#define REGISTER_COUNT 13


// ------------------------------------------------------------------- PCB TYPES

typedef void (*pcb_func_t)(void);

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

        // next (fifos)
        struct pcb_s * mNextFifo;
} kernel_pcb_t;


// --------------------------------------------------------------- PCB FUNCTIONS

/*
 * @infos : Init a PCB :
 *  - the pcb's state will be set to PCB_PAUSE
 *  - mPID will be assigned (0 is reserved for the kernel)
 *  - alloc the stack
 *  - pcb->mNext == pcb
 *
 * @param <pcb> : a valid pcb pointer
 * @param <f> : the start address
 * @param <stack_size> : stack's size
 *
 * @asserts
 *  - <pcb> != 0
 *  - <pcb> has not been initialized before
 *  - <stack_size> != 0
 */
void
pcb_init(struct pcb_s* pcb, pcb_func_t f, uint32_t stack_size);

/*
 * @infos : Release a PCB :
 *  - release the stack
 *
 * @param <pcb> : the released pcb
 *
 * @asserts
 *  - <pcb> != 0
 *  - <has> been initialized before
 */
void
pcb_release(struct pcb_s* pcb);

/*
 * @infos : Switch to another PCB :
 *  - save the current execution in <oldPcb> and switch to the <newPcb>
 *
 * @param <old_pcb> : the pcb to save the current execution
 * @param <new_pcb> : the pcb to switch to
 *
 * @asserts
 *  - <new_pcb> != 0
 */
void
pcb_switch_to(struct pcb_s* old_pcb, struct pcb_s* new_pcb);

/*
 * @infos : Set a non-running pcb's register's value
 *
 * @param <pcb> : the non-running pcb
 * @param <register_id> : the register's id
 * @param <value> : the register's value to set
 *
 * @asserts
 *  - <pcb> != 0
 *  - 0 <= <register_id> < REGISTER_COUNT
 *
 * @external : ARM documentation on multiple pushes/pops
 *  The registers are stored in sequence, the lowest-numbered register to the
 *  lowest memory address (start_address), through to the highest-numbered
 *  register to the highest memory address (end_address)
 */
#define pcb_set_register(pcb,register_id,value) \
    (pcb)->mSP[- REGISTER_COUNT + (register_id)] = (uint32_t)(value)

#endif
