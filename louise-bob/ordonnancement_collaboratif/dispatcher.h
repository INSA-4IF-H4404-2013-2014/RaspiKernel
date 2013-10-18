#ifndef DISPATCHER_H
#define DISPATCHER_H

#include <stdint.h>

#include "process.h"


/*
 * Methods 
 */
void __attribute__((naked)) start_current_ctx();
void ctx_switch();

#endif
