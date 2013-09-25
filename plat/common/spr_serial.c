/*
 * (C) Copyright 2009
 * Shiraz Hashim, ST Micoelectronics, shiraz.hashim@st.com.
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

#ifdef CONFIG_SPEAR13XX
#include <asm/arch/spr13xx_misc.h>
#include "spr_ras.h"
#else
#include <asm/arch/spr_misc.h>
#endif

void spear_serial_init(void)
{

#if (defined(CONFIG_SPEAR1380_REVA) ||  defined(CONFIG_SPEAR1380_REVC))
	struct misc_regs *misc_p = (struct misc_regs *)CONFIG_SPEAR_MISCBASE;
	//enable RAC clk
	struct conf_regs *const conf = (struct conf_regs * const)CONFIG_RAS_CONF_BASE;
	//writel(readl(&misc_p->ras_clk_enb) | 1<<1/*iPclk 83MHz*/|1<<5/*USBPHY pll 48MHz*/ , &misc_p->ras_clk_enb);
	writel(0x1 | 0x1 << 1 | 0x1 << 5 | 0x1 << 6 , &misc_p->ras_clk_enb);
	writel(RAS_RST_ALL, &misc_p->ras_sw_rst);

	//configure pads - only for trace purpose, no need to configure rx path
	uint32_t regIO = readl(&conf->IO5);
	/* disable protection */
	writel(DIS_PROT_WORD, &conf->prot_dis);
	while ((readl(&conf->prot_status) & 1) != 0x1){}
	/* configure pads */
	regIO = (regIO & (~((uint32_t)(0xf) << 8 ))) | (4 << 8 );
	regIO = (regIO & (~((uint32_t)(0xf) << 12))) | (4 << 12);
	writel(regIO, &conf->IO5);
	/* enable protection */
	writel(EN_PROT_WORD, &conf->prot_en);

	//use UART6
	uartDebug_InstallNs16550(CONFIG_UART_DEBUG_BASEADDR);
	uartDebug_Init();
	uartDebug_Puts("\r\n1\r\n");
#endif
#ifdef CONFIG_SPEAR320
	struct misc_regs *misc_p = (struct misc_regs *)CONFIG_SPEAR_MISCBASE;
	void *perip_clk_cfg, *perip_clk_enb;
	u32 val, uart_clk_enb;

	perip_clk_cfg = &misc_p->periph_clk_cfg;
	perip_clk_enb = &misc_p->periph1_clken;
	uart_clk_enb = PERIPH_UART1;

	/* choose the clk src to USB PLL (48MHz) */
	val = readl(perip_clk_cfg);
	val &= ~UARTCLK_MASK;
	val |= UARTCLK_48MHZ;
	writel(val, perip_clk_cfg);

	/* enable UART clk */
	val = readl(perip_clk_enb);
	val |= uart_clk_enb;
	writel(val, perip_clk_enb);

	uartDebug_InstallPl01x();
	uartDebug_Init();
	uartDebug_Puts("\r\n1\r\n");
#endif
}
