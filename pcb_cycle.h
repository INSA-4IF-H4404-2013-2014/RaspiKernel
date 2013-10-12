#ifndef _H_PCB_CYCLE
#define _H_PCB_CYCLE

#include "pcb.h"


// --------------------------------------------------------- PCB CYCLE FUNCTIONS

#define pcb_cycle_next(pcb_cycle) \
    (pcb_cycle)->mNext

struct pcb_s*
pcb_cycle_previous(struct pcb_s* pcb);

void
pcb_cycle_append(struct pcb_s ** pcb_cycle, struct pcb_s * pcb);

struct pcb_s *
pcb_cycle_rm_current(struct pcb_s ** pcb_cycle);


#endif
