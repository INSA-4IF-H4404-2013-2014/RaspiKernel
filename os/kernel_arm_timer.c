
#include "kernel_arm_timer.h"
#include "kernel_config.h"


void
kernel_arm_timer_init()
{
    // enables IRQ mailboxing
    kernel_arm_addr32(0x2000B210) = 0x00000002;

    kernel_arm_timer_frequency_divisor(KERNEL_TIMER_FREQUENCY_DIVISOR);
}

