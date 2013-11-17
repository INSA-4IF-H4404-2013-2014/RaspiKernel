
#include "os/api_process.h"
#include "os/api_led.h"
#include "os/api_directory.h"


extern uint8_t fat32_content[];


void
main_process(void)
{
    directory_mount_fat_mem(fat32_content);

    directory_exists("/hello.txt");

    for ( ; ; )
    {
        led_on();
        process_sleep(process_get_pid(), 100000);

        led_off();
        process_sleep(process_get_pid(), 100000);
    }
}
