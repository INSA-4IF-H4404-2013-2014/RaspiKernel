
#include "kernel_plumbing.h"
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

uint32_t
kernel_fat_bpb_next_cluster(const kernel_fat_bpb_t * bpb, uint32_t cluster)
{
    uint32_t fat_offset;

    if (bpb->type == KERNEL_FAT12)
    {
        fat_offset = cluster + cluster / 2;
    }
    else if (bpb->type == KERNEL_FAT16)
    {
        fat_offset = cluster * 2;
    }
    else if (bpb->type == KERNEL_FAT32)
    {
        fat_offset = cluster * 4;
    }
    else
    {
        kernel_panic();
    }

    uint32_t partition_offset = bpb->BPB_RsvdSecCnt * bpb->BPB_BytsPerSec + fat_offset;

    uint32_t fat_info = *((uint32_t*)(((uint8_t*) bpb->content) + partition_offset));

    if (bpb->type == KERNEL_FAT12)
    {
        if (cluster & 0x1)
        {
            fat_info = fat_info >> 4;
        }

        fat_info &= 0x0FFF;

        if (fat_info >= 0xFF8)
        {
            return KERNEL_FAT_CLUSTER_LAST;
        }

        if (fat_info < 0x002 || fat_info > 0xFEF)
        {
            // special cluster
            return KERNEL_FAT_CLUSTER_ERROR;
        }

        return fat_info;
    }
    else if (bpb->type == KERNEL_FAT16)
    {
        fat_info &= 0xFFFF;

        if (fat_info >= 0xFFF8)
        {
            return KERNEL_FAT_CLUSTER_LAST;
        }

        if (fat_info < 0x0002 || fat_info > 0xFFEF)
        {
            // special cluster
            return KERNEL_FAT_CLUSTER_ERROR;
        }

        return fat_info;
    }

    fat_info &= 0x0FFFFFFF;

    if (fat_info >= 0xFFFFFF8)
    {
        return KERNEL_FAT_CLUSTER_LAST;
    }

    if (fat_info < 0x0000002 || fat_info > 0xFFFFFEF)
    {
        // special cluster
        return KERNEL_FAT_CLUSTER_ERROR;
    }

    return fat_info;
}

uint32_t
kernel_fat_bpb_rfind(const kernel_fat_bpb_t * bpb, uint32_t cluster, uint32_t start_pos, kernel_fat_file_t * file, const char * path)
{
    uint32_t cluster_offset = kernel_fat_data_cluster_offset(bpb, cluster) * bpb->BPB_BytsPerSec;
    uint32_t global_offset = kernel_fat_data_offset(bpb) * bpb->BPB_BytsPerSec + cluster_offset;
    void * current = ((char*)bpb->content) + global_offset + start_pos * 32;
    void * current_end = ((char*)current) + kernel_fat_bpb_cluster_size(bpb);

    if (cluster == 0)
    {
        current = ((char*)bpb->content) + kernel_fat_root_first_sector(bpb) * bpb->BPB_BytsPerSec + start_pos * 32;
        current_end = nullptr;
    }

    char encoded_name[12];

    kernel_fat_encode_name(encoded_name, path);

    for ( ; ; )
    {
        if (current == current_end)
        {
            uint32_t cluster = kernel_fat_bpb_next_cluster(bpb, cluster);

            if (cluster == KERNEL_FAT_CLUSTER_ERROR || cluster == KERNEL_FAT_CLUSTER_LAST)
            {
                return 0;
            }

            cluster_offset = kernel_fat_data_cluster_offset(bpb, cluster) * bpb->BPB_BytsPerSec;
            global_offset = kernel_fat_data_offset(bpb) * bpb->BPB_BytsPerSec + cluster_offset;
            current = ((char*)bpb->content) + global_offset + start_pos * 32;
            current_end = ((char*)current) + kernel_fat_bpb_cluster_size(bpb);
        }

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

        if (((uint8_t*)current)[11] == KERNEL_FAT_ATTR_LONG_NAME)
        {
            // we ignore the long name entry
            void_ptr_shift(current, 32);
            continue;
        }

        if (!kernel_fat_cmp_encode_src(encoded_name, current))
        {
            void_ptr_shift(current, 32);
            continue;
        }

        const char * next_path = kernel_fat_next_dir(path);

        if (next_path)
        {
            kernel_fat_file_t dir;

            kernel_fat_file_fetch(&dir, current);

            if ((dir.attr & KERNEL_FAT_ATTR_DIRECTORY) == 0)
            {
                // we are try to access in directory that is not a directory
                return 0;
            }

            return kernel_fat_bpb_rfind(bpb, dir.first_cluster, 0, file, next_path);
        }

        if (file)
        {
            kernel_fat_file_fetch(file, current);
        }

        return 1;
    }

    return 0;
}

void
kernel_fat_bpb_read_cluster(const kernel_fat_bpb_t * bpb, void * output_buffer, uint32_t cluster, uint32_t offset, uint32_t size)
{
    uint32_t data_offset = bpb->BPB_BytsPerSec * kernel_fat_data_offset(bpb);
    uint32_t cluster_offset = bpb->BPB_BytsPerSec * kernel_fat_data_cluster_offset(bpb, cluster) + data_offset;

    uint8_t * dest = ((uint8_t*) output_buffer);
    uint8_t * dest_end = dest + size;
    uint8_t * src = ((uint8_t*)bpb->content) + offset + cluster_offset;

    while (dest != dest_end)
    {
        *dest = *src;
        dest++;
        src++;
    }
}

