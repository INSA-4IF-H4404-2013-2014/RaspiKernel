
#include "api_directory.h"
#include "kernel_scheduler.h"
#include "kernel_fat_bpb.h"
#include "kernel_memory.h"


static kernel_fat_bpb_t kernel_bpb;


/*
 * @infos: only call by kernel_main()
 */
void
kernel_directory_api_init()
{
    kernel_bpb.type = 0;
}

uint32_t
directory_mount_fat_mem(void * memory)
{
    kernel_pause_scheduler();

    if (kernel_fat_bpb_init(&kernel_bpb, memory) != 1)
    {
        kernel_resume_scheduler();
        return 0;
    }

    kernel_resume_scheduler();

    return 1;
}

uint32_t
directory_exists(const char * path)
{
    if (path[0] != '/')
    {
        return 0;
    }

    kernel_pause_scheduler();

    if (!kernel_bpb.type)
    {
        kernel_resume_scheduler();
        return 0;
    }

    if (path[1] == 0)
    {
        kernel_resume_scheduler();
        return 1;
    }

    uint32_t found = kernel_fat_bpb_find(&kernel_bpb, nullptr, path + 1);

    kernel_resume_scheduler();

    return found;
}

void *
file_load(const char * path)
{
#if 0
    if (path[0] != '/')
    {
        return nullptr;
    }

    {
        uint32_t i = 0;

        while (path[i + 1])
        {
            i++;
        }

        if (path[i] == 0)
        {
            return nullptr;
        }
    }
#endif

    kernel_pause_scheduler();

    if (!kernel_bpb.type)
    {
        kernel_resume_scheduler();
        return nullptr;
    }

    kernel_fat_file_t file;

    if (!kernel_fat_bpb_find(&kernel_bpb, &file, path + 1))
    {
        kernel_resume_scheduler();
        return nullptr;
    }

    if ((file.attr & KERNEL_FAT_ATTR_DIRECTORY) || file.size == 0)
    {
        kernel_resume_scheduler();
        return nullptr;
    }

    char * content = kernel_allocate_memory(file.size);

    kernel_fat_bpb_read_cluster(&kernel_bpb, content, file.first_cluster, 0, file.size);

    kernel_resume_scheduler();

    return content;
}

