#include "os/api_process.h"
#include "os/api_sync_sem.h"
#include "music.h"


void main_process(void)
{
	music_init();
    uint32_t PID = process_create((process_func_t) play_music, 0);

    process_start(PID);
}
