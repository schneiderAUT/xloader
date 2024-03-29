/*
 * (C) Copyright 2000
 * Rob Taylor, Flying Pig Systems. robt@flyingpig.com.
 *
 * (C) Copyright 2004
 * ARM Ltd.
 * Philippe Robin, <philippe.robin@arm.com>
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

/* Simple U-Boot driver for the PrimeCell PL010/PL011 UARTs */

#include <common.h>

#include "serial_pl01x.h"

#define IO_WRITE(addr, val) (*(volatile unsigned int *)(addr) = (val))
#define IO_READ(addr) (*(volatile unsigned int *)(addr))

/*
 * Integrator AP has two UARTs, we use the first one, at 38400-8-N-1
 * Integrator CP has two UARTs, use the first one, at 38400-8-N-1
 * Versatile PB has four UARTs.
 */
#define CONSOLE_PORT CONFIG_CONS_INDEX
#define baudRate CONFIG_BAUDRATE
static volatile unsigned char *const port[] = CONFIG_PL01x_PORTS;

void serial_pl01x_init (void)
{
	unsigned int temp;
	unsigned int divider;
	unsigned int remainder;
	unsigned int fraction;

	/*
	 ** First, disable everything.
	 */
	IO_WRITE (port[CONSOLE_PORT] + UART_PL011_CR, 0x0);

	/*
	 ** Set baud rate
	 **
	 ** IBRD = UART_CLK / (16 * BAUD_RATE)
	 ** FBRD = ROUND((64 * MOD(UART_CLK,(16 * BAUD_RATE))) / (16 * BAUD_RATE))
	 */
	temp = 16 * baudRate;
	divider = CONFIG_PL011_CLOCK / temp;
	remainder = CONFIG_PL011_CLOCK % temp;
	temp = (8 * remainder) / baudRate;
	fraction = (temp >> 1) + (temp & 1);

	IO_WRITE (port[CONSOLE_PORT] + UART_PL011_IBRD, divider);
	IO_WRITE (port[CONSOLE_PORT] + UART_PL011_FBRD, fraction);

	/*
	 ** Set the UART to be 8 bits, 1 stop bit, no parity, fifo enabled.
	 */
	IO_WRITE (port[CONSOLE_PORT] + UART_PL011_LCRH,
		  (UART_PL011_LCRH_WLEN_8 | UART_PL011_LCRH_FEN));

	/*
	 ** Finally, enable the UART
	 */
	IO_WRITE (port[CONSOLE_PORT] + UART_PL011_CR,
		  (UART_PL011_CR_UARTEN | UART_PL011_CR_TXE |
		   UART_PL011_CR_RXE));

}

static void pl01x_putc(int portnum, char c)
{
	/* Wait until there is space in the FIFO */
	while (IO_READ(port[portnum] + UART_PL01x_FR) & UART_PL01x_FR_TXFF)
		;

	/* Send the character */
	IO_WRITE(port[portnum] + UART_PL01x_DR, c);
}

void serial_putc(const char c)
{
	if (c == '\n')
		pl01x_putc(CONSOLE_PORT, '\r');

	pl01x_putc(CONSOLE_PORT, c);
}

void serial_puts(const char *s)
{
	while (*s)
		serial_putc(*s++);
}
