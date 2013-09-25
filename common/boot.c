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
#include <image.h>
#include <nand.h>

#define CONFIG_NAND_LAST_BLK (CONFIG_NAND_BOOT_BLK + \
				CONFIG_NAND_BOOT_BLKCNT)
#define CONFIG_NAND_OSLAST_BLK (CONFIG_NAND_OSBOOT_BLK + \
				CONFIG_NAND_OSBOOT_BLKCNT)

#if defined(CONFIG_OS_BOOT)
static void boot_os(void);
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

static void boot_image(funcp image) __attribute__ ((noreturn));

static int snor_image_load(u8 *, funcp *, const char *);
#ifndef SNOR_BOOT_ONLY //to save some space
static int nand_image_load(u32, u32, funcp *, const char *);
static int pnor_image_load(u8 *, u32, funcp *, const char *);
#endif //SNOR_BOOT_ONLY
static const char kernel_name[] = "Linux";
static const char loader_name_uboot[] = "U-Boot";
static const char loader_name_vxboot[] = "Vx-Boot";
const char * loader_name = NULL;

#define BOOT_SEL_UBOOT   0
#define BOOT_SEL_VXBOOT  1

#ifdef CONFIG_SPEAR320_MDI
#include "asm/arch/spr_misc.h"
#include "asm/arch/spr320_ras.h"
int getBootSel (void) {
	struct misc_regs *const miscReg =
	    (struct misc_regs *)CONFIG_SPEAR_MISCBASE;

	struct rasRegs *const rasReg =
	    (struct rasRegs *)CONFIG_SPEAR_RASBASE;

	unsigned int val;
	int ret;

	/* activate PD on pad 72,73,74,75 */
	miscReg->plgpio3_pad_prg |=  PLGPIO_72_TO_75_PD_DIS | PLGPIO_72_TO_75_PU_DIS;
	miscReg->plgpio3_pad_prg &= ~PLGPIO_72_TO_75_PD_DIS;

	/* gpio enable as input */
	SET_BIT(rasReg->gpioEn_64_95, PLGPIO_74_BITPOS);

	/* gpio selected */
	SET_BIT(rasReg->gpioSel_64_95, PLGPIO_74_BITPOS);

	/* read gpio */
	val = READ_BIT(rasReg->gpioIn_64_95, PLGPIO_74_BITPOS);

	if ( val == 0) {
		/* pin SPEAR_TEST_0 = PLGPIO74 == 1  => Vx-boot mode for dev for MDI*/
		ret = BOOT_SEL_VXBOOT;
	} else {
		/* pin SPEAR_TEST_0 = PLGPIO74 == 0  => U-boot mode for dev for MDI*/
		ret = BOOT_SEL_UBOOT;
	}
	return ret;
}

#endif /* CONFIG_SPEAR320_MDI */

#ifdef CONFIG_SPEAR1380_REVC
#include "asm/arch/spr13xx_defs.h"
int getBootSel (void) {
	int ret;
	if (getConfHwBootSel() == 0) {
		ret = BOOT_SEL_VXBOOT;
	} else {
		ret = BOOT_SEL_UBOOT;
	}
	return ret;
}

#endif /* CONFIG_SPEAR1380_REVC */

/*
 * boot:
 *
 * All supported booting types of all supported SoCs are listed here.
 * Generic readback APIs are provided for each supported booting type
 * eg. nand_read_skip_bad
 */
u32 boot(void)
{
	funcp image;

#ifdef CONFIG_SPEAR_USBTTY
	plat_late_init();
	return TRUE;
#endif

	/*
	 * All the supported booting devices are listed here. Each of
	 * the booting type supported by the platform would define the
	 * macro xxx_boot_supported to TRUE.
	 */

	if (snor_boot_supported() && snor_boot_selected()) {
		/* SNOR-SMI initialization */
		extern void snor_init(void);
		snor_init();

		uartDebug_Puts("4\r\n");

		u32 snorBootAddr;

#if defined(CONFIG_SPEAR320_MDI) || defined(CONFIG_SPEAR1380_REVC)
		/* setting SNOR image source addr */
		int bootSel = BOOT_SEL_VXBOOT;
		bootSel = getBootSel();
		if (bootSel == BOOT_SEL_UBOOT) {
			snorBootAddr = CONFIG_SNOR_BOOT_ADDR1;
			loader_name = loader_name_uboot;
		} else {
			/* VXBOOT */
			snorBootAddr = CONFIG_SNOR_BOOT_ADDR2;
			loader_name = loader_name_vxboot;
		}
#else
		snorBootAddr = CONFIG_SNOR_BOOT_ADDR;
		loader_name = loader_name_uboot;
#endif

		/* Serial NOR booting */
		if (TRUE == snor_image_load((u8 *) snorBootAddr,
					&image, loader_name)
#ifdef CONFIG_SNOR_BOOT_ADDR_EXTRA
		    || TRUE == snor_image_load((u8 *) CONFIG_SNOR_BOOT_ADDR_EXTRA,
					&image, loader_name)
#endif
		    ) {

			/* Platform related late initializations */
			plat_late_init();

			uartDebug_Puts("5\r\n");

			/* Jump to boot image */
			boot_image(image);
			return TRUE;
		}
	}
#ifndef SNOR_BOOT_ONLY //to save some space

	if (nand_boot_supported() && nand_boot_selected()) {
		/* NAND-FSMC initialization */
		extern void nand_init(void);
		nand_init();

		/* NAND booting */
		if (TRUE == nand_image_load(CONFIG_NAND_BOOT_BLK,
					    CONFIG_NAND_LAST_BLK, &image,
					    loader_name)) {
			/* Platform related late initialasations */
			plat_late_init();

			/* Jump to boot image */
			boot_image(image);
			return TRUE;
		}
	}

	if (pnor_boot_supported() && pnor_boot_selected()) {

		extern u32 get_pnor_width(void);

#if (defined(CONFIG_SPEAR1340) || defined(CONFIG_SPEAR1310))
		return CONFIG_PNOR_BOOT_ADDR;
#else
		u32 width = get_pnor_width();

		/*
		 * Try with 8-bit initialization first.
		 * If the authentication fails, jump to 16 bit
		 * initialization and so on
		 */
		if (width == PNOR_WIDTH_SEARCH)
			width = PNOR_WIDTH_8;

		/* Parallel NOR booting */
		for (; width <= PNOR_WIDTH_32; width++) {
			/* PNOR-FSMC-EMI initialization */
			extern void pnor_init(u32);
			pnor_init(width);

			if (TRUE ==
			    pnor_image_load((u8 *) CONFIG_PNOR_BOOT_ADDR, width,
					    &image, loader_name)) {
				/* Platform related late initialasations */
				plat_late_init();

				/* Jump to boot image */
				boot_image(image);
				return TRUE;
			}
		}
#endif
	}

	if (mmc_boot_supported() && mmc_boot_selected()) {
#if (defined(CONFIG_SPEAR1340) || defined(CONFIG_SPEAR1310))
		char *filename = (char *)MMC_UBOOT_FILE;
#endif

		/* MMC booting */
		plat_late_init();
#if (defined(CONFIG_SPEAR1340) || defined(CONFIG_SPEAR1310))
		return (u32)filename;
#else
		return FALSE;
#endif
	}

	if (spi_boot_supported() && spi_boot_selected()) {
		return FALSE;
		/* SPI booting */
		/* Not Supported for any platform as of now */
	}

	if (i2c_boot_supported() && i2c_boot_selected()) {
		return FALSE;
		/* I2C booting */
		/* Not Supported for any platform as of now */
	}

	/*
	 * All booting types without memory are listed as below
	 * Control has to be returned to BootROM in case of all
	 * the following booting scenarios
	 */

	if (usb_boot_supported() && usb_boot_selected()) {
		plat_late_init();
		return TRUE;
	}

	if (tftp_boot_supported() && tftp_boot_selected()) {
		plat_late_init();
		return TRUE;
	}

	if (uart_boot_supported() && uart_boot_selected()) {
		plat_late_init();
		return TRUE;
	}
#if defined(CONFIG_OS_BOOT)
	/*
	 * 2nd level boot (U-Boot) not found in flashes.
	 * Try running linux image from default location
	 */
	boot_os();
#endif
#endif //SNOR_BOOT_ONLY

	/* Ideally, the control should not reach here. */
	hang();
}

#if defined(CONFIG_OS_BOOT)
static void boot_os(void)
{
	funcp image;

	/*
	 * All the supported flash devices are listed here.
	 * Default linux booting is tried from the selected booting type
	 */

	if (snor_boot_supported() && snor_boot_selected()) {
		/* Serial NOR booting */
		if (TRUE == snor_image_load((u8 *) CONFIG_SNOR_OSBOOT_ADDR,
					&image, kernel_name)) {
			/* Platform related late initialasations */
			plat_late_init();

			/* Jump to boot image */
			boot_kernel(image);
		}
	}

	if (nand_boot_supported() && nand_boot_selected()) {
		/* NAND booting */
		if (TRUE == nand_image_load(CONFIG_NAND_OSBOOT_BLK,
					    CONFIG_NAND_OSLAST_BLK, &image,
					    kernel_name)) {
			/* Platform related late initialasations */
			plat_late_init();

			/* Jump to boot image */
			boot_kernel(image);
		}
	}

	if (pnor_boot_supported() && pnor_boot_selected()) {
		extern u32 get_pnor_width(void);
		u32 width = get_pnor_width();

		/*
		 * Try with 8-bit initialization first.
		 * If the authentication fails, jump to 16 bit
		 * initialization and so on
		 */
		if (width == PNOR_WIDTH_SEARCH)
			width = PNOR_WIDTH_8;

		/* Parallel NOR booting */
		for (; width <= PNOR_WIDTH_32; width++) {
			/* PNOR-FSMC-EMI initialization */
			extern void pnor_init(u32);
			pnor_init(width);

			if (TRUE ==
			    pnor_image_load((u8 *) CONFIG_PNOR_OSBOOT_ADDR,
					    width, &image, kernel_name)) {
				/* Platform related late initialasations */
				plat_late_init();

				/* Jump to boot image */
				boot_kernel(image);
			}
		}
	}
}
#endif

static void boot_image(funcp image)
{
	cleanup_caches();
	(*image) ();
}

static int snor_image_load(u8 *load_addr, funcp *image_p,
			   const char *image_name)
{
	image_header_t header;

	lcopy((const ulong *)load_addr, (ulong *)&header,
	      (sizeof(image_header_t) + sizeof(ulong) - 1) / sizeof(ulong));

	if (image_check_header(&header, image_name)) {
		RESET_TIMER;
		/* Copy the image to load address */
		lcopy((const ulong *)(load_addr + sizeof(image_header_t)),
		      (ulong *) image_get_load(&header),
		      (image_get_data_size(&header) + sizeof(ulong) -
		       1) / sizeof(ulong));
		SHOW_TIMER("snor_image_load");
		RESET_TIMER;

		if (image_check_data(&header)) {
			SHOW_TIMER("image_check_data");
			/* Jump to boot image */
			*image_p = (funcp)image_get_load(&header);
			return TRUE;
		}
	}

	return FALSE;
}
#ifndef SNOR_BOOT_ONLY //to save some space

static int nand_image_load(u32 blkstart, u32 blkend, funcp *image_p,
			   const char *image_name)
{
	image_header_t header;
	int ret = 0, blknum = blkstart;
	size_t size;
	ulong load_address;

	do {
		size = sizeof(image_header_t);
		ret = nand_read_skip_bad(blknum, 0, &size, (u_char *)&header);

		if ((ret >= 0) && image_check_header(&header, image_name)) {
			size = image_get_data_size(&header);
			load_address = image_get_load(&header);

			ret = nand_read_skip_bad(blknum,
						 sizeof(image_header_t),
						 &size, (void *)load_address);
			if (image_check_data(&header)) {
				/* Jump to boot image */
				*image_p = (funcp)image_get_load(&header);
				return TRUE;
			}
		}
	} while (++blknum < blkend);

	return FALSE;
}

static int pnor_image_load(u8 * load_addr, u32 norwidth, funcp *image_p,
			   const char *image_name)
{
	image_header_t header;

	/*
	 * Copy routines and respective widths are defined to generalize
	 * copy operations
	 */

	typedef void * (*func_ptr)(const void *, void *, int);

	func_ptr pnor_copy[PNOR_WIDTH_NUM] = {
		(func_ptr)bcopy,
		(func_ptr)wcopy,
		(func_ptr)lcopy
	};

	func_ptr copy_p;

	u32 numtypes, norshift;

	copy_p = pnor_copy[norwidth];

	switch (norwidth) {
	case PNOR_WIDTH_8:
		norshift = 0;
		break;

	case PNOR_WIDTH_16:
		norshift = 1;
		break;

	case PNOR_WIDTH_32:
		norshift = 2;
		break;

	default:
		norshift = 0;
		break;
	}

	numtypes = sizeof(image_header_t) >> norshift;

	copy_p((const void *)load_addr, &header, numtypes);

	if (image_check_header(&header, image_name)) {
		numtypes = image_get_data_size(&header) >> norshift;

		/* Copy the image to load address */
		copy_p((const void *)load_addr + sizeof(image_header_t),
		       (void *)image_get_load(&header), numtypes);

		if (image_check_data(&header)) {
			/* Jump to boot image */
			*image_p = (funcp)image_get_load(&header);
			return TRUE;
		}
	}

	return FALSE;
}
#endif // SNOR_BOOT_ONLY
