#ifndef _H_KERNEL_PCB
#define _H_KERNEL_PCB

#include "standart.h"


// ----------------------------------------------------------------- PCB DEFINES

#define STACK_SIZE 1024 * 32
#define REGISTER_COUNT 13


// ------------------------------------------------------------------- PCB TYPES

typedef void (*pcb_func_t)(void);

typedef enum {PCB_PAUSE, PCB_READY, PCB_RUN} pcb_state;



/*
 * @infos: PCB structure
 */
typedef struct pcb_s
{
	// State
	pcb_state mState;

	// Process ID
	uint32_t mPID;

	// stack head
	uint32_t * mStack;

	// SP = stack counter
	uint32_t * mSP;

	// next pcb
	struct pcb_s * mNext;

        // next (fifos)
        struct pcb_s * mNextFifo;
} kernel_pcb_t;

/* Stack storage when PCB is not running:
 *
 * mSP ->   r0
 *          r1
 *          r2
 *          r3
 *          r4
 *          r5
 *          r6
 *          r7
 *          r8
 *          r9
 *          r10
 *          r11
 *          r12
 *          r14 (lr)
 *          r15 (pc)
 *          cpsr
 *          . CALL STACK...
 *          .
 *          .
 */


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
kernel_pcb_init(kernel_pcb_t * pcb, pcb_func_t f, uint32_t stack_size);

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
kernel_pcb_release(kernel_pcb_t * pcb);

/*
 * @infos : Accesses a non-running pcb's register's value
 *
 * @param <pcb> : the non-running pcb
 * @param <N> : the register's id
 *
 * @return: uint32_t reference
 *
 * @asserts
 *  - <pcb> != 0
 *  - 0 <= <N> < REGISTER_COUNT
 */
#define kernel_pcb_rN(pcb,N) \
    ((pcb)->mSP[(N)])

#define kernel_pcb_lr(pcb) \
    ((pcb)->mSP[13])

#define kernel_pcb_pc(pcb) \
    ((pcb)->mSP[14])

/*
 * @infos : Set a non-running pcb's register's value
 *
 * @param <pcb> : the non-running pcb
 * @param <N> : the register's id
 * @param <value> : the register's value to set
 *
 * @asserts
 *  - <pcb> != 0
 *  - 0 <= <N> < REGISTER_COUNT
 */
#define kernel_pcb_set_rN(pcb,N,value) \
    kernel_pcb_rN(pcb,N) = (uint32_t)(value)

#define kernel_pcb_set_lr(pcb,value) \
    kernel_pcb_lr(pcb) = (uint32_t)(value)

#define kernel_pcb_set_pc(pcb,value) \
    kernel_pcb_pc(pcb) = (uint32_t)(value)

#endif
