
#include "os/kernel_process.h"
#include "music/music.h"


static void
sub_process(uint32_t * p_i)
{
    uint32_t i = *p_i;

    for ( ; ; )
    {
        i += 2;
    }
}

void
main_process(void)
{
    uint32_t i = 33;
    uint32_t j = 10;

    uint32_t PID = process_create((process_func_t) sub_process, &j);
    
    uint32_t PID_MUSIC = process_create((process_func_t) play_music, 0);

    process_start(PID);
    process_start(PID_MUSIC);

    for ( ; ; )
    {
        i += 3;
    }
}

