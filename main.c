/* maple-libopencm3 - demo project
 * Copyright (C) 2016 Zoltán Csahók
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include "uart.h"

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/cm3/systick.h>


int led_timer;

/* called every 1 ms */
void sys_tick_handler(void)
{
    if (led_timer) {
        if (led_timer == 1) {
            gpio_clear(GPIOA, GPIO5);   /* LED off */
        }
        --led_timer;
    }
}



int main(void)
{
    uart_init();


    led_timer = 0;

    /* 72 MHz / 8 => 9000000 counts per second */
    systick_set_clocksource(STK_CSR_CLKSOURCE_AHB_DIV8);

    /* 9000000/9000 = 1000 overflows per second - every 1ms one interrupt */
    /* SysTick interrupt every N clock pulses: set reload to N-1 */
    systick_set_reload(8999);

    systick_interrupt_enable();
    systick_counter_enable();


    while (1) {
        while (uart_available()) {
            gpio_set(GPIOA, GPIO5);     /* LED on */
            led_timer = 1000;
            char c = uart_getc();
            if (c == 'x') {
                uart_puts("hello\r\n");
            } else if (c == 'n') {
                uart_print_d(1234);
            } else if (c == 'h') {
                uart_print_n(0x12fa8, 16, 9);
            } else {
                uart_putc(c);
            }
        }
    }

    return 0;
}
