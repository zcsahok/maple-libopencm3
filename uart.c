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
#include "cdcacm.h"

char rxbuf[UART_RX_BUFFER_SIZE];
volatile int start;
volatile int end;
volatile int size;

int uart_available(void)
{
    return size;
}

void uart_receive(const char *buf, int len)
{
    while (len > 0 && size < UART_RX_BUFFER_SIZE) {
        rxbuf[end] = *buf;
        ++buf;
        --len;
        end = (end + 1) % (UART_RX_BUFFER_SIZE - 1);
        ++size;
    }
}

char uart_getc(void)
{
    while (size == 0);          // wait for data
    char c = rxbuf[start];
    DISABLE_INTERRUPTS;
    start = (start + 1) % (UART_RX_BUFFER_SIZE - 1);
    --size;
    ENABLE_INTERRUPTS;
    return c;
}

void uart_send(const char *buffer, int n)
{
    if (n <= 0) {
        return;
    }
    // retry until it succeeds
    while (0 == usbd_ep_write_packet(cdcacm_usbd_dev, 0x82, buffer, n));
}

void uart_putc(unsigned char c)
{
    uart_send((const char *) &c, 1);
}

void uart_puts(const char *s)
{
    const char *p = s;
    while (1) {
        if (p == s + UART_TX_SIZE || *p == 0) {
            uart_send(s, p - s);
            if (*p == 0) {
                return;
            }
            s = p;
        }
        p++;
    }
}

void uart_clean(void)
{
    start = end = size = 0;
}

void uart_init(void)
{
    uart_clean();
    cdcacm_init();
}

void uart_print_n(int value, int base, int length)
{
#define BUFSZ 32                // 32 for signed int32 (worst case: negative and base 2)
    char buf[BUFSZ];
    char *p = buf;
    if (value == 0) {
        *p++ = '0';
    } else {
        char sign = 0;
        if (value < 0) {
            sign = '-';
            value = -value;
        }
        while (value > 0) {
            *p++ = "0123456789ABCDEF"[value % base];
            value /= base;
        }
        if (sign) {
            *p++ = sign;
        }
    }

    if (length > BUFSZ) {
        length = BUFSZ;
    }
    // append leading blanks
    while (p < buf + length) {
        *p++ = ' ';
    }

    // reverse buf
    int bufsz = p - buf;
    int i;
    for (i = 0; i < bufsz / 2; ++i) {
        char tmp = buf[i];
        buf[i] = buf[bufsz - 1 - i];
        buf[bufsz - 1 - i] = tmp;

    }
    uart_send(buf, bufsz);
}


void uart_print_d(int value)
{
    uart_print_n(value, 10, 0);
}

void uart_print_x(int value)
{
    uart_print_n(value, 16, 0);
}
