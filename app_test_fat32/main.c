
#include "os/api_process.h"
#include "os/api_led.h"


extern uint32_t fat32_content[];

void
main_process(void)
{
    if (((char*)fat32_content)[0] == 0xEB)
    {
        led_on();
    }

    for ( ; ; )
    {
        led_on();
        process_sleep(process_get_pid(), 100000);

        led_off();
        process_sleep(process_get_pid(), 100000);
    }
}
