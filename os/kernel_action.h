#ifndef _H_KERNEL_ACTION
#define _H_KERNEL_ACTION

#include "kernel_pcb.h"


/*
 * @infos: create a new PCB
 *
 * @param <f>: entry point address
 * @param <args>: parameter
 */
kernel_pcb_t *
kernel_pcb_create(void * f, void * args);

/*
 * @infos: find a PCB with a given pid
 *
 * @param <pid>: PID to search
 *
 * @return:
 *  - nullptr if this process doesn't exist
 *  - a pointer on the process found
 */
kernel_pcb_t *
kernel_pcb_global_by_pid(uint32_t pid);

/*
 * @infos: get a <pcb> state
 *
 * @param <pcb>: a PCB
 *
 * @return:
 *  - API_STATE_RUNNING if <pcb> is the current executing pcb
 *  - API_STATE_READY if <pcb> in its ready list
 *  - API_STATE_PAUSE elsewhere
 */
process_state_t
kernel_pcb_get_state(kernel_pcb_t * pcb);

/*
 * @infos: start a <pcb>
 *
 * @param <pcb>: a PCB to switch state to READY
 */
void
kernel_pcb_start(kernel_pcb_t * pcb);

/*
 * @infos: switch a <pcb>'s state to PAUSE
 *
 * @param <pcb>: a PCB to switch state to PAUSE
 */
void
kernel_pcb_pause(kernel_pcb_list_t * pause_list, kernel_pcb_t * pcb);

/*
 * @infos: switch the current PCB to PAUSE
 *
 * @cautions:
 *  - automatiquely call kernel_resume_scheduler()
 */
void
kernel_pcb_self_pause(kernel_pcb_list_t * pause_list);

/*
 * @infos: destroy a given <pcb>
 *
 * @param <pcb>: PCB to destroy
 */
void
kernel_pcb_destroy(kernel_pcb_t * pcb);

#endif
