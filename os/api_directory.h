#ifndef _H_API_DIRECTORY
#define _H_API_DIRECTORY

#include "standard.h"


/*
 * @infos: mount a FAT memory partition
 */
uint32_t
directory_mount_fat_mem(void * memory);

/*
 * @infos: test a file exists
 *
 * @param <path>: path to test
 *
 * @return:
 *  - 1 if exists
 *  - 0 elsewhere
 */
uint32_t
directory_exists(const char * path);

/*
 * @infos: load a file's content
 */
void *
file_load(const char * path);


#endif
