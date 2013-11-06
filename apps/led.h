#ifndef _H_LED
#define _H_LED

typedef enum { LED_OFF, LED_ON } led_state;


/*
 * @infos : start a LED process
 *
 * @param <pid> : the led state (on or off).
 *
 * @return
 *  VOID
 */
void led_process ( led_state ledState );

#endif
