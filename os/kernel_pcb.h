#ifndef _H_KERNEL_PCB
#define _H_KERNEL_PCB

#include "kernel_forward.h"


// ------------------------------------------------------------------- PCB TYPES

/*
 * @infos: PCB structure
 */
struct kernel_pcb_s
{
    // Process ID
    uint32_t mPID;

    // stack head
    uint32_t * mStack;

    // SP = stack counter
    uint32_t * mSP;

    // next in list containing all PCBs
    kernel_pcb_t * mGlobalNext;

    // next pcb in a list
    kernel_pcb_t * mNext;

    // ptr on the list where it is
    kernel_pcb_list_t * mParentList;

    // scheduler list
    kernel_pcb_list_t * mSchedulerList;
};

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
