#ifndef _H_API_MEMORY
#define _H_API_MEMORY

#include "standart.h"


//-------------------------------------------------------------------------------- FUNCTIONS

/*
 * @infos: alloc in memory
 *
 * @param <size>: the size needed
 *
 * @return:
 *  - nullptr if memory allocation failed
 *  - pointer on the memory block if succed
 */
void *
malloc(uint32_t size);

/*
 * @infos: release memory block to the OS
 *
 * @param <ptr>: ptr on the memory block to free
 *
 * @assert:
 *  - this memory block as been allocated by malloc() before
 */
void
free(void * ptr);

#endif
