#include "os/api_process.h"
#include "os/api_sync_sem.h"
#include "music.h"

void play_music_test()
{
    // Test
	play_music();
}

void main_process(void)
{
	music_init();
    uint32_t PID = process_create((process_func_t) play_music_test, 0);

    process_start(PID);
}

