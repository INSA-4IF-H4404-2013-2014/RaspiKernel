
#include "os/api_process.h"


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

    process_start(PID);

    process_pause(process_get_pid());

    for ( ; ; )
    {
        i += 3;
    }
}

