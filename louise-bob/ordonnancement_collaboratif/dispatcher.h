#ifndef DISPATCHER_H
#define DISPATCHER_H

#include <stdint.h>

#include "process.h"


/*
 * Methods 
 */
//void switch_to(struct ctx_s* ctx);
void ctx_switch(/*struct pcb_s* old_pcb, struct pcb_s* new_pcb*/);

#endif
