#ifndef _H_DISPATCHER
#define _H_DISPATCHER

int create_process(int stack_size, func_t f, void *args);

void yield();

#endif

