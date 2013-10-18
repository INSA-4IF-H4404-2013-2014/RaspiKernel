#ifndef _H_DISPATCHER
#define _H_DISPATCHER

#include "process.h"

void __attribute__((naked)) ctx_switch();

void exit_process();

#endif

