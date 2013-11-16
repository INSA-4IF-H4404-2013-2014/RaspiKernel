#include "os/api_process.h"

int param1 = 2;
int param2 = 1; 
int param3 = 3;
int param4 = 3;

static void
sub_process(int * top)
{
	int i;
	for ( i = 0 ; i < *top ; i++) 
    {
        process_yield();
    }
}

/*
expected at process_yield() => b api_process.c:146
p kernel_running_pcb->mPID

0 (main) 1time
PID2 1time
PID1 3times
PID3 and PID4 alternated 7 times
*/
void
main_process(void)
{
    uint32_t PID1 = process_create((process_func_t) sub_process, &param1);
    uint32_t PID2 = process_create((process_func_t) sub_process, &param2);
    uint32_t PID3 = process_create((process_func_t) sub_process, &param3);
    uint32_t PID4 = process_create((process_func_t) sub_process, &param3);

    uint32_t prio1 = 1;
    uint32_t prio3 = 0;
    uint32_t prio4 = 0;

    process_set_rr_priority(PID1, prio1);
    process_set_collabo(PID2);
    process_set_rr_priority(PID3, prio3);
    process_set_rr_priority(PID4, prio4);

	process_start(PID3);
    process_start(PID4);
    process_start(PID1);
    process_start(PID2);
    
    while(1)process_yield(); //one process must stay alive forever
}

