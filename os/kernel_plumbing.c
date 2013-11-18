
#include "kernel_plumbing.h"
#include "kernel_arm_timer.h"
#include "api_led.h"



void
kernel_sleep(uint32_t duration)
{
    uint32_t end_clock = kernel_arm_timer_clock() + duration;

    while (kernel_arm_timer_clock() < end_clock);
}

void
kernel_plumbing_panic(uint32_t on_duration, uint32_t off_duration)
{
    for ( ; ; )
    {
        led_on();
        kernel_sleep(on_duration);

        led_off();
        kernel_sleep(off_duration);
    }

    __builtin_unreachable();
}
