#ifndef _H_KERNEL_MATH
#define _H_KERNEL_MATH

#include "standard.h"


/*
 * @infos: get log2
 */
uint32_t
kernel_math_log2_u32(uint32_t value);


/*
 * @infos: divide by a power of two
 */
#define kernel_math_divide_PO2(a,b) \
    ((a) >> kernel_math_log2_u32(b))


#endif
