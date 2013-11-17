#ifndef _H_KERNEL_FAT_BPB
#define _H_KERNEL_FAT_BPB

#include "standard.h"


/*
 * @definition BPB: BIOS Parameter Block
 * @definition BS: Boot Sector
 */
typedef struct kernel_fat_bpb_s
{
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
 * @infos: count sector used by the root directory
 */
#define kernel_fat_root_sector_count(bpb) \
    ((((bpb)->BPB_RootEntCnt * 32) + ((bpb)->BPB_BytsPerSec – 1)) / (bpb)->BPB_BytsPerSec)

/*
 * @infos: compute the start of the data region, the first sector of cluster 2
 *      this offset os relative to the sector 0 (the BPB table)
 */
#define kernel_fat_data_offset(bpb) \
    ((bpb)->BPB_ResvdSecCnt + ((bpb)->BPB_NumFATs * (bpb)->BPB_FATSz16) + kernel_fat_root_sector_count(bpb))

/*
 * @infos: compute the data sector offset relatively to the data offset
 */
#define kernel_fat_data_cluster_offset(bpb,id) \
    ((id – 2) * (bpb)->BPB_SecPerClus)

/*
 * @infos: count the number of sector in the data region
 */
#define kernel_fat_count_data_sectors(bpb) \
    ( \
        (bpb)->BPB_TotSec16 – \
        ((bpb)->BPB_ResvdSecCnt + ((bpb)->BPB_NumFATs * (bpb)->BPB_FATSz16) + kernel_fat_root_sector_count(bpb)) \
    )

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
    (kernel_fat_count_data_sectors(bpb) / (bpb)->BPB_SecPerClus)

#endif
