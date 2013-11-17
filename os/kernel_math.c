
#include "kernel_math.h"


uint32_t
kernel_math_log2_u32(uint32_t value)
{
    uint32_t log = 0;

    while ((1u << log) != value)
    {
        log++;
    }

    return log;
}

