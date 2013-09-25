/** ****************************************************************************
 * @file    UartDebug.h
 * @date    29-05-2012
 * @author  Jean-Christophe Gillet
 * @brief   Header for uart debug
 *          very low level driver without using OS ressources
 *
 * Copyright (C) 2012 Schneider Automation, Carros
 * All Rights Reserved
 *
 * *****************************************************************************
 */

#ifndef __UARTDEBUG_H__
#define __UARTDEBUG_H__


#ifdef __cplusplus
extern "C" {
#endif

// special char
#define LF          '\n'
#define CR          '\r'
#define EOS         '\0'    // end of string

/*void uartDebug_InstallNs16550(unsigned baseAddr);
void uartDebug_InstallPl01x(void);
void uartDebug_Init (void);
void uartDebug_Putc (char TxChar);
void uartDebug_Puts (char *TxString);
void uartDebug_Puthex (unsigned TxVal);*/

#ifdef __cplusplus
}
#endif

#endif // __UARTDEBUG_H__
