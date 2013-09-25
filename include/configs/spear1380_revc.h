/*
 */

#ifndef __CONFIG_H
#define __CONFIG_H

/*
 * High Level Configuration Options
 * (easy to change)
 */
#define CONFIG_SPEAR1380_REVC	1
#define CONFIG_SPEAR1310		1
#define CONFIG_SPEAR13XX		1

/*
 * Please select/define only one of the following
 * Each definition corresponds to a supported DDR chip.
 * DDR configuration is based on the following selection
 */
#define CONFIG_DDR_MT41J64M16		1
#define CONFIG_DDR_MT41J256M8		0

/*
 * DDR frequency selection
 *
 * Not available anymore in rev C
 *
 */
#define CONFIG_DDR_PLL1			0
#define CONFIG_DDR_PLL4			0

/* enable test of DDR */
#define CONFIG_RAM_TEST
/* #define CONFIG_RAM_TEST_VERBOSE */

/* Maximum supported DDR size */
#define PHYS_SDRAM_MAXSIZE		(1 * 1024 * 1024 * 1024)

/*
 * DDR frequency selection using PLL4
 * Select(define to 1) only one out of following list
 */
#define CONFIG_DDR_FREQ_400		0
#define CONFIG_DDR_FREQ_533		1


/*
#define DEBUG_TRACK_DDR_INIT
#define DEBUG_FORCE_DDR_32_BITS
*/

/*
 * DDR ECC Enable selection.
 * Select(define to 1).
 */

#ifdef CONFIG_SPEAR_USBTTY
 #undef  CONFIG_DDR_ECC_ENABLE
 #define CONFIG_C3_DDR_INIT		0
#else
 #define  CONFIG_DDR_ECC_ENABLE
 #define CONFIG_C3_DDR_INIT		1
#endif

/* #define CONFIG_TIMER_MEASURE */

#ifdef CONFIG_TIMER_MEASURE
  #define CONFIG_CA9TIMER
#endif  

/*
 * Machine type for SPEAr1380_revc
 */
#define CONFIG_MACH_TYPE		(2881)
#define CONFIG_BOOTARGS			\
		"console=ttyAMA0,115200 mem=1G root=/dev/mtdblock3 " \
		"rootfstype=jffs2"

/*
 * Platform specific defines (SPEAr)
 *
 * Strictly SPEAr300 specific. Do not modify any of the below definitins. All
 * these definitions are derived from SPEAr300 hardware support
 */
#define CONFIG_SPEAR_MPMCBASE		(0xEC000000)
#define CONFIG_SPEAR_MPMCREGS		(208)

#define CONFIG_SPEAR_BOOTSTRAPCFG	(0xE0700004)
	#define CONFIG_SPEAR_BOOTSTRAPSHFT	(0)
	#define CONFIG_SPEAR_BOOTSTRAPMASK	(0xF)
	#define CONFIG_SPEAR_BOOTBYPASS		(0x0)
	#define CONFIG_SPEAR_SNORBOOT_DEFUSBD	(0x1)
	#define CONFIG_SPEAR_NANDBOOT_DEFUSBD	(0x2)
	#define CONFIG_SPEAR_PNOR8BOOT_DEFUSBD	(0x3)
	#define CONFIG_SPEAR_PNOR16BOOT_DEFUSBD	(0x4)
	#define CONFIG_SPEAR_UARTBOOT		(0x5)
	#define CONFIG_SPEAR_PCIEBOOT		(0x6)
	#define CONFIG_SPEAR_SATABOOT		(0x7)
	#define CONFIG_SPEAR_USBBOOT		(0x8)
	#define CONFIG_SPEAR_SNORBOOT_DEFUART	(0x9)
	#define CONFIG_SPEAR_NANDBOOT_DEFUART	(0xA)
	#define CONFIG_SPEAR_PNOR8BOOT_DEFUART	(0xB)
	#define CONFIG_SPEAR_PNOR16BOOT_DEFUART	(0xC)
	#define CONFIG_SPEAR_MMCBOOT		(0xD)
	/* not supported */
	#define CONFIG_SPEAR_TFTPBOOT		(0xF)
	#define CONFIG_SPEAR_I2CBOOT		(0xF)
	#define CONFIG_SPEAR_SPIBOOT		(0xF)
	/* ECC status regs */
	#define MPMC_CTRL_REG_26            (CONFIG_SPEAR_MPMCBASE + 0x68)
	#define MPMC_26_ECC_STS_SHIFT	    (26)
	#define MPMC_26_ECC_STS_MSK        (0x1)
	#define MPMC_CTRL_REG_105           (CONFIG_SPEAR_MPMCBASE + 0x1a4)
	#define MPMC_105_ECC_STS_SHIFT      (0x3)
	#define MPMC_105_ECC_STS_MSK        (0xF)

/*
 * xxx_boot_supported macro defines whether a booting type is supported
 * or not. Modify/Add to only these macros to define new boot types
 */
#define SNOR_BOOT_ONLY                  1

#define boot_bypass_supported()         1
#define usb_boot_supported()		    1
#define pcie_boot_supported()           0
#define snor_boot_supported()           1
#define nand_boot_supported()           1
#define pnor_boot_supported()           1
#define tftp_boot_supported()           0
#define uart_boot_supported()           1
#define spi_boot_supported()            0
#define i2c_boot_supported()            0
#define mmc_boot_supported()            1

#include <configs/spear-common.h>
#include <configs/spear-boot.h>

#endif
