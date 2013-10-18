#ifndef SCHED_H
#define SCHED_H

#include <stdint.h>

#include "dispatcher.h"
#include "hw.h"


/*
 * Constants
 */
static const unsigned int STACK_SIZE = 128;


/*
 * Methods
 */
void create_process(func_t f, void* args);
void yield();
void exit();
void start_sched();

#endif
