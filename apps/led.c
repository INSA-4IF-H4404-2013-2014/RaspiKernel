#include "../os/hw.h"
#include "led.h"

void led_process ( led_state ledState )
{
	if ( ledState == LED_ON )
	{
		for ( ; ; )
		{
			led_on();
		}
	}
	else if ( ledState == LED_OFF )
	{
		for ( ; ; )
		{
			led_off();
		}
	}
}
