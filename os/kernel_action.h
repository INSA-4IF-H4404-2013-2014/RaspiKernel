#ifndef _H_KERNEL_ACTION
#define _H_KERNEL_ACTION

#include "kernel_pcb.h"

kernel_pcb_t *
kernel_pcb_create(void * f, void * args);

process_state_t
kernel_pcb_get_state(kernel_pcb_t * pcb);

uint32_t
kernel_pcb_start(kernel_pcb_t * pcb);

uint32_t
kernel_pcb_pause_other(kernel_pcb_t * pcb);

void
kernel_pcb_self_pause();

void
kernel_pcb_destroy(kernel_pcb_t * pcb);

#endif
