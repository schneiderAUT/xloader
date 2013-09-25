#ifndef __SPEAR320_RAS_H__
#define __SPEAR320_RAS_H__

struct rasRegs {
	volatile unsigned int bootStrap;		    /* 0x00 */
	volatile unsigned int irqStatus;		    /* 0x04 */
	volatile unsigned int irqMask;		        /* 0x08 */
	volatile unsigned int rasSel;		        /* 0x0c */
	volatile unsigned int ctrl;		            /* 0x10 */
	volatile unsigned int touchsreenDur;        /* 0x14 */
	volatile unsigned int extControl;           /* 0x18 */
	unsigned char         reserved1[0x24-0x18-4];
	volatile unsigned int gpioSel_00_31;        /* 0x24 */
	volatile unsigned int gpioSel_32_63;        /* 0x28 */
	volatile unsigned int gpioSel_64_95;        /* 0x2c */
	volatile unsigned int gpioSel_96_101;       /* 0x30 */
	volatile unsigned int gpioOut_00_31;        /* 0x34 */
	volatile unsigned int gpioOut_32_63;        /* 0x38 */
	volatile unsigned int gpioOut_64_95;        /* 0x3c */
	volatile unsigned int gpioOut_96_101;       /* 0x40 */
	volatile unsigned int gpioEn_00_31;         /* 0x44 */
	volatile unsigned int gpioEn_32_63;         /* 0x48 */
	volatile unsigned int gpioEn_64_95;         /* 0x4c */
	volatile unsigned int gpioEn_96_101;        /* 0x50 */
	volatile unsigned int gpioIn_00_31;         /* 0x54 */
	volatile unsigned int gpioIn_32_63;         /* 0x58 */
	volatile unsigned int gpioIn_64_95;         /* 0x5c */
	volatile unsigned int gpioIn_96_101;        /* 0x60 */
};

#define PLGPIO_74_BITPOS	    (74-64)
#define PLGPIO_72_TO_75_PD_DIS	(0x1 << 4)
#define PLGPIO_72_TO_75_PU_DIS	(0x1 << 3)

#define SET_BIT(reg, bitPos)    (reg |= 0x1 << bitPos)
#define CLR_BIT(reg, bitPos)    (reg &= ~(0x1 << bitPos))
#define READ_BIT(reg, bitPos)   ((reg >> bitPos) & 0x1)

#endif
