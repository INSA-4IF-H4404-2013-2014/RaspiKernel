#ifndef _H_KERNEL_FAT_FILE
#define _H_KERNEL_FAT_FILE

#include "kernel_fat.h"


/*
 * @infos: define an FAT file info
 */
typedef struct kernel_fat_file_s
{
    /*
     * @infos: name of the file
     */
    char name[12];

    /*
     * @infos: bitfield of KERNEL_FAT_ATTR_*
     */
    uint8_t attr;

    /*
     * @infos: size of the file
     */
    uint32_t size;

    /*
     * @infos: first cluster id
     */
    union
    {
        uint32_t first_cluster;

        struct
        {
            uint16_t first_cluster_lo;
            uint16_t first_cluster_hi;
        };
    };

} kernel_fat_file_t;


/*
 * @infos: Fetches <file>'s info at a given <pos> in a given <sector>
 */
void
kernel_fat_file_info(kernel_fat_bpb_t * bpb, uint32_t sector, uint32_t pos, kernel_fat_file_t * file);

/*
 * @infos: Fetches <file>'s info from a temp buffer
 */
void
kernel_fat_file_fetch(kernel_fat_file_t * file, const void * temp_buffer);

/*
 * @infos: Compare an <encoded> name and a <current> file
 *
 * @param <encoded>: encoded name
 * @param <current>: pointer on the current file in en temp buffer
 *
 * @return:
 *  - 1 if matches
 *  - 0 elsewhere
 */
uint32_t
kernel_fat_cmp_encode_src(const char encoded[12], void * current);


#endif
