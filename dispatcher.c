
#include "dispatcher.h"
#include "allocateMemory.h"

static struct pcb_s * current_pcb = 0;

static void
append(struct pcb_s ** pcb_cycle, struct pcb_s * pcb)
{
	if (*pcb_cycle == 0)
	{
		(*pcb_cycle) = pcb;
	}
	else
	{
		pcb->mNext = (*pcb_cycle)->mNext;
		(*pcb_cycle)->mNext = pcb;
	}
}

static struct pcb_s *
cycle_next(struct pcb_s * current_pcb)
{
	struct pcb_s * next_pcb = current_pcb->mNext;
	
	while (next_pcb->mState != PCB_READY)
	{
		if (next_pcb == current_pcb)
		{
			break;
		}

		next_pcb = next_pcb->mNext;
	}

	return next_pcb;
}

int
create_process(func_t f, void * args)
{
	struct pcb_s * newPcb = (struct pcb_s *) AllocateMemory(sizeof(struct pcb_s));

	init_pcb(newPcb, f, STACK_SIZE);
	newPcb->mR[0] = (unsigned int) args;

	append(&current_pcb, newPcb);

	return 1;
}

void
yield()
{
	struct pcb_s * previous_pcb = current_pcb;
	struct pcb_s * next_pcb = cycle_next(previous_pcb);

	if (next_pcb == previous_pcb)
	{
		return;
	}

	previous_pcb->mState = PCB_READY;
	next_pcb->mState = PCB_RUN;
	current_pcb = next_pcb;

	pcb_switch_to(previous_pcb, next_pcb);
}
