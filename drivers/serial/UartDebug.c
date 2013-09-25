/** ****************************************************************************
 * @file    UartDebug.c
 * @date    30-05-2012
 * @author  Jean-Christophe Gillet
 * @brief   Driver for uart debug (poolling mode).
 *          very low level driver without using OS ressources
 *
 * Copyright (C) 2012 Schneider Automation, Carros
 * All Rights Reserved
 *
 * *****************************************************************************
 */

#include "common.h"
#include "UartDebug.h"
#include "UartDebugNs16550.h"
#include "serial_pl01x.h"

// globals
static void (* uartDebug_InitRtn) (void) = uartDebugNs16550_Init; /*init to avoid to be on DDR*/
static void (* uartDebug_PutcRtn) (char) = uartDebugNs16550_Putc; /*init to avoid to be on DDR*/

/** ****************************************************************************
 * Install uart debug routines IP dependent
 *
 * *****************************************************************************
 */
void uartDebug_InstallNs16550(unsigned baseAddr) {
#ifndef CONFIG_SPEAR_USBTTY
    uartDebug_InitRtn = uartDebugNs16550_Init;
    uartDebug_PutcRtn = uartDebugNs16550_Putc;
    uartDebugNs16550_SetBaseAddr(baseAddr);
#endif
}

void uartDebug_InstallPl01x(void) {
#ifndef CONFIG_SPEAR_USBTTY
    uartDebug_InitRtn = serial_pl01x_init;
    uartDebug_PutcRtn = serial_putc;
#endif
}

/** ****************************************************************************
 * Initialize uart debug
 *
 * *****************************************************************************
 */
void uartDebug_Init(void) {
#ifndef CONFIG_SPEAR_USBTTY
    uartDebug_InitRtn();
#endif
}


/** ****************************************************************************
 * Put char from uart debug
 *
 * @param TxChar : char to put on serial link - RO
 *
 * *****************************************************************************
 */
void uartDebug_Putc (char TxChar)
{
#ifndef CONFIG_SPEAR_USBTTY
    uartDebug_PutcRtn(TxChar);
#endif
}


/** ****************************************************************************
 * Put string for uart debug
 *
 * @param TxString : string to put on serial link - RO
 *
 * *****************************************************************************
 */
void uartDebug_Puts (char *TxString)
{
#ifndef CONFIG_SPEAR_USBTTY
    unsigned  i = 0 ;

    while ( (TxString[i] != EOS) )
    {
        uartDebug_Putc(TxString[i++]);
    }
#endif
}


/** ****************************************************************************
 * Converts an u32 to an hexa ASCII string and prints it to debug uart
 *
 * @param  TxVal : value to print in hexadecimal - RO
 *
 * *****************************************************************************
 */
void uartDebug_Puthex (unsigned int TxVal)
{
#ifndef CONFIG_SPEAR_USBTTY
   unsigned char ucharVal, hexaDigit;
   unsigned buf[2];
   int i, j;

   uartDebug_Puts("0x");

   for  (j = 24; j >= 0; j = j - 8)
   {
        // unsigned char to print
        ucharVal  = (unsigned char) (TxVal >> j);

        // converts the unsigned char to print
        for (i = 1; i >= 0; i--)
        {
            hexaDigit = (ucharVal & 0xF);
            if (hexaDigit < 10)
            {
                buf[i] = hexaDigit + '0';
            }
            else
            {
                buf[i] = (hexaDigit - 10) + 'A';
            }
            ucharVal = ucharVal >> 4;
        }

        uartDebug_Putc(buf[0]);
        uartDebug_Putc(buf[1]);
   }
#endif
}

/** ****************************************************************************
 * Converts an u32 to an decimal ASCII string and prints it to debug uart
 *
 * @param  TxVal : value to print in decimal - RO
 *
 * *****************************************************************************
 */
void uartDebug_Putdec (unsigned int number)
{
	int dec;
	int table[20];
	int i =0;
	int j =0;
	if (number == 0)
		uartDebug_Putc((char)((int)'0'));

	while (number > 0 && i < 20)
	{
		dec = (int)(number % 10);
		table[i]=dec;
		i++;
		number=((number - dec) / 10);
	}
	for (j = (i-1);j>=0;j--) {
		uartDebug_Putc((char)(((int)'0')+table[j]));
	}
}
