#ifndef _H_KERNEL_FAT
#define _H_KERNEL_FAT

#include "standard.h"


typedef struct kernel_fat_file_s kernel_fat_file_t;
typedef struct kernel_fat_bpb_s kernel_fat_bpb_t;


/*
 * @infos: encode <path>
 *
 * @param <encoded>: encode destination
 * @param <path>: encode path
 */
void
kernel_fat_encode_name(char encoded[12], const char * path);


#endif
