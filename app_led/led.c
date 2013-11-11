#include "../os/hw.h"
#include "../os/api_process.h"
#include "led.h"

void led_process ( led_state * ledState )
{
	if ( *ledState == LED_ON )
	{
		for ( ; ; )
		{
			//led_on();
		}
	}
	else if ( *ledState == LED_OFF )
	{
		for ( ; ; )
		{
			//led_off();
		}
	}
}

void launch_led_process()
{
	int i = LED_ON;
	int j = LED_OFF;

	uint32_t PID_ON = process_create((process_func_t) led_process, (void *) &i);
	uint32_t PID_OFF = process_create((process_func_t) led_process, (void *) &j);
	
	process_start(PID_ON);
	process_start(PID_OFF);
	
}
