#ifndef _H_KERNEL_CONFIG
#define _H_KERNEL_CONFIG

/*
 * @infos: defines the total kernel heap size
 */
#define KERNEL_HEAP_SIZE \
    (256 * 1024 * 1024)


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


#endif
