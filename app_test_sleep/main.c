
#include "os/api_process.h"
#include "os/hw.h"


void
main_process(void)
{
    for ( ; ; )
    {
        led_on();
        process_sleep(process_get_pid(), 100000);

        led_off();
        process_sleep(process_get_pid(), 100000);
    }
}
