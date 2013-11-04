#ifndef _H_KERNEL_DISPATCHER
#define _H_KERNEL_DISPATCHER

// -------------------------------------------------------------------- INCLUDES

#include "standart.h"


// --------------------------------------------------------------- PROCESS TYPES

typedef void (*process_func_t)(void *);


// ----------------------------------------------------------- PROCESS FUNCTIONS

/*
 * @infos : create an idle process
 *
 * @param <f> : process function to call
 * @param <args> : process arguments' pointer
 *
 * @asserts
 *  - <f> != 0
 *
 * @return
 *  - the non-null PID
 */
uint32_t
process_create(process_func_t f, void * args);

/*
 * @infos : start a process
 *
 * @param <pid> : the process's PID
 *
 * @return
 *  - 1 if succed (the process has just been created before)
 *  - 0 elsewhere
 */
uint32_t
process_start(uint32_t pid);

/*
 * @infos : get the current process's PID
 *
 * @return
 *  - the current process's PID
 */
uint32_t
process_get_pid();

/*
 * @infos : give back the CPU to other processes
 */
void
process_yield();

/*
 * @infos : stop and delete the process
 *
 * @return
 * - NEVER RETURNS
 */
void
process_exit() __attribute__ ((noreturn));

#endif
