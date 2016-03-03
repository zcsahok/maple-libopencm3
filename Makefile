##
## Copyright (C) 2009 Uwe Hermann <uwe@hermann-uwe.de>
#* Copyright (C) 2016 Zoltán Csahók
##
## This library is free software: you can redistribute it and/or modify
## it under the terms of the GNU Lesser General Public License as published by
## the Free Software Foundation, either version 3 of the License, or
## (at your option) any later version.
##
## This library is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU Lesser General Public License for more details.
##
## You should have received a copy of the GNU Lesser General Public License
## along with this library.  If not, see <http://www.gnu.org/licenses/>.
##

BINARY = main

OBJS = cdcacm.o uart.o 

OPENCM3_DIR = libopencm3
LDSCRIPT = stm32-maple.ld

include libopencm3.target.mk

#=======================================
#
# rules to build libopencm3 library
#
LIB_A = $(OPENCM3_DIR)/lib/lib$(LIBNAME).a
lib: $(LIB_A)
$(OBJS): $(LIB_A)
$(LIB_A):
	make -C $(OPENCM3_DIR) lib/stm32/f1
#=======================================

all: $(BINARY).bin

$(BINARY).bin: $(BINARY).elf
	@arm-none-eabi-size $<
	@arm-none-eabi-objcopy -v -Obinary $< $@
	@dfu-suffix -a $@ >/dev/null

burn: $(BINARY).bin
	@dfu-util -a 1 -d 1EAF:0003 -D $< -R
	
