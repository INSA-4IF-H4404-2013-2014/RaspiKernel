#include "kernel_memory.h"
#include "kernel_memory_private.h"

#include "kernel_config.h"


static char kernel_memory_heap[KERNEL_HEAP_SIZE];

static const void *
	KERNEL_HEAP_ADDR_MIN = kernel_memory_heap + 2 * sizeof(kernel_heap_part_s);

static const void *
	KERNEL_HEAP_ADDR_MAX = (void *) KERNEL_HEAP_SIZE - sizeof(kernel_heap_part_s);


void kernel_memory_init()
{
	kernel_heap_part_s * pHead = (kernel_heap_part_s *) kernel_memory_heap;

	kernel_heap_part_s *
		pFoot = (kernel_heap_part_s *)
			(kernel_memory_heap + KERNEL_HEAP_SIZE - sizeof(kernel_heap_part_s));

	pHead->mpNext = pFoot;
	pHead->mpPrevious = 0;
	pHead->mSize = 0;

	pFoot->mpNext = 0;
	pFoot->mpPrevious = pHead;
	pHead->mSize = 0;
}

void * kernel_allocate_memory(uint32_t size)
{
	return (void *)0;
}

void kernel_deallocate_memory(void * address)
{
	// Boudaries check for address
	if(address < KERNEL_HEAP_ADDR_MIN || address >= KERNEL_HEAP_ADDR_MAX)
	{
		// KALASHNIKOV
		for ( ; ; );
	}

	// We get the kernel memory header pointer
	kernel_heap_part_s * heap_part_head = &(((kernel_heap_part_s *) address)[-1]);

	// Some other checks for address validity
	if(heap_part_head->mpPrevious->mpNext != heap_part_head ||
		heap_part_head->mpNext->mpPrevious != heap_part_head)
	{
		// KALASHNIKOV
		for ( ; ; );
	}


    // User gave us valid address. We can start deallocate!
	if(heap_part_head->mpPrevious)
	{
		heap_part_head->mpPrevious->mpNext = heap_part_head->mpNext;
	}

	if(heap_part_head->mpNext)
	{
		heap_part_head->mpNext->mpPrevious = heap_part_head->mpPrevious;
	}
}
