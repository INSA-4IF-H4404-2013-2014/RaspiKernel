#ifndef _H_DISPATCHER
#define _H_DISPATCHER

#include "process.h"

void ctx_switch(pcb_s * oldPcb, pcb_s * newPcb);

#endif

