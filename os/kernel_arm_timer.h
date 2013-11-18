#ifndef _H_KERNEL_ARM_TIMER
#define _H_KERNEL_ARM_TIMER

#include "kernel_arm.h"

// doc1 : doc_arm_peripherals.pdf

//------------------------------------------------------------------------------ CONSTANTS

#define KERNEL_ARM_TIMER_CS 0x20003000  // System Timer Control/Status (doc1:p172)
#define KERNEL_ARM_TIMER_CL0 0x20003004 // System Timer Counter Lower 32 bits (doc1:p172)
#define KERNEL_ARM_TIMER_C0 0x2000300C  // System Timer Compare 0
#define KERNEL_ARM_TIMER_C1 0x20003010  // System Timer Compare 1
#define KERNEL_ARM_TIMER_C2 0x20003014  // System Timer Compare 2
#define KERNEL_ARM_TIMER_C3 0x20003018  // System Timer Compare 3
#define KERNEL_ARM_TIMER_PREDIVISOR 0x2000B41C // Pre-divider (doc1:p196)


//------------------------------------------------------------------------------ MACROS

/*
 * @infos: enable timer interupt <i>
 *
 * @param <i>: timer id
 *
 * @assert:
 *  - 0 <= i < 4
 */
#define kernel_arm_timer_enable(i) \
    kernel_arm_addr32(KERNEL_ARM_TIMER_CS) |= (1 << (i))

/*
 * @infos: disable timer interupt <i>
 *
 * @param <i>: timer id
 *
 * @assert:
 *  - 0 <= i < 4
 */
#define kernel_arm_timer_disable(i) \
    kernel_arm_addr32(KERNEL_ARM_TIMER_CS) &= ~(1 << (i))

/*
 * @infos: set global timer frequency divisor
 *
 * @param <divisor>: frequency divisor
 *
 * @doc:
 *  - timer_clock = apb_clock/(pre_divider+1)
 *  - at reset, pre_divider = 125
 */
#define kernel_arm_timer_frequency_divisor(divisor) \
    kernel_arm_addr32(KERNEL_ARM_TIMER_PREDIVISOR) = (divisor) - 1

/*
 * @infos: get the timer clock
 *
 * @return:
 *  - the number of upper front
 */
#define kernel_arm_timer_clock() \
    kernel_arm_addr32(KERNEL_ARM_TIMER_CL0)

/*
 * @infos: get access on the triger front number for interupt <i>
 *
 * @param <i>: timer id
 *
 * @return
 *  - front id of the timer <i>
 *
 * @assert:
 *  - 0 <= i < 4
 */
#define kernel_arm_timer_slot(i) \
    kernel_arm_array32(KERNEL_ARM_TIMER_C0,i)

/*
 * @infos: init timer
 */
void
kernel_arm_timer_init();


#endif
