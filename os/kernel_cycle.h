#ifndef _H_KERNEL_kernel_cycle
#define _H_KERNEL_kernel_cycle

#include "kernel_pcb.h"


// --------------------------------------------------------- PCB CYCLE FUNCTIONS

/*
 * @infos : get the next followed pcb
 *
 * @param <pcb> : a valid pcb pointer
 *
 * @asserts
 *  - <pcb> != 0
 */
#define kernel_cycle_next(pcb) \
    (pcb)->mNext

/*
 * @infos : get the previous followed pcb
 *
 * @param <pcb> : a valid pcb pointer
 *
 * @asserts
 *  - <pcb> != 0
 */
kernel_pcb_t*
kernel_cycle_previous(kernel_pcb_t* pcb);

/*
 * @infos : get the next pcb that has the ready state
 *
 * @param <pcb> : a valid pcb pointer
 *
 * @asserts
 *  - <pcb> != 0
 */
kernel_pcb_t *
kernel_cycle_next_ready(kernel_pcb_t * pcb);

/*
 * @infos : get pcb by the PID in a pcbs' cycle
 *
 * @param <pcb_head> : a valid pcb pointer
 * @param <pid> : the PID to search
 *
 * @asserts
 *  - <pcb_head> != 0
 *
 * @returns
 *  - 0: if any pcb match PID
 *  - the associated PCB struct for the given <pid>
 */
kernel_pcb_t *
kernel_cycle_by_pid(kernel_pcb_t * pcb_head, uint32_t pid);

/*
 * @infos : append a alone PCB in a PCB cycle
 *
 * @param <kernel_cycle> : a PCB cycle head pointer
 *
 * @asserts
 *  - <kernel_cycle> != 0
 *  - <pcb> != 0
 *  - <pcb> is alone (pcb = pcb->mNext)
 */
void
kernel_cycle_append(kernel_pcb_t ** kernel_cycle, kernel_pcb_t * pcb);

/*
 * @infos : remove in cycle
 *
 * @param <kernel_cycle> : a PCB cycle
 * @param <pcb> : a PCB
 *
 * @asserts
 *  - <pcb> in <*kernel_cycle> != 0
 */
void
kernel_cycle_remove(kernel_pcb_t ** kernel_cycle, kernel_pcb_t * pcb);

#endif
