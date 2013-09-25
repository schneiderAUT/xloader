/*
 * (C) Copyright 2009
 * Vipin Kumar, ST Micoelectronics, vipin.kumar@st.com.
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

#include <common.h>
#include <asm/io.h>
#include <asm/arch/spr13xx_misc.h>
#include <asm/arch/spr13xx_defs.h>
#include <asm/arch/spr13xx_mpmc.h>
#include <pl061.h>
#include <ddrtest.h>
#include "spr_ras.h"
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

/* global variable to store present slices for 16-bit DDR support */
u32 slice_present[DATA_SLICE_MAX] = { 0 };

static void ddr_clock_init(void)
{
	struct misc_regs *misc_p = (struct misc_regs *)CONFIG_SPEAR_MISCBASE;
	u32 perip_clkcfg, perip2_clkenb, perip2_swrst;
#if defined(CONFIG_SPEAR1310) && defined(CONFIG_DDR_ECC_ENABLE)
	u32 mpmc_cfg;
#endif

	perip_clkcfg = readl(&misc_p->perip_clk_cfg);

#if (CONFIG_DDR_PLL4)
	perip_clkcfg |= MPMC_CLK_PLL4;
#elif (CONFIG_DDR_PLL1)
	perip_clkcfg &= ~MPMC_CLK_PLL4;
#endif
	writel(perip_clkcfg, &misc_p->perip_clk_cfg);

	perip2_clkenb = readl(&misc_p->perip2_clk_enb);
	perip2_clkenb |= DDR_CTRL_CLKEN | DDR_CORE_CLKEN;
	writel(perip2_clkenb, &misc_p->perip2_clk_enb);

#if defined(CONFIG_SPEAR1310) && defined(CONFIG_DDR_ECC_ENABLE)
	/*
	 * Following modifies write access as non-bufferable
	 * and read to happen word by word. Without this
	 * dependent write-read are happening out of order
	 * resulting in Linux crash.
	 */
	mpmc_cfg = readl(&misc_p->mpmc_cfg);
	mpmc_cfg |= 0x05000000;
	mpmc_cfg &= ~0xf0f;
	mpmc_cfg |= 0x101;
 #ifdef CONFIG_SPEAR1380_REVC
	/* decode hardware bit for std or high density DDR */
	struct rgpio2_regs *const rgpio2_p = (struct rgpio2_regs * const)CONFIG_RAS_RGPIO2_BASE;
	if (readl(&rgpio2_p->b_data_in) & (0x1 << 21)) // RGPIO2B[21] <=> NFIO[12]
		mpmc_cfg |= (0x1 << 30); //enable 2GB address
 #endif
	writel(mpmc_cfg, &misc_p->mpmc_cfg);
#endif

	/*
	 * MISC compensation_ddr_cfg before mpmc reset
	 * disable automatic ddr pad compensation
	 * use fixed comzcp=0000 and comzcn=0000
	 */
#if defined(CONFIG_SPEAR1340)
	u32 pad_pu_cfg_3, pad_pd_cfg_3;

	/* MISC 0x710 update=0, enb=0, encomzc=0 */
	writel(0x00000000, &misc_p->compensation_ddr_cfg);

	/*
	 * The code below modifies pad_pu_cfg_3 and pad_pd_cfg_3
	 * registers settings in order to add support for SPEAr1340
	 * DDR Board Modifications:
	 * - DDR_CLKEN (XGPIO 88: PullDown = 1, PullUp = 0)
	 * - DDR_RESET (XGPIO 89: PullDown = 1, PullUp = 0)
	 */
	pad_pu_cfg_3 = readl(&misc_p->pad_pu_cfg_3);
	pad_pu_cfg_3 |= (PAD_88_PU_CFG | PAD_89_PU_CFG);
	writel(pad_pu_cfg_3, &misc_p->pad_pu_cfg_3);

	pad_pd_cfg_3 = readl(&misc_p->pad_pd_cfg_3);
	pad_pd_cfg_3 &= PAD_88_PD_CFG;
	pad_pd_cfg_3 &= PAD_89_PD_CFG;
	writel(pad_pd_cfg_3, &misc_p->pad_pd_cfg_3);

#elif (!defined(CONFIG_SPEAR1380_REVC))

#define PLGPIO_2_3_DIR_SEL		(void *)(CONFIG_SPEAR_GPIO0_BASE + 0x400)
#define PLGPIO_2_3_RW_DATA		(void *)(CONFIG_SPEAR_GPIO0_BASE + 0x3FC)

	/* Enable the GPIO Clock Enable */
	writel(readl(&misc_p->perip1_clk_enb) | GPIO0_CLKEN,
			&misc_p->perip1_clk_enb);
	/*
	 * The code below modifies plgpio2 and plgpio3
	 * registers settings in order to add support for SPEAr13xx
	 * DDR Board Modifications:
	 * - DDR_CLKEN (PLGPIO 2: PullDown = 1, PullUp = 0)
	 * - DDR_RESET (PLGPIO 3: PullDown = 1, PullUp = 0)
	 */

	/* Set up the plgpio direction as output */
	writel(readl(PLGPIO_2_3_DIR_SEL) | 0xc, PLGPIO_2_3_DIR_SEL);
	/* Set up the Value for DDR_CLKEN and DDR_RESET */
	writel(readl(PLGPIO_2_3_RW_DATA) | (PLGPIO3_PU_CFG | PLGPIO2_PU_CFG) ,
			PLGPIO_2_3_RW_DATA);
	writel(readl(PLGPIO_2_3_RW_DATA) & (PLGPIO3_PD_CFG & PLGPIO2_PD_CFG),
			PLGPIO_2_3_RW_DATA);

#endif
	perip2_swrst = readl(&misc_p->perip2_sw_rst);
	perip2_swrst |= DDR_CTRL_CLKEN | DDR_CORE_CLKEN;
	writel(perip2_swrst, &misc_p->perip2_sw_rst);

	perip2_swrst = readl(&misc_p->perip2_sw_rst);
	perip2_swrst &= ~(DDR_CTRL_CLKEN | DDR_CORE_CLKEN);
	writel(perip2_swrst, &misc_p->perip2_sw_rst);

#if defined(CONFIG_SPEAR1310) && defined(CONFIG_DDR_ECC_ENABLE)
	/* enable MPMC ECC gasket for all AXI ports */
	writel(0x0, &misc_p->mpmc_ctr_sts);

	/* wait for turn-on */
	while ((readl(&misc_p->mpmc_ctr_sts) & 0xFFF))
		;
#endif

}

static void mpmc_init_values(void)
{
	u32 i;
	u32 *mpmc_reg_p = (u32 *)CONFIG_SPEAR_MPMCBASE;
	u32 *mpmc_val_p = &mpmc_conf_vals[0];

	for (i = 0; i < DATA_SLICE_MAX; i++)
		slice_present[i] = 1;

	for (i = 0; i < CONFIG_SPEAR_MPMCREGS; i++, mpmc_reg_p++, mpmc_val_p++)
		writel(*mpmc_val_p, mpmc_reg_p);

	mpmc_reg_p = (u32 *)CONFIG_SPEAR_MPMCBASE;

	/* patch DENALI_CTL_72_DATA - just to try debug */
	/* writel(0x00420042, CONFIG_SPEAR_MPMCBASE + 72*4); */

	/* patch DENALI_CTL_49_DATA - just to try debug */
	/* writel(0x10030407, CONFIG_SPEAR_MPMCBASE + 49*4); */

#ifdef DEBUG_TRACK_DDR_INIT
	uartDebug_Puts("mpmc_init_values - 1st : OK\r\n");
#endif

#ifdef CONFIG_SPEAR1380_REVC
	/* Detect 16 or 32 bits DDR */
#ifndef DEBUG_FORCE_DDR_32_BITS
	struct rgpio2_regs *const rgpio2_p = (struct rgpio2_regs * const)CONFIG_RAS_RGPIO2_BASE;
	if (!(readl(&rgpio2_p->b_data_in) & (0x1 << 22))) // RGPIO2B[22] <=> NFIO[13]
	{
		/* DDR bus width is 16 bits */
		writel(0x00000100, &mpmc_reg_p[10]); // reduced operation (16 bits)
		slice_present[2] = 0; /* bits 16 to 23 unused */
		slice_present[3] = 0; /* bits 24 to 31 unused */
	}
#endif
#endif

#ifdef DEBUG_TRACK_DDR_INIT
	uartDebug_Puts("mpmc_init_values - patch 16 32 bits DDR : OK\r\n");
#endif

	/*
	 * MPMC register25 rewrite
	 * MPMC controller start
	 */
	writel(0x03070700, &mpmc_reg_p[25]);
	writel(0x01000101, &mpmc_reg_p[11]);
#if (defined(CONFIG_SPEAR1340) || defined(CONFIG_SPEAR1310))
	while (!(readl(&mpmc_reg_p[105]) & 0x200))
#else
	while (!(readl(&mpmc_reg_p[105]) & 0x100))
#endif
		;

#ifdef DEBUG_TRACK_DDR_INIT
	uartDebug_Puts("mpmc_init_values - mpmc start : OK\r\n");
#endif

}

static void mpmc_init(void)
{
	/* Clock related settings for DDR */
	ddr_clock_init();

#ifdef DEBUG_TRACK_DDR_INIT
	uartDebug_Puts("ddr_clock_init : OK\r\n");
#endif

	/* Initialize mpmc register values */
	mpmc_init_values();

#ifdef DEBUG_TRACK_DDR_INIT
	uartDebug_Puts("mpmc_init_values : OK\r\n");
#endif

	/*
	 * DDR pad register bits are different for different SoCs
	 * Compensation values are also handled separately
	 */
	plat_ddr_init();

#ifdef DEBUG_TRACK_DDR_INIT
	uartDebug_Puts("plat_ddr_init : OK\r\n");
#endif
}

static void pll_late_init(void)
{
	struct misc_regs *misc_p = (struct misc_regs *)CONFIG_SPEAR_MISCBASE;

	/* Initialize PLLs */
#if CONFIG_SPEAR1380_REVC

	writel(FREQ_533, &misc_p->pll4_frq);

#elif CONFIG_DDR_FREQ_400
	writel(FREQ_400, &misc_p->pll4_frq);
#elif CONFIG_DDR_FREQ_533
	writel(FREQ_533, &misc_p->pll4_frq);
#else
#error Define one of the valid DDR frequency(CONFIG_DDR_FREQ_[533/400])
#endif
	/* strobing required for pll4 */
	writel(0x60A, &misc_p->pll4_ctr);
	writel(0x60E, &misc_p->pll4_ctr);
	writel(0x606, &misc_p->pll4_ctr);
	writel(0x60E, &misc_p->pll4_ctr);

	/* wait for pll locks */
	while (!(readl(&misc_p->pll4_ctr) & PLLLOCK))
		;
}

static void pll_init(void)
{
	struct misc_regs *misc_p = (struct misc_regs *)CONFIG_SPEAR_MISCBASE;
	u32 usbphycfg;

	/* Initialize PLLs */
	writel(FREQ_1000, &misc_p->pll1_frq);
	writel(readl(&misc_p->pll1_ctr) | PLLENABLE, &misc_p->pll1_ctr);

	writel(FREQ_125, &misc_p->pll2_frq);
	writel(readl(&misc_p->pll2_ctr) | PLLENABLE, &misc_p->pll2_ctr);

	usbphycfg = readl(&misc_p->usbphy_gen_cfg);
	usbphycfg &= ~(COMMON_PWDN | USBPHY_POR);
	usbphycfg |= USBPHY_RST;

	writel(usbphycfg, &misc_p->usbphy_gen_cfg);
	while (!(readl(&misc_p->usbphy_gen_cfg) & USB_PLL_LOCK))
		;
	/* AHB Master Burst is not supported for SPEAr1340 */

	usbphycfg = readl(&misc_p->usbphy_gen_cfg);

	usbphycfg |= AUTOPPD_ON_OVRCURR | UTMI_XFER_RST0 | UTMI_XFER_RST1 |
		UTMI_XFER_RST2;
#if (!defined(CONFIG_SPEAR1340) && !defined(CONFIG_SPEAR1310))
	usbphycfg |= USB_BURST_INCR16;
#endif
	writel(usbphycfg, &misc_p->usbphy_gen_cfg);

	/* wait for pll locks */
	while (!(readl(&misc_p->pll1_ctr) & PLLLOCK))
		;
	while (!(readl(&misc_p->pll2_ctr) & PLLLOCK))
		;
}

static void mac_init(void)
{
}

static void sys_init(void)
{
	struct misc_regs *misc_p = (struct misc_regs *)CONFIG_SPEAR_MISCBASE;
	u32 sysclkctrl;

	/* Set system state to SLOW */
	sysclkctrl = readl(&misc_p->sys_clk_ctrl);
	sysclkctrl &= ~SYS_MODE_MASK;
	sysclkctrl |= XTAL_TIMEOUT_ENB | PLL_TIMEOUT_ENB | SYS_MODE_REQ_SLOW;
	writel(sysclkctrl, &misc_p->sys_clk_ctrl);

	writel(PLL_TIM, &misc_p->sys_clk_plltimer);
	writel(OSCI_TIM, &misc_p->sys_clk_oscitimer);

#if defined(CONFIG_SPEAR1340)
	u32 plgpio_enb_3;
	/*
	 * The code below modifies  plgpio_enb_3 register
	 * settings in order to add support for SPEAr1340
	 * rev AB DDR Board Modifications setting in output
	 * GPIOs 88 and 89 on GPIO controller.
	 */
	plgpio_enb_3 = readl(PLGPIO_ENB_3);
	plgpio_enb_3 &= ~(PLGPIO_88_CFG | PLGPIO_89_CFG);
	writel(plgpio_enb_3, PLGPIO_ENB_3);

	u32 pad_pu_cfg_1, pad_pd_cfg_1;

	/*
	 * The code below modifies pad_pu_cfg_1 and pad_pd_cfg_1
	 * registers settings in order to add support for SPEAr1340
	 * DDR Board Modifications:
	 * - DDR_PHY_1v2 (XGPIO 21: PullDown = 1, PullUp = 0)
	 * - DDR_PHY_1v5 (XGPIO 22: PullDown = 1, PullUp = 0)
	 */
	pad_pu_cfg_1 = readl(&misc_p->pad_pu_cfg_1);
	pad_pu_cfg_1 |= (PAD_21_PU_CFG | PAD_22_PU_CFG);
	writel(pad_pu_cfg_1, &misc_p->pad_pu_cfg_1);

	pad_pd_cfg_1 = readl(&misc_p->pad_pd_cfg_1);
	pad_pd_cfg_1 &= PAD_21_PD_CFG;
	pad_pd_cfg_1 &= PAD_22_PD_CFG;
	writel(pad_pd_cfg_1, &misc_p->pad_pd_cfg_1);
#elif (defined(CONFIG_SPEAR1310) && !defined(CONFIG_SPEAR1380_REVC))
	/*
	 * Set the PAD function enable such that the PADs are routed to
	 * IP
	 */
	writel(readl(&misc_p->pad_function_en_1) | 0x300,
		&misc_p->pad_function_en_1);
	/*
	* Set up the PAD direction in control of IP's / RAS by default
	*/
	writel(readl(&misc_p->pad_dir_sel_1) | 0x300,
		&misc_p->pad_dir_sel_1);
#endif

	/* Initialize PLLs */
	pll_init();

	mac_init();

	/* Set system state to NORMAL */
	sysclkctrl = readl(&misc_p->sys_clk_ctrl);
	sysclkctrl &= ~SYS_MODE_MASK;
	sysclkctrl |= XTAL_TIMEOUT_ENB | PLL_TIMEOUT_ENB | SYS_MODE_REQ_NORMAL;
	writel(sysclkctrl, &misc_p->sys_clk_ctrl);

	/* Wait for system to switch to normal mode */
	while ((readl(&misc_p->sys_clk_ctrl) & SYS_STATE_MASK) !=
			SYS_STATE_NORMAL);
}

#ifdef CONFIG_SPEAR900_LCAD
static void pl061_init(void)
{
	struct misc_regs *misc_p = (struct misc_regs *)CONFIG_SPEAR_MISCBASE;

	writel(readl(&misc_p->perip1_clk_enb) | GPIO1_CLKEN,
			&misc_p->perip1_clk_enb);
}

/*
 * SPEAr900 LCAD board requires a GPIO to be set in order to
 * power on...
 */
static void set_lcad_power_on(void)
{
	pl061_set_value(CONFIG_SPEAR_GPIO1_BASE, GPIO1_1, 1);
	pl061_set_out(CONFIG_SPEAR_GPIO1_BASE, GPIO1_1);
	pl061_set_value(CONFIG_SPEAR_GPIO1_BASE, GPIO1_1, 1);
}
#endif

#ifdef CONFIG_SPEAR1340_LCAD
static void pl061_init(void)
{
	struct misc_regs *misc_p = (struct misc_regs *)CONFIG_SPEAR_MISCBASE;

	writel(readl(&misc_p->perip1_clk_enb) | GPIO0_CLKEN,
			&misc_p->perip1_clk_enb);
}

/*
 * SPEAr1340 LCAD board requires a GPIO to be set in order to
 * power on...
 */
static void set_lcad_power_on(void)
{
	pl061_set_value(CONFIG_SPEAR_GPIO0_BASE, GPIO0_3, 1);
	pl061_set_out(CONFIG_SPEAR_GPIO0_BASE, GPIO0_3);
	pl061_set_value(CONFIG_SPEAR_GPIO0_BASE, GPIO0_3, 1);
}
#endif

#ifdef CONFIG_RAM_TEST
void ddr_memory_test(void)
{
	/* memory test trial */
	if (probememory()) {
		while (1) /* loop infinitly on ddr test error */
		;
	}
}
#endif

void lowlevel_init(void)
{
	struct misc_regs *misc_p = (struct misc_regs *)CONFIG_SPEAR_MISCBASE;
#if defined(CONFIG_SPEAR1310) && !defined(CONFIG_SPEAR1380_REVC)
	u32 pad_dir_sel1_reg;
#endif

	/* Pad configuration */
#ifdef CONFIG_SPEAR1380_REVC
	/* bootrom IO are routed and driven by IPs in standard part.
	* To avoid contention on Spear output driven and other device on board
	* IO are routed to RAS and not driven because RAS part is always under reset
	*
	* IOs routed to standard IPs:
	*   EGPIO_A[0],..EGPIO_A[7],EGPIO_B[8],EGPIO_B[9]
	*   SDA,SCL
	*   SMIDATAIN,SMIDATAOUT,SMI_CLK,SMI_nCS[0],SMI_nCS[1]
	*   NFIO[0],..,NFIO[7],NFCE0,NFWE,NFRE,NFALE,NFCLE,NFRB,NFRWPRT0
	*   GMII_TXCLK125,GMII_TXCLK,MII_TXCLK,TXD[0],TXD[1],TXD[2],TXD[3],GMII_TXD[4],GMII_TXD[5],GMII_TXD[6],GMII_TXD[7],TX_EN,TX_ER
	*   RX_CLK,RX_DV,RX_ER,RXD[0],RXD[1],RXD[2],RXD[3],GMII_RXD[4],GMII_RXD[5],GMII_RXD[6],GMII_RXD[7],GMII_COL,CRS,MDC,MDIO
	*   MCI_Data0,MCI_Data1_SD,MCI_Data2_SD,MCI_Data3_SD,MCI_Addr1_CLE_CLK,MCI_nCD_SD_MMC,MCI_DMARQ_RnB_WP,MCI_SD_CMD
	*
	* Others configurable IOs are configured for RAS.
	*
	* use Table 60 in SPEAR1310 - ADDRESS MAP AND REGISTERS RM - REV2.pdf
	*
	*/

   /* pad function enable :
    * 0 : pad routed to RAS
    * 1 : pad routed to IP
    */
   writel(  0x1         /* bit 0 is reserved in revC */
		 | (0x1 << 2)   /* SDA, SCL */
		 | (0x3ff << 6) /* EGPIO_A[0],..EGPIO_A[7],EGPIO_B[8],EGPIO_B[9] */
		 | (0x1 << 16)  /* SMIDATAIN,SMIDATAOUT,SMI_CLK,SMI_nCS[0],SMI_nCS[1] */
		 | (0x1 << 17)  /* FSMC for NAND 8-bit */
		 | (0x1f << 18) /* MAC0 */
		 , &misc_p->pad_function_en_1);
   writel(((0x1 << 27)) /* MCI_Data0 */
		 , &misc_p->pad_function_en_2);
   writel( (0x7 << 3)   /* MCI_Data1_SD,MCI_Data2_SD,MCI_Data3_SD */
		 | (0x1 << 7)   /* MCI_Addr1_CLE_CLK */
		 | (0x1 << 15)  /* MCI_nCD_SD_MMC */
		 | (0x1 << 17)  /* MCI_DMARQ_RnB_WP */
		 | (0x1 << 26)  /* MCI_SD_CMD */
		 , &misc_p->pad_function_en_3);

   /* pad direction selection :
    * 0 : pad direction set to input
    * 1 : pad direction controlled by IP or RAS depending on pad_function_en_* registers
    */
   writel( 0xfffffffe, &misc_p->pad_dir_sel_1); // bit 0 reserved
   writel( 0xffffffff, &misc_p->pad_dir_sel_2);
   writel( 0x7fffffff, &misc_p->pad_dir_sel_3); // bit 31 reserved

   /* pad pull up and pull down configuration : done in OS */
   /* pad drive level configuration : done in OS */
   /* pad slew level configuration : done in OS */

#endif

	/* Initialize PLLs */
	sys_init();

#if defined(CONFIG_OS_BOOT)
	writel(readl(&misc_p->perip1_clk_enb) | UART_CLKEN,
			&misc_p->perip1_clk_enb);
#endif

	/* Enable IPs (release reset) */
	writel(PERIPH1_RST_ALL, &misc_p->perip1_sw_rst);
	writel(PERIPH2_RST_ALL, &misc_p->perip2_sw_rst);

#if defined(CONFIG_SPEAR900_LCAD) || defined(CONFIG_SPEAR1340_LCAD)
	pl061_init();

	/* Power on complete */
	set_lcad_power_on();
#endif

#if defined(CONFIG_SPEAR1340)
	writel(PERIPH3_RST_ALL, &misc_p->perip3_sw_rst);
#else
	writel(RAS_RST_ALL, &misc_p->ras_sw_rst);
#endif

#if defined(CONFIG_SPEAR1310) && !defined(CONFIG_SPEAR1380_REVC)
	pad_dir_sel1_reg = readl(&misc_p->pad_dir_sel_1);
	pad_dir_sel1_reg |= PAD_DIR_SEL_1_UART;
	writel(pad_dir_sel1_reg, &misc_p->pad_dir_sel_1);
#endif

	/* Read Ras Gpio for hardware configuration bits of MPMC*/
#ifdef CONFIG_SPEAR1380_REVC

	/* init uart debug */
	spear_serial_init();

	/* Configure ras clock, reset, and pads to access RGPIO2B pins
	 * used to read hardware configuration bits */
	struct conf_regs *conf  = (struct conf_regs *)CONFIG_RAS_CONF_BASE;
	u32 perip1_clk_enb;
	u32 ras_clk_enb;

	/* enable CLK periph 1 */
	perip1_clk_enb = readl(&misc_p->perip1_clk_enb);
	perip1_clk_enb |= (0x1 );          // enable bus (ahb axi) clk
	perip1_clk_enb |= (GPIO1_CLKEN);   // enable clk for gpio B used for test mode detection
	writel(perip1_clk_enb, &misc_p->perip1_clk_enb);

	/* enable 166Mhz, 83Mhz, 48Mhz and 30Mkz clock for RAS. */
	ras_clk_enb = 0x1 | 0x1 << 1 | 0x1 << 5 | 0x1 << 6;
	writel(ras_clk_enb, &misc_p->ras_clk_enb);

	/* disable protection */
	writel(DIS_PROT_WORD, &conf->prot_dis);

	/* configure ROW[5:2] pad = hardware configuration bits */
	u32 regIO = readl(&conf->IO23);
	regIO = (regIO & (~((u32)(0xffff) << 16)))
			| (RAS_PAD_FUNC7 << 16)  /* ROW[2] */
			| (RAS_PAD_FUNC7 << 20)  /* ROW[3] */
			| (RAS_PAD_FUNC7 << 24)  /* ROW[4] */
			| (RAS_PAD_FUNC7 << 28); /* ROW[5] */
	writel(regIO, &conf->IO23);

	/* enable protection */
	writel(EN_PROT_WORD, &conf->prot_en);
	readl(&conf->prot_en);

#ifdef DEBUG_TRACK_DDR_INIT
	uartDebug_Puts("\r\n");
	uartDebug_Puts("pad conf to rd hw conf 16 or 32 bit ddr : OK\r\n");
#endif

#endif

	pll_late_init();

	/* Initialize MPMC */
	RESET_TIMER;
	mpmc_init();
	SHOW_TIMER("mpmc_init");

#ifdef DEBUG_TRACK_DDR_INIT
	uartDebug_Puts("mpmc_init : OK\r\n");
#endif

	/* SoC specific initialization */
	soc_init();

#ifdef DEBUG_TRACK_DDR_INIT
	uartDebug_Puts("soc_init : OK\r\n");
#endif

#ifdef CONFIG_RAM_TEST
	/* WARNING: must wait few time before accessing DDR */
	/* process test for DDR */
	RESET_TIMER;
    test_ddr(TEST_DDR_WITHOUT_ECC);
	SHOW_TIMER("test_ddr_no_ecc");

#ifdef DEBUG_TRACK_DDR_INIT
	uartDebug_Puts("test_ddr wo ECC: OK\r\n");
#endif

#endif

}
