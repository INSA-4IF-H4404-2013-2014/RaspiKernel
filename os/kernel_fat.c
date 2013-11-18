
#include "kernel_fat.h"


void
kernel_fat_encode_name(char encoded[12], const char * path)
{
    uint32_t i = 0;
    char c = path[0];

    while (c && c != '/' && c != '.')
    {
        if (c >= 'a' && c < 'z')
        {
            c += 'A' - 'a';
        }

        encoded[i] = c;

        i++;

        if (i == 8)
        {
            encoded[8] = 0x20;
            encoded[9] = 0x20;
            encoded[10] = 0x20;
            encoded[11] = 0x0;
            return;
        }

        c = path[i];
    }

    if (c != '.')
    {
        for ( ; i < 11; i++)
        {
            encoded[i] = 0x20;
        }
        encoded[11] = 0x0;

        return;
    }

    path += i + 1;

    for ( ; i < 8; i++)
    {
        encoded[i] = 0x20;
    }

    encoded += 8;
    c = path[0];
    i = 0;

    while (c && c != '/' && c != '.')
    {
        if (c >= 'a' && c < 'z')
        {
            c += 'A' - 'a';
        }

        encoded[i] = c;

        i++;

        if (i == 3)
        {
            encoded[3] = 0x0;
            return;
        }

        c = path[i];
    }

    for ( ; i < 3; i++)
    {
        encoded[i] = 0x20;
    }
    encoded[3] = 0x0;
}

const char *
kernel_fat_next_dir(const char * path)
{
    while (*path)
    {
        if (*path == '/')
        {
            path++;

            return path;
        }

        path++;
    }

    return 0;
}

