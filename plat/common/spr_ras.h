/*
 * Jean-Christophe Gillet, Schneider, jean-christophe.gillet@schneider-electric.com
 *
 */

#ifndef __SPR13XX_RAS_H
#define __SPR13XX_RAS_H

#include "asm/types.h"

struct conf_regs {
	u8  todo_1[0x30- 0x0];
	u32 prot_status;			/* 0x030 */
	u32 prot_en;				/* 0x034 */
	u32 prot_dis;				/* 0x038 */
	u8  todo_2[0x100- 0x3C];
	u32 IO0;				    /* 0x100 */
	u32 IO1;				    /* 0x104 */
	u32 IO2;				    /* 0x108 */
	u32 IO3;				    /* 0x10C */
	u32 IO4;				    /* 0x110 */
	u32 IO5;				    /* 0x114 */
	u32 IO6;				    /* 0x118 */
	u32 IO7;				    /* 0x11C */
	u32 IO8;				    /* 0x120 */
	u32 IO9;				    /* 0x124 */
	u32 IO10;				    /* 0x128 */
	u32 IO11;				    /* 0x12C */
	u32 IO12;				    /* 0x130 */
	u32 IO13;				    /* 0x134 */
	u32 IO14;				    /* 0x138 */
	u32 IO15;				    /* 0x13C */
	u32 IO16;				    /* 0x140 */
	u32 IO17;				    /* 0x144 */
	u32 IO18;				    /* 0x148 */
	u32 IO19;				    /* 0x14C */
	u32 IO20;				    /* 0x150 */
	u32 IO21;				    /* 0x154 */
	u32 IO22;				    /* 0x158 */
	u32 IO23;				    /* 0x15C */
	u32 IO24;				    /* 0x160 */
	u32 IO25;				    /* 0x164 */
	u32 IO26;				    /* 0x168 */
	u32 IO27;				    /* 0x16C */
	u32 IO28;				    /* 0x170 */
	u32 IO29;				    /* 0x174 */
	u32 IO30;				    /* 0x178 */
	u8 reserved_1[0x280-0x17C];
	u32 version; 		        /* 0x280 */
};

/* configuration protection */
#define DIS_PROT_WORD				(0xBCDEF012)
#define EN_PROT_WORD				(0xCDEF0123)

/* pad function configuration */
#define RAS_PAD_FUNC0		    (0)
#define RAS_PAD_FUNC1		    (1)
#define RAS_PAD_FUNC2		    (2)
#define RAS_PAD_FUNC3		    (3)
#define RAS_PAD_FUNC4		    (4)
#define RAS_PAD_FUNC5		    (5)
#define RAS_PAD_FUNC6		    (6)
#define RAS_PAD_FUNC7		    (7)
#define RAS_PAD_FUNC8		    (8)
#define RAS_PAD_FUNC9		    (9)
#define RAS_PAD_FUNC10		    (10)
#define RAS_PAD_FUNC11		    (11)
#define RAS_PAD_FUNC12		    (12)

struct rgpio2_regs {
	u32 a_data_out;		/* 0x00 */
	u32 a_dir; 		    /* 0x04 */
	u32 reserved_1;     /* 0x08 */
	u32 b_data_out;		/* 0x0C */
	u32 b_dir; 		    /* 0x10 */
	u32 reserved_2;     /* 0x14 */
	u32 c_data_out;		/* 0x18 */
	u32 c_dir; 		    /* 0x1C */
	u32 reserved_3;     /* 0x20 */
	u32 d_data_out;		/* 0x24 */
	u32 d_dir; 		    /* 0x28 */
	u8 reserved_4[0x50-0x2C];
	u32 a_data_in;		/* 0x50 */
	u32 b_data_in;		/* 0x54 */
	u32 c_data_in;		/* 0x58 */
	u32 d_data_in;		/* 0x5C */
};

#define CONFIG_RAS_BASE				(0x40000000)
#define CONFIG_RAS_CONF_BASE		(CONFIG_RAS_BASE+0xFFC8800)
#define CONFIG_RAS_RGPIO2_BASE		(CONFIG_RAS_BASE+0xFFC3400)
#define CONFIG_UART_DEBUG_BASEADDR  (CONFIG_RAS_BASE + 0xFFC1000)

/* perip*_[clk_enb/sw_rst] definitions */
#define BUS_CLKEN				(1 << 0)	/* perip1 */


#endif
