#ifndef _H_KERNEL_DISPATCHER
#define _H_KERNEL_DISPATCHER

// -------------------------------------------------------------------- INCLUDES

#include "standart.h"


// --------------------------------------------------------------- PROCESS TYPES

typedef void (*process_func_t)(void *);


// ----------------------------------------------------------- PROCESS FUNCTIONS

/*
 * @infos : create process in the PAUSE state
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
 * @infos: sets the process scheduler on a specified round robin level
 *
 * @param <pid>: the process's PID
 * @param <priority>: the round robin priority
 *
 * @return:
 *  - 1 if succed
 *  - 0 otherwise
 */
uint32_t
process_set_rr_priority(uint32_t pid, uint32_t priority);

/*
 * @infos: sets the process scheduler on the collaborative level
 *
 * @param <pid>: the process's PID
 *
 * @return:
 *  - 1 if succed
 *  - 0 otherwise
 */
uint32_t
process_set_collabo(uint32_t pid);

/*
 * @infos : pause a process
 *
 * @param <pid> : the process's PID
 *
 * @return
 *  - 1 if succed (the process has just been created before)
 *  - 0 elsewhere
 */
uint32_t
process_pause(uint32_t pid);

/*
 * @infos : start a process
 *
 * @param <pid> : the process's PID
 *
 * @return
 *  - 1 if succed
 *  - 0 elsewhere
 */
uint32_t
process_start(uint32_t pid);

/*
 * @infos: sleep a process
 *
 * @param <pid>: the process's PID to sleep
 * @param <duration>: the desired sleep duration in micro seconds
 *
 * @return
 *  - 1 if succed
 *  - 0 elsewhere
 */
uint32_t
process_sleep(uint32_t pid, uint32_t duration);

/*
 * @info : make the running process yield the hand to the next process with the hihest priority
 */
void
process_yield();

/*
 * @infos : get the current process's PID
 *
 * @return
 *  - the current process's PID
 */
uint32_t
process_get_pid();

/*
 * @infos : stop and delete the process
 *
 * @return
 * - NEVER RETURNS
 */
void
process_exit() __attribute__ ((noreturn));

#endif
