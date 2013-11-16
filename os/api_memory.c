
#include "api_memory.h"
#include "kernel_scheduler.h"
#include "kernel_memory.h"


void *
malloc(uint32_t size)
{
    kernel_pause_scheduler();

    void * ptr = kernel_allocate_memory(size);

    kernel_resume_scheduler();

    return ptr;
}

void
free(void * ptr)
{
    kernel_pause_scheduler();

    kernel_deallocate_memory(ptr);

    kernel_resume_scheduler();
}

