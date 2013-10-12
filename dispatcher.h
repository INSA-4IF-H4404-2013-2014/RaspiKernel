#ifndef _H_DISPATCHER
#define _H_DISPATCHER

#include "pcb.h"

uint32_t
process_create(func_t f, void * args);

void
process_yield();

void
process_exit() __attribute__ ((noreturn));

#endif
