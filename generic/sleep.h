#ifdef OS_RASP
	#include "../os/api_process.h"
	#define generic_sleep(duration) process_sleep(process_get_pid(), (1000000)*duration)
	#define generic_usleep(duration) process_sleep(process_get_pid(), duration)
#else
	#include <unistd.h>
	#define generic_sleep(duration) sleep(duration)
	#define generic_usleep(duration) usleep(duration)
#endif
