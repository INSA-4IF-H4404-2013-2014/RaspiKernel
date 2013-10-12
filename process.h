#ifndef _H_DISPATCHER
#define _H_DISPATCHER

#include "pcb.h"


// --------------------------------------------------------------- PROCESS TYPES

typedef void (*process_func_t)(void *);


// ----------------------------------------------------------- PROCESS FUNCTIONS

uint32_t
process_create(process_func_t f, void * args);

uint32_t
process_start(uint32_t pid);

uint32_t
process_get_pid();

void
process_yield();

void
process_exit() __attribute__ ((noreturn));

#endif
