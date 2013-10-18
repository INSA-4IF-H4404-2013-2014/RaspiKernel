#ifndef _H_SHED
#define _H_SHED

#include "process.h"
#include "list.h"

Tmaillon * next_running;

//Create a new ready process
void create_process(func_t f, void * args);


void start_current_process();

#endif
