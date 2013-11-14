#include "kernel_memory.h"
#include "kernel_memory_private.h"

#include "kernel_config.h"

static char kernel_memory_heap[KERNEL_HEAP_SIZE];


void kernel_memory_init()
{
	kernel_heap_part_s * pHead = (kernel_heap_part_s *) kernel_memory_heap;
	pHead->mNextPart = 0;
	pHead->mPreviousPart = 0;
	pHead->mSize = 0;
}

void * kernel_allocate_memory(uint32_t size)
{
	return (void *)0;
}

void * kernel_deallocate_memory(void * address)
{
	return (void *)0;
}
