#ifndef _H_KERNEL_PLUMBING
#define _H_KERNEL_PLUMBING

#include "standard.h"
#include <stdint.h>


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
#define KERNEL_SOS_DURATION_ON 100000
#define KERNEL_SOS_DURATION_OFF 1000000

#define KERNEL_USER_SOS_DURATION_ON 1000000
#define KERNEL_USER_SOS_DURATION_OFF 1500000

#define kernel_panic() \
	kernel_plumbing_panic(KERNEL_SOS_DURATION_ON, KERNEL_SOS_DURATION_OFF)

#define kernel_user_panic() \
	kernel_plumbing_panic(KERNEL_USER_SOS_DURATION_ON, KERNEL_USER_SOS_DURATION_OFF)

void __attribute__((noreturn))
kernel_plumbing_panic(uint32_t on_duration, uint32_t off_duration);


#endif
