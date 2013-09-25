/*
 * (C) Copyright 2000-2009
 * Vipin Kumar, ST Microelectronics, vipin.kumar@st.com
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#ifndef __COMMON_H_
#define __COMMON_H_	1

typedef unsigned char		uchar;

#include <config.h>
#include <linux/types.h>
#include <linux/string.h>

#ifdef CONFIG_ARM
#define asmlinkage	/* nothing */
#endif

#include <image.h>

/*
 * General Purpose Utilities
 */
#define min(X, Y)				\
	({ typeof (X) __x = (X), __y = (Y);	\
		(__x < __y) ? __x : __y; })

#define max(X, Y)				\
	({ typeof (X) __x = (X), __y = (Y);	\
		(__x > __y) ? __x : __y; })

#define MIN(x, y)  min(x, y)
#define MAX(x, y)  max(x, y)

typedef void (*funcp)(void) __attribute__ ((noreturn));

/* common/memsize.c */
long    get_ram_size  (volatile long *, long);
unsigned get_expected_mem_size(void);

/*
 * Function Prototypes
 */
int	    cleanup_caches(void);
int	    disable_interrupts(void);
void	dcache_disable(void);
void	icache_disable(void);
void	hang		(void) __attribute__ ((noreturn));
u32	    boot		(void);
void	boot_kernel	(funcp image) __attribute__ ((noreturn));
void	reset_cpu	(ulong ignored) __attribute__ ((noreturn));
int     test_ddr(int test_with_ecc);

void spear_serial_init(void);
#if defined(CONFIG_SPEAR3XX) || defined(CONFIG_SPEAR13XX)
void uartDebug_InstallNs16550(unsigned baseAddr);
void uartDebug_InstallPl01x(void);
void uartDebug_Init (void);
void uartDebug_Putc (char TxChar);
void uartDebug_Puts (char *TxString);
void uartDebug_Puthex (unsigned TxVal);
void uartDebug_Putdec (unsigned int number);
#else
void serial_puts(const char *);
#endif

/*
 * plat/xxx/xxx definitions
 */
int snor_boot_selected(void);
int nand_boot_selected(void);
int pnor_boot_selected(void);
int usb_boot_selected(void);
int uart_boot_selected(void);
int tftp_boot_selected(void);
int i2c_boot_selected(void);
int spi_boot_selected(void);
int mmc_boot_selected(void);

void plat_late_init(void);

#endif	/* __COMMON_H_ */
