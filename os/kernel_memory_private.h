#ifndef _H_KERNEL_MEMORY_PRIVATE
#define _H_KERNEL_MEMORY_PRIVATE

#include "standart.h"


/*
 * @infos: Kernel heap structure
 *
 * @members:
 * - mpNext: pointer to the next memory element
 * - mpPrevious: pointer to the previous memory element
 * - mSize: size (in bytes) of the following user space
 */
typedef struct _kernel_heap_part_s
{
	struct _kernel_heap_part_s * mpNext;
	struct _kernel_heap_part_s * mpPrevious;
	uint32_t mSize;
} kernel_heap_part_s;

#endif
