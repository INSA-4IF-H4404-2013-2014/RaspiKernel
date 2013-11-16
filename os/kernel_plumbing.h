#ifndef _H_KERNEL_PLUMBING
#define _H_KERNEL_PLUMBING

#include "standart.h"


/*
 * @infos: actif sleep
 *
 * @param <duration>: sleep duration in micro seconds
 */
void
kernel_sleep(uint32_t duration);

/*
 * @infos: emit SOS by the green led indefinitly
 */
void __attribute__((naked, noreturn))
kernel_panic();


#endif
