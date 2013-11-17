
#include "os/api_process.h"
#include "os/api_led.h"
#include "os/kernel_fat_bpb.h"


extern uint8_t fat32_content[];


static kernel_fat_bpb_t BPB;


void
main_process(void)
{
    kernel_fat_bpb_init(&BPB, fat32_content);

    for ( ; ; )
    {
        led_on();
        process_sleep(process_get_pid(), 100000);

        led_off();
        process_sleep(process_get_pid(), 100000);
    }
}
