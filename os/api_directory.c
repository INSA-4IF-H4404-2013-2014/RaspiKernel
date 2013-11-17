
#include "api_directory.h"
#include "kernel_scheduler.h"
#include "kernel_fat_bpb.h"

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

