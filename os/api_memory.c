
#include "api_memory.h"
#include "kernel_scheduler.h"
#include "allocateMemory.h"


void *
malloc(uint32_t size)
{
    kernel_pause_scheduler();

    void * ptr = AllocateMemory(size);

    kernel_resume_scheduler();

    return ptr;
}

void
free(void * ptr)
{
    kernel_pause_scheduler();

    FreeAllocatedMemory(ptr);

    kernel_resume_scheduler();
}

