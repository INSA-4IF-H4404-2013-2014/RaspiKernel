
#include "api_led.h"
#include "kernel_arm.h"


#define GPFSEL1 0x20200004
#define GPSET0  0x2020001C
#define GPCLR0  0x20200028


void
led_off()
{
    kernel_arm_addr32(GPSET0) = 1 << 16;
}

void
led_on()
{
    kernel_arm_addr32(GPCLR0) = 1 << 16;
}

/*
 * @infos: init led. Only called by kernel_main
 */
void
kernel_led_init()
{
    uint32_t ra;

    ra = kernel_arm_addr32(GPFSEL1);
    ra &= ~(7 << 18);
    ra |= 1 << 18;
    kernel_arm_addr32(GPFSEL1) = ra;

    led_off();
}
