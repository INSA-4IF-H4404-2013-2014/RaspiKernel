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
 */
#define kernel_fat_data_offset(bpb) \
    ((bpb)->BPB_RsvdSecCnt + ((bpb)->BPB_NumFATs * (bpb)->BPB_FATSz16) + kernel_fat_root_sector_count(bpb))

/*
 * @infos: compute the data sector offset relatively to the data offset
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


uint32_t
kernel_fat_bpb_find(const kernel_fat_bpb_t * bpb, kernel_fat_file_t * file, const char * path);


#endif
