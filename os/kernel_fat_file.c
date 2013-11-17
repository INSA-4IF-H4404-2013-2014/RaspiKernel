
#include "kernel_fat_file.h"
#include "kernel_fat_bpb.h"


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

void
kernel_fat_file_info(kernel_fat_bpb_t * bpb, uint32_t sector, uint32_t pos, kernel_fat_file_t * file)
{
    void * current = ((char*)bpb->content) + sector * bpb->BPB_BytsPerSec + pos * 32;

    void_char_read_inc(file->name, 11, current);
    void_ptr_read_inc(uint8_t, file->attr, current);
    void_ptr_shift(current, 8);
    void_ptr_read_inc(uint16_t, file->first_cluster_hi, current);
    void_ptr_shift(current, 4);
    void_ptr_read_inc(uint16_t, file->first_cluster_lo, current);
    void_ptr_read_inc(uint32_t, file->size, current);
}

void
kernel_fat_file_fetch(kernel_fat_file_t * file, const void * temp_buffer)
{
    void_char_read_inc(file->name, 11, temp_buffer);
    void_ptr_read_inc(uint8_t, file->attr, temp_buffer);
    void_ptr_shift(temp_buffer, 8);
    void_ptr_read_inc(uint16_t, file->first_cluster_hi, temp_buffer);
    void_ptr_shift(temp_buffer, 4);
    void_ptr_read_inc(uint16_t, file->first_cluster_lo, temp_buffer);
    void_ptr_read_inc(uint32_t, file->size, temp_buffer);
}

uint32_t
kernel_fat_cmp_encode_src(const char encoded[12], void * current)
{
    while (*encoded)
    {
        if (*encoded != *((char*)current))
        {
            return 0;
        }

        encoded++;
        current++;
    }

    return 1;
}

