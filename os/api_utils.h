#ifndef _H_API_UTILS
#define _H_API_UTILS


/*
 * Enter in infite loop with blinking LED.
 * The LED will blink slowly, like a heart beat.
 * Use this util for user debug purpose.
 * i.e: Allows you to detect that your code reach a point
 * it shouldn't reach normally.
 */
void __attribute__((noreturn))
utils_user_panic();


#endif
