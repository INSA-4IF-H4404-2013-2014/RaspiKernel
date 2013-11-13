#include "os/api_process.h"

static void
sub_process(int * top)
{
	int i;
	//the last process have to run forever because kernel doesn t know how to kill him
	if(*top <= 0)
	{
		for ( ; ; );
	}
	else
	{
		for ( i = 0 ; i < *top ; i++);
	}
}


void
main_process(void)
{
				int param1 = 3;
				int param2 = 0; 
				int param3 = 7;
				int i=0;

				uint32_t PID1 = process_create((process_func_t) sub_process, &param1);
				uint32_t PID2 = process_create((process_func_t) sub_process, &param2);
				uint32_t PID3 = process_create((process_func_t) sub_process, &param3);
    
				process_set_collabo(PID1);
				process_set_collabo(PID2);
				process_set_collabo(PID3);

	
    process_start(PID1);
				process_start(PID3);
				process_start(PID2);
				//last is void
				process_start(0);
    
    i++;
    
}

