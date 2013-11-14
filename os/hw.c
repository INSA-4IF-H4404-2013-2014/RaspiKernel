#include "hw.h"
#include "kernel_arm.h"


// doc1 : doc_arm_peripherals.pdf

#define GPFSEL1 0x20200004
#define GPSET0  0x2020001C
#define GPCLR0  0x20200028

extern void PUT32 ( unsigned int, unsigned int );
extern unsigned int GET32 ( unsigned int );


/*
 * LEDs on/off
 */

void
led_off()
{
  PUT32(GPSET0,1<<16); //led off
}

void
led_on()
{
  PUT32(GPCLR0,1<<16); //led on
}

/*
 * Start_hw
 */
void
init_hw()
{
    //unsigned int ra;
    unsigned int ra;

    /* Make gpio pin tied to the led an output */
    ra = GET32(GPFSEL1);
    ra&=~(7<<18);
    ra|=1<<18;
    PUT32(GPFSEL1,ra);
    PUT32(GPSET0,1<<16);

    /* Enable interrupt *line* */
    /* (doc1:p116):
     * 0x2000B210 = Enable IRQs 1 (doc1:p116)
     * 0x2000B214 = Enable IRQs 2
     * 0x2000B218 = Enable Basics IRQs
     * 0x2000B21C = Disable IRQs 1
     * 0x2000B220 = Disable IRQs 2
     * 0x2000B224 = Disable Basics IRQs
     *
     * Diference betwen {Enable,Disable} IRGs 1 ??????????g
     */
    kernel_arm_addr32(0x2000B210) = 0x00000002;
}
