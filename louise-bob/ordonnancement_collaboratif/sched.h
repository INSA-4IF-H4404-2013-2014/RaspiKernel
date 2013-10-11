#ifndef SCHED_H
#define SCHED_H

#include <stdint.h>

#include "dispatcher.h"


/*
 * Constants
 */
static const unsigned int STACK_SIZE = 128;

/*
 * Static variables
 */
static struct pcb_s* current_process;

/*
 * Methods
 */
void create_process(func_t f, void* args);
void yield();
void start_current_process();

#endif
