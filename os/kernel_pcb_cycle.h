#ifndef _H_KERNEL_PCB_CYCLE
#define _H_KERNEL_PCB_CYCLE

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
#define pcb_cycle_next(pcb) \
    (pcb)->mNext

/*
 * @infos : get the previous followed pcb
 *
 * @param <pcb> : a valid pcb pointer
 *
 * @asserts
 *  - <pcb> != 0
 */
struct pcb_s*
pcb_cycle_previous(struct pcb_s* pcb);

/*
 * @infos : get the next pcb that has the ready state
 *
 * @param <pcb> : a valid pcb pointer
 *
 * @asserts
 *  - <pcb> != 0
 */
struct pcb_s *
pcb_cycle_next_ready(struct pcb_s * pcb);

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
struct pcb_s *
pcb_cycle_by_pid(struct pcb_s * pcb_head, uint32_t pid);

/*
 * @infos : append a alone PCB in a PCB cycle
 *
 * @param <pcb_cycle> : a PCB cycle head pointer
 *
 * @asserts
 *  - <pcb_cycle> != 0
 *  - <pcb> != 0
 *  - <pcb> is alone (pcb = pcb->mNext)
 */
void
pcb_cycle_append(struct pcb_s ** pcb_cycle, struct pcb_s * pcb);

/*
 * @infos : remove the cycle head
 *
 * @param <pcb_cycle> : a PCB cycle
 *
 * @asserts
 *  - <pcb_cycle> != 0
 *  - <*pcb_cycle> != 0
 *
 * @returns
 *  - an alone PCB
 */
struct pcb_s *
pcb_cycle_rm_current(struct pcb_s ** pcb_cycle);


#endif
