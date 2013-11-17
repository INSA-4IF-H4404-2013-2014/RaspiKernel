
#include "kernel_fat.h"
#include "kernel_fat_bpb.h"
#include "kernel_fat_file.h"


#define void_ptr_shift(ptr,shift) \
    ptr = (void*)(((char*)(ptr)) + (shift))

#define void_ptr_read_inc(type,dest,ptr) \
    { \
        dest = *((type*)(ptr)); \
        void_ptr_shift(ptr, sizeof(type)); \
    }

#define void_char_read_inc(dest,size,ptr) \
    { \
        uint32_t i; \
        dest[size] = 0; \
        for (i = 0; i < size; i++) \
            dest[i] = ((char*)(ptr))[i]; \
        void_ptr_shift(ptr, size); \
    }

#define void_value_at(ptr,offset,type) \
    *((type*)(((char*)(ptr)) + offset))

uint32_t
kernel_fat_bpb_init(kernel_fat_bpb_t * bpb, void * first_sector_content)
{
    void * current = first_sector_content;

    if (
        void_value_at(current, 0, uint8_t) != 0xEB &&
        void_value_at(current, 0, uint8_t) != 0xE9
    )
    {
        // FAT alway begin by a x86 JUMP instruction
        return 0;
    }

    if (void_value_at(current, 510, uint16_t) != 0xAA55)
    {
        // not a FAT partition
        return 0;
    }


    bpb->BS_jmpBoot = ((uint32_t *)current)[0] & 0x00FFFFFF;
    void_ptr_shift(current, 3);

    void_char_read_inc(bpb->BS_OEMName, 8, current);
    void_ptr_read_inc(uint16_t, bpb->BPB_BytsPerSec, current);
    void_ptr_read_inc(uint8_t, bpb->BPB_SecPerClus, current);
    void_ptr_read_inc(uint16_t, bpb->BPB_RsvdSecCnt, current);
    void_ptr_read_inc(uint8_t, bpb->BPB_NumFATs, current);
    void_ptr_read_inc(uint16_t, bpb->BPB_RootEntCnt, current);
    void_ptr_read_inc(uint16_t, bpb->BPB_TotSec16, current);
    void_ptr_read_inc(uint8_t, bpb->BPB_Media, current);
    void_ptr_read_inc(uint16_t, bpb->BPB_FATSz16, current);
    void_ptr_read_inc(uint16_t, bpb->BPB_SecPerTrk, current);
    void_ptr_read_inc(uint16_t, bpb->BPB_NumHeads, current);
    void_ptr_read_inc(uint32_t, bpb->BPB_HiddSec, current);
    void_ptr_read_inc(uint32_t, bpb->BPB_TotSec32, current);

    if (bpb->BPB_FATSz16 == 0)
    {
        // we don't support FAT32 yet
        return 0;
    }

    void_ptr_read_inc(uint8_t, bpb->BS_DrvNum, current);
    void_ptr_read_inc(uint8_t, bpb->BS_Reserved1, current);
    void_ptr_read_inc(uint8_t, bpb->BS_BootSig, current);
    void_ptr_read_inc(uint32_t, bpb->BS_VolID, current);
    void_char_read_inc(bpb->BS_VolLab, 11, current);
    void_char_read_inc(bpb->BS_FilSysType, 8, current);

    uint32_t cluster_count = kernel_fat_count_data_clusters(bpb);

    if (cluster_count < 4085)
    {
        bpb->type = KERNEL_FAT12;
    }
    else if (cluster_count < 65525)
    {
        bpb->type = KERNEL_FAT16;
    }
    else
    {
        bpb->type = KERNEL_FAT32;
    }

    bpb->content = first_sector_content;

    return 1;
}

uint16_t
kernel_fat12_cluster_entry(kernel_fat_bpb_t * bpb, uint32_t id)
{
    uint32_t FATOffset = id + id / 2;

    uint32_t global_offset = bpb->BPB_RsvdSecCnt * bpb->BPB_BytsPerSec + FATOffset;

    uint16_t entry = ((uint16_t*)bpb->content)[global_offset];

    if (id & 0x1)
    {
        entry = entry >> 4;
    }
    else
    {
        entry &= 0x0FFF;
    }

    return entry;
}

static uint32_t
kernel_fat_bpb_rfind(const kernel_fat_bpb_t * bpb, uint32_t sector, uint32_t start_pos, kernel_fat_file_t * file, const char * path)
{
    void * current = ((char*)bpb->content) + sector * bpb->BPB_BytsPerSec + start_pos * 32;

    char encoded_name[12];

    kernel_fat_encode_name(encoded_name, path);

    for ( ; ; )
    {
        if (((uint8_t*)current)[0] == 0x00)
        {
            break;
        }

        if (((uint8_t*)current)[0] == 0xE5)
        {
            // the directory entry is free
            void_ptr_shift(current, 32);
            continue;
        }

        if (!kernel_fat_cmp_encode_src(encoded_name, current))
        {
            void_ptr_shift(current, 32);
            continue;
        }

        if (file)
        {
            kernel_fat_file_fetch(file, current);
        }

        return 1;
    }

    return 0;
}

uint32_t
kernel_fat_bpb_find(const kernel_fat_bpb_t * bpb, kernel_fat_file_t * file, const char * path)
{
    uint32_t root_sector = kernel_fat_root_first_sector(bpb);

    return kernel_fat_bpb_rfind(bpb, root_sector, 1, file, path);
}

