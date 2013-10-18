#ifndef _H_SHED
#define _H_SHED

#include "process.h"
#include "list.h"

Tmaillon * next_running;

//Create a new ready process
int create_process(int stack_size, func_t f, void * args);


void start_current_process();

void start_sched();

#endif
