#ifndef _H_KERNEL_MEMORY
#define _H_KERNEL_MEMORY

#include "standart.h"

void kernel_memory_init();

void * kernel_allocate_memory(uint32_t size);
void * kernel_deallocate_memory(void * address);

#endif
