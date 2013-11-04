
#include "kernel_process.h"
#include "hw.h"


void
main_process(void);

int
kernel_main(void)
{
    // create kernel process
    process_create((process_func_t)0, (void *)0);

    // create the main process
    uint32_t main_process_PID = process_create((process_func_t) main_process, 0);
    process_start(main_process_PID);

    init_hw();

    ENABLE_IRQ();

    while ( 1 )
    {
        //process_yield();
    }

    return 0;
}
