#ifndef _H_DISPATCHER
#define _H_DISPATCHER

#include "pcb.h"

int create_process(func_t f, void * args);

void yield();

void process_exit() __attribute__ ((noreturn));

#endif
