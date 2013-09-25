/*
 * (C) Copyright 2002-2006
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 *
 * (C) Copyright 2002
 * Sysgo Real-Time Solutions, GmbH <www.elinos.com>
 * Marius Groeger <mgroeger@sysgo.de>
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

/*
 * To match the U-Boot user interface on ARM platforms to the U-Boot
 * standard (as on PPC platforms), some messages with debug character
 * are removed from the default U-Boot build.
 *
 * Define DEBUG here if you want additional info as shown below
 * printed upon startup:
 *
 * U-Boot code: 00F00000 -> 00F3C774 BSS: -> 00FC3274
 * IRQ Stack: 00ebff7c
 * FIQ Stack: 00ebef7c
 */

#include <common.h>
#include <asm/io.h>
#include <c3.h>
#ifdef CONFIG_RAM_TEST
#include "test_mem.h"
#endif

#ifdef CONFIG_TIMER_MEASURE
extern void reset_timer(void);
extern void show_timer(char *s);
#define RESET_TIMER reset_timer()
#define SHOW_TIMER(s) show_timer(s)
#else
#define RESET_TIMER
#define SHOW_TIMER(s)
#endif

#ifdef CONFIG_DDR_ECC_ENABLE
#define ECC_MASK	(3<<8)
#define NO_ECC		(0<<8)
#define ECC_REPORT_ON	(1<<8)
#define ECC_CORR_ON	(3<<8)

s32
memset_long(u32 *addr, u32 val, u32 size)
{
	u32 i;
	for (i = 0; i < (size/4); i++)
		*(addr + i) = val;
	return 0;
}

void mpmc_config_ecc(u32 value)
{
	u32 *mpmc_reg_p = (u32 *)CONFIG_SPEAR_MPMCBASE;
	writel((readl(&mpmc_reg_p[18]) & (~ECC_MASK)) | (value),
						&mpmc_reg_p[18]);
	while ((readl(&mpmc_reg_p[18]) & ECC_MASK) != value)
		;
}
#endif

extern void __armv7_mmu_cache_on(void);
extern void __v7_flush_dcache_all(void);
extern void __disable_dcache(void);
extern void __disable_mmu(void);

ulong start_armboot(void)
{
#ifdef CONFIG_DDR_ECC_ENABLE
	void *end = (void *)get_ram_size(0x00, PHYS_SDRAM_MAXSIZE);
#if defined(CONFIG_C3_DEVICE) && CONFIG_C3_DDR_INIT
	void *c3sram = (void *)C3_INT_MEM_BASE_ADDR;
	RESET_TIMER;
	c3_init();
	mpmc_config_ecc(ECC_CORR_ON);
#ifdef DEBUG_TRACK_DDR_INIT
	uartDebug_Puts("mpmc_config_ecc: OK\r\n");
#endif
	c3_memset(c3sram, end, 0);
	SHOW_TIMER("c3_init_ddr");
#ifdef DEBUG_TRACK_DDR_INIT
	uartDebug_Puts("DDR c3_memset 0: OK\r\n");
#endif
#ifdef CONFIG_RAM_TEST
	/* re-do the test ddr to check ECC connections */
	RESET_TIMER;
	test_ddr(TEST_DDR_WITH_ECC);
	SHOW_TIMER("test_ddr_w_ecc");
#ifdef DEBUG_TRACK_DDR_INIT
	uartDebug_Puts("test_ddr w ECC: OK\r\n");
#endif
#endif
#else
	__armv7_mmu_cache_on();
	memset_long((u32 *)(0x00), 0, 96); /*intializing 96 bytes, 24 words*/
	mpmc_config_ecc(ECC_CORR_ON);
	asm("dmb"); /* data memory barrier */
	asm("dsb"); /* data synch barrier*/
	asm("isb"); /* isntn synch barrier*/
	memset_long((u32 *)(0x00), 0, (u32)end); /* Initializing DDR*/
	__v7_flush_dcache_all();
	__disable_dcache();
	__disable_mmu();
#endif
#endif
	return boot();
}

void hang(void)
{
	for (;;);
}
