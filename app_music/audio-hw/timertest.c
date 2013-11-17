#include <stdint.h>

#include "../os/kernel_arm.h"
#include "timertest.h"
#include "registers.h"


static uint32_t timer_ms_base; // 'zero' time

uint32_t get_timer_ms()
{
    // Return ms elapsed since timer_ms_base. This is currently approximate - should do the math properly.
    return ((((uint64_t)kernel_arm_addr32(SYSTIMERCHI) << 32) | (uint64_t)kernel_arm_addr32(SYSTIMERCLO)) >> 10) - timer_ms_base;
}


uint32_t reset_timer_ms()
{
    timer_ms_base = 0;
    timer_ms_base = get_timer_ms();
    return timer_ms_base;
}
