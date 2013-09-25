/*
 * (C) Copyright 2004
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
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
 *
 */

#include <config.h>
#ifdef __PPC__
/*
 * At least on G2 PowerPC cores, sequential accesses to non-existent
 * memory must be synchronized.
 */
# include <asm/io.h>	/* for sync() */
#else
# define sync()		/* nothing */
#endif
#ifdef CONFIG_SPEAR13XX
#include <../plat/common/spr_ras.h>
#endif
/*
 * Check memory range for valid RAM. A simple memory test determines
 * the actually available RAM size between addresses `base' and
 * `base + maxsize'.
 */
long get_ram_size(volatile long *base, long maxsize)
{
	volatile long *addr;
	long           save[32];
	long           cnt;
	long           val;
	long           size;
	int            i = 0;

	for (cnt = (maxsize / sizeof (long)) >> 1; cnt > 0; cnt >>= 1) {
		addr = base + cnt;	/* pointer arith! */
		sync ();
		save[i++] = *addr;
		sync ();
		*addr = ~cnt;
	}

	addr = base;
	sync ();
	save[i] = *addr;
	sync ();
	*addr = 0;

	sync ();
	if ((val = *addr) != 0) {
		/* Restore the original data before leaving the function.
		 */
		sync ();
		*addr = save[i];
		for (cnt = 1; cnt < maxsize / sizeof(long); cnt <<= 1) {
			addr  = base + cnt;
			sync ();
			*addr = save[--i];
		}
		return (0);
	}

	for (cnt = 1; cnt < maxsize / sizeof (long); cnt <<= 1) {
		addr = base + cnt;	/* pointer arith! */
		val = *addr;
		*addr = save[--i];
		if (val != ~cnt) {
			size = cnt * sizeof (long);
			/* Restore the original data before leaving the function.
			 */
			for (cnt <<= 1; cnt < maxsize / sizeof (long); cnt <<= 1) {
				addr  = base + cnt;
				*addr = save[--i];
			}
			return (size);
		}
	}

	return (maxsize);
}

unsigned get_expected_mem_size(void)
{
	unsigned size = 0;

#ifdef CONFIG_SPEAR1380_REVC

	struct rgpio2_regs *const rgpio2_p = (struct rgpio2_regs * const)CONFIG_RAS_RGPIO2_BASE;
	unsigned width = ((unsigned)(rgpio2_p->b_data_in) & (0x1 << 21)); // => ddr density

	if (((unsigned )(rgpio2_p->b_data_in)) & (0x1 << 22)) // RGPIO2B[22] <=> NFIO[13] => word width
		size = (2 * (128 << (width >> 21)) * 1024 * 1024); //word width = 32b
	else
		size = ((128 << (width >> 21)) * 1024 * 1024); //word width = 16b
#endif
#ifdef CONFIG_SPEAR320_MDI
	size = (64 * 1024 * 1024); //word width = 16b
#endif
	return size;
}
