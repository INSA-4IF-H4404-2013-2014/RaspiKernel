#include "os/api_process.h"

int param1 = 3;
int param2 = 1; 
int param3 = 7;

static void
sub_process(int * top)
{
	int i;
	for ( i = 0 ; i < *top ; i++) 
    {
        process_yield();
    }
}

static void immortal()
{
    while(1)
    {
        process_yield();
    }
}


void
main_process(void)
{
    uint32_t PID1 = process_create((process_func_t) sub_process, &param1);
    uint32_t PID2 = process_create((process_func_t) immortal, &param2);
    uint32_t PID3 = process_create((process_func_t) sub_process, &param3);
    //ignore parameter
    uint32_t PID4 = process_create((process_func_t) immortal, &param3);


    process_set_collabo(PID1);
    process_set_collabo(PID2);
    process_set_collabo(PID3);
    process_set_collabo(PID4);

	
    process_start(PID1);
    process_start(PID3);
    process_start(PID2);
    process_start(PID4);

}

