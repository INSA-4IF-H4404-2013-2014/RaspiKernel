#ifndef _H_KERNEL_MEMORY_PRIVATE
#define _H_KERNEL_MEMORY_PRIVATE

#include "standart.h"

typedef struct _kernel_heap_part_s
{
	struct _kernel_heap_part_s * mpNext;
	struct _kernel_heap_part_s * mpPrevious;
	uint32_t mSize;
} kernel_heap_part_s;

#endif
