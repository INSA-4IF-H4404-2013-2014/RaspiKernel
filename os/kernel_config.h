#ifndef _H_KERNEL_CONFIG
#define _H_KERNEL_CONFIG

/*
 * @infos; defines the default CPU frequency (Hz)
 */
#define KERNEL_CPU_FREQUENCY 700000000

/*
 * @infos: set the default frequency divisor
 *
 * @asssert
 *  - KERNEL_TIMER_FREQUENCY_DIVISOR < 1024
 */
#define KERNEL_TIMER_FREQUENCY_DIVISOR 70

/*
 * @infos: defines the standart PCB stack size
 */
#define KERNEL_STACK_SIZE \
    (1024 * 32)

/*
 * @infos: defines the number of round robin priority levels
 *
 * @domain: must be strictly positive
 */
#define KERNEL_RR_LEVELS 8

#if KERNEL_RR_LEVELS <= 0
#error "KERNEL_RR_LEVELS must be positive."
#endif

/*
 * @infos: defines the scheduler's timer slot
 */
#define KERNEL_SCHEDULER_TIMER_SLOT 1

/*
 * @infos: defines the scheduler interupt periode
 *
 * @note:
 *  - depond on CPU frequency and timer frequency divisor
 */
#define KERNEL_SCHEDULER_TIMER_PERIODE 1000000


#endif
