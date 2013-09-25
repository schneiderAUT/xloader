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

#include <common.h>

#if defined(CONFIG_SPEAR3XX) && \
	(CONFIG_DDR_MT47H64M16) && \
	(CONFIG_DDR_HCLK)

const u32 mpmc_conf_vals[CONFIG_SPEAR_MPMCREGS] = {
	0x00000001,
	0x00000000,
	0x01000000,
	0x00000101,
#ifdef EIGHT_BANK_MODE
	0x00000101,
#else
	0x00000001,
#endif
	0x01000000,
	0x00010001,
	0x00000100,
	0x00010001,
#if CONFIG_DUAL_DDR
	0x01020003,
	0x01000102,
	0x04000202,
#else
	0x00000001,
	0x02000001,
	0x04000201,
#endif
	0x03030104,
	0x03020202,
	0x01040000,
	0x00000001,
	0x00000000,
	0x03000404,
	0x02020002,
	0x03000203,
	0x0505053f,
	0x05050505,
	0x04040405,
	0x04040404,
	0x03030304,
	0x03030303,
	0x02020203,
	0x02020202,
	0x01010102,
	0x01010101,
	0x00000001,
	0x00000000,
	0x00000000,
	0x00000000,
	0x07080a00,
	0x0000023f,
	0x00030600,
	0x09000000,
	0x00000a02,
	0x00001e1e,
	0x7F000000,
	0x005F0000,
	0x16030700,
	0x00640064,
	0x00640064,
	0x00000064,
	0x00000000,
	0x00200020,
	0x00200020,
	0x00200020,
	0x00200020,
	0x00200020,
	0x00000000,
	0x00000000,
	0x0000050e,
	0x00000000,
	0x2d8900c8,
	0x00c80017,
	0x00000000,
	0x00008236,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x003a0000,
	0x00010000,
	0x00200000,
	0x003c00f4,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x01010001,
	0x01000000,
	0x00000001,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00430000,
	0x00000002
};
#endif
