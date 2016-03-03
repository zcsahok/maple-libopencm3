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

#ifndef UART_H
#define UART_H

/** Size of the circular receive buffer */
#ifndef UART_RX_BUFFER_SIZE
#define UART_RX_BUFFER_SIZE 8
#endif

/** Transmit chunk size */
#ifndef UART_TX_SIZE
#define UART_TX_SIZE        30
#endif

void uart_init(void);

/**
 *  @brief   Get received byte from receive buffer
 *
 *  Blocks if buffer is empty
 *
 *  @param   void
 *  @return  received byte
 */
char uart_getc(void);

/**
 *  @brief   Send a byte
 *  @param   byte to be transmitted
 *  @return  none
 */
void uart_putc(unsigned char data);

/**
 *  @brief   Send a null-terminated string
 *
 *  Blocks until the whole string is sent.
 * 
 *  @param   s string to be transmitted
 *  @return  none
 */
void uart_puts(const char *s);

/**
 *  @brief   Send n bytes from buffer
 *
 *  Blocks until the whole buffer is sent.
 * 
 *  @param   buffer data to be transmitted
 *  @param   n number of bytes in the buffer
 *  @return  none
 */
void uart_send(const char *buffer, int n);

/**
 *  @brief   Return number of bytes waiting in the receive buffer
 *  @param   none
 *  @return  bytes waiting in the receive buffer
 */
int uart_available(void);

/**
 *  @brief   Clean bytes waiting in receive buffer
 *  @param   none
 *  @return  none
 */
void uart_clean(void);

/**
 *  @brief   Print a number in given base and length
 *  @param   value number to be printed
 *  @param   base 2..16
 *  @param   length field width (the number is right aligned)
 *  @return  none
 */
void uart_print_n(int value, int base, int length);

/**
 *  @brief   Print a decimal number
 *  @param   value number to be printed
 *  @return  none
 */
void uart_print_d(int value);

/**
 *  @brief   Print a hexadecimal number
 *  @param   value number to be printed
 *  @return  none
 */
void uart_print_x(int value);


#endif                          // UART_H
