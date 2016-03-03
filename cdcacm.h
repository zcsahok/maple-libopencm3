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

#ifndef CDCACM_H
#define CDCACM_H

#include <libopencm3/usb/usbd.h>
#include <libopencm3/cm3/nvic.h>

#define ENABLE_INTERRUPTS   nvic_enable_irq(NVIC_USB_LP_CAN_RX0_IRQ)
#define DISABLE_INTERRUPTS  nvic_disable_irq(NVIC_USB_LP_CAN_RX0_IRQ)

extern usbd_device *cdcacm_usbd_dev;

void uart_receive(const char *buf,int len);

void cdcacm_init(void);

#endif

