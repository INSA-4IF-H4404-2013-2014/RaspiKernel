#include "hw.h"

// doc1 : doc_arm_peripherals.pdf

// Why not 0x7E003000 ? (doc1:p172)
#define CS 0x20003000  // System Timer Control/Status (doc1:p172)
#define CLO 0x20003004 // System Timer Counter Lower 32 bits (doc1:p172)
#define C0 0x2000300C  // System Timer Compare 0
#define C1 0x20003010  // System Timer Compare 1
#define C2 0x20003014  // System Timer Compare 2
#define C3 0x20003018  // System Timer Compare 3

#define GPFSEL1 0x20200004
#define GPSET0  0x2020001C
#define GPCLR0  0x20200028

// 0x218 Enable Basic IRQs



/*
 * (doc1:p114)
 * BIT  0 : ARM Timer IRQ pending
 */
#define INTERVAL 0x2000B200 // (doc1:p112)



extern void PUT32 ( unsigned int, unsigned int );
extern unsigned int GET32 ( unsigned int );

/*
 * Timer interrupts
 */
void
enable_timer_irq()
{
  /* Enable timer interrupt */
  PUT32(CS,2);
}

void
disable_timer_irq()
{
  /* Disable timer interrupt */
  PUT32(CS,~2);
}


void
set_next_tick_and_enable_timer_irq()
{
  unsigned int rx = GET32(CLO);
  rx += INTERVAL;
  PUT32(C1,rx);

  enable_timer_irq();
}


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
    unsigned int ra;
    unsigned int rx;

    /* Make gpio pin tied to the led an output */
    ra=GET32(GPFSEL1);
    ra&=~(7<<18);
    ra|=1<<18;
    PUT32(GPFSEL1,ra);
    PUT32(GPSET0,1<<16); //led off

    /* Set up delay before timer interrupt (we use CM1) */
    rx=GET32(CLO);
    rx += INTERVAL;
    PUT32(C1,rx);

    /* Enable irq triggering by the *system timer* peripheral */
    /*   - we use the compare module CM1 */
    enable_timer_irq();

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
    PUT32(0x2000B210, 0x00000002); // why not 0x7E00B000 ?
}
