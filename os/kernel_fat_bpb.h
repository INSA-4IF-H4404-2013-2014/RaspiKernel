#ifndef _H_KERNEL_FAT_BPB
#define _H_KERNEL_FAT_BPB

#include "kernel_math.h"
#include "kernel_fat_file.h"

typedef enum
{
    KERNEL_FAT_UNKNOWN = 0,
    KERNEL_FAT12,
    KERNEL_FAT16,
    KERNEL_FAT32 // not yet
} kernel_fat_type_t;


/*
 * @definition BPB: BIOS Parameter Block
 * @definition BS: Boot Sector
 */
typedef struct kernel_fat_bpb_s
{
    kernel_fat_type_t type;
    void * content;

    uint32_t BS_jmpBoot; // uint24_t !!!
    char BS_OEMName[9];
    uint16_t BPB_BytsPerSec;
    uint8_t BPB_SecPerClus;
    uint16_t BPB_RsvdSecCnt;
    uint8_t BPB_NumFATs;
    uint16_t BPB_RootEntCnt;
    uint16_t BPB_TotSec16;
    uint8_t BPB_Media;
    uint16_t BPB_FATSz16;
    uint16_t BPB_SecPerTrk;
    uint16_t BPB_NumHeads;
    uint32_t BPB_HiddSec;
    uint32_t BPB_TotSec32;

    union
    {
        struct // FAT12 / FAT16
        {
            uint8_t BS_DrvNum;
            uint8_t BS_Reserved1;
            uint8_t BS_BootSig;
            uint32_t BS_VolID;
            char BS_VolLab[12];
            char BS_FilSysType[9];
        };

    };
} kernel_fat_bpb_t;


uint32_t
kernel_fat_bpb_init(kernel_fat_bpb_t * bpb, void * first_sector_content);


/*
 * @infos: get the first root sector id
 */
#define kernel_fat_root_first_sector(bpb) \
    ((bpb)->BPB_RsvdSecCnt + (bpb)->BPB_NumFATs * (bpb)->BPB_FATSz16)

/*
 * @infos: count sector used by the root directory
 */
#define kernel_fat_root_sector_count(bpb) \
    kernel_math_divide_PO2((((uint32_t)(bpb)->BPB_RootEntCnt) * 32) + (((uint32_t)(bpb)->BPB_BytsPerSec) - 1), (uint32_t)(bpb)->BPB_BytsPerSec)

/*
 * @infos: compute the start of the data region, the first sector of cluster 2
 *      this offset os relative to the sector 0 (the BPB table)
 *
 * @return:
 *  - type: uint32_t
 *  - unit: sector
 */
#define kernel_fat_data_offset(bpb) \
    ((bpb)->BPB_RsvdSecCnt + ((bpb)->BPB_NumFATs * (bpb)->BPB_FATSz16) + kernel_fat_root_sector_count(bpb))

/*
 * @infos: compute the data sector offset relatively to the data offset
 *
 * @return:
 *  - type: uint32_t
 *  - unit: sector
 */
#define kernel_fat_data_cluster_offset(bpb,id) \
    ((id - 2) * (bpb)->BPB_SecPerClus)

/*
 * @infos: count the number of sector in the data region
 */
#define kernel_fat_count_data_sectors(bpb) \
    ((bpb)->BPB_TotSec16 - ((bpb)->BPB_RsvdSecCnt + ((bpb)->BPB_NumFATs * (bpb)->BPB_FATSz16) + kernel_fat_root_sector_count(bpb)))

/*
 * @infos: count the number of cluster in the data region
 *
 *  if (CountofClusters < 4085)
 *  {
 *      Volume is FAT12
 *  }
 *  else if (CountofClusters < 65525)
 *  {
 *      Volume is FAT16
 *  }
 *  else
 *  {
 *      Volume is FAT32
 *  }
 */
#define kernel_fat_count_data_clusters(bpb) \
    kernel_math_divide_PO2(kernel_fat_count_data_sectors(bpb), (bpb)->BPB_SecPerClus)

/*
 * @infos: return cluster size
 *
 * @return:
 *  - uint32_t cluster size in bytes
 */
#define kernel_fat_bpb_cluster_size(bpb) \
    (((uint32_t)(bpb)->BPB_SecPerClus) * ((uint32_t)(bpb)->BPB_BytsPerSec))

/*
 * @infos: special cases of kernel_fat_bpb_next_cluster()
 */
#define KERNEL_FAT_CLUSTER_ERROR 0
#define KERNEL_FAT_CLUSTER_LAST 1

/*
 * @infos: get the next cluster
 *
 * @param <bpb>: the BPB structure
 * @paran <cluster>: the cluster ID
 *
 * @return:
 *  - KERNEL_FAT_CLUSTER_ERROR if invalid sector (unused or non existing)
 *  - KERNEL_FAT_CLUSTER_LAST if do not have any next cluster
 *  - the next cluster id elsewhere
 */
uint32_t
kernel_fat_bpb_next_cluster(const kernel_fat_bpb_t * bpb, uint32_t cluster);

/*
 * @infos: find a <file> for a given path
 *
 * @param <bpb>: the BPB structure
 * @param <file>: the file structure to write infos to
 * @param <path>: the file's path to find
 *
 * @assert:
 *  - path do not begin by /
 */
uint32_t
kernel_fat_bpb_find(const kernel_fat_bpb_t * bpb, kernel_fat_file_t * file, const char * path);

/*
 * @infos: read a <cluster> in a given <size> and <offset>
 *
 * @param <bpb>: the BPB structure
 * @param <output_buffer>: dest buffer to copy to
 * @param <cluster>: the cluster ID
 * @param <offset>: offset in the cluster
 * @param <size>: size of the reading
 */
void
kernel_fat_bpb_read_cluster(const kernel_fat_bpb_t * bpb, void * output_buffer, uint32_t cluster, uint32_t offset, uint32_t size);


#endif
