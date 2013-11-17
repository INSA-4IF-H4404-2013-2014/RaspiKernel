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


#endif
