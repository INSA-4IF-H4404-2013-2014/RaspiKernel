
#include "kernel_plumbing.h"
#include "kernel_arm_timer.h"
#include "api_led.h"

#define KERNEL_ABORT_SOS 100000


void
kernel_sleep(uint32_t duration)
{
    uint32_t end_clock = kernel_arm_timer_clock() + duration;

    while (kernel_arm_timer_clock() < end_clock);
}

void
kernel_panic()
{
    for ( ; ; )
    {
        led_on();
        kernel_sleep(KERNEL_ABORT_SOS);

        led_off();
        kernel_sleep(1000000 - KERNEL_ABORT_SOS);
    }

    __builtin_unreachable();
}
