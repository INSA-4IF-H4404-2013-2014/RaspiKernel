#include <stdint.h>
#include "memory.h"
#include "allocateMemory.h"

uint32_t* malloc(uint32_t size)
{
	return AllocateMemory(size);
}


int free(uint32_t* address)
{
	return FreeAllocatedMemory(address);
}
