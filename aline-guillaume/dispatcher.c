
#include "process.h"
#include "switch.h"
#include "dispatcher.h"

typedef struct ordo_s
{
	struct ctx_s current;
	struct ordo_s * next;
} _ordo_s;

static typedef struct * current;

int create_process(int stack_size, func_t f, void *args)
{
	
	return 1;
}

void yield()
{
	
}
