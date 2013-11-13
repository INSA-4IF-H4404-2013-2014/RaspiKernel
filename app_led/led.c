#include "../os/hw.h"
#include "../os/api_process.h"
#include "led.h"

void led_on_process ()
{
		for ( ; ; )
		{
			//led_on();
		}
}

void led_off_process ()
{
		for ( ; ; )
		{
			//led_off();
		}
}

void launch_led_process()
{
	uint32_t PID_ON = process_create((process_func_t) led_on_process, 0);
	uint32_t PID_OFF = process_create((process_func_t) led_off_process, 0);
	
	process_start(PID_ON);
	process_start(PID_OFF);
}
