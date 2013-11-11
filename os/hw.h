#ifndef HW_H
#define HW_H

void enable_timer_irq();
void disable_timer_irq();
void set_next_tick_and_enable_timer_irq();

void led_off();
void led_on();

void init_hw();

#endif
