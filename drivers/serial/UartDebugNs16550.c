/** ****************************************************************************
 * @file    UartDebugNs16550.c
 * @date    25-05-2012
 * @author  Jean-Christophe Gillet
 * @brief   Driver for uart16550 for debug in Spear 1380 RAS (poolling mode)
 *          very low level driver without using OS ressources
 *
 * Copyright (C) 2012 Schneider Automation, Carros
 * All Rights Reserved
 *
 * *****************************************************************************
 */


#include "UartDebug.h"
#include "UartDebugNs16550.h"

// globals
static unsigned int baseAddr = 0;

/** ****************************************************************************
 * Set base addresse where uart debug is mapped in memory
 *
 * *****************************************************************************
 */
void uartDebugNs16550_SetBaseAddr(unsigned int uartBaseAddr) {
    baseAddr = uartBaseAddr;
}

/** ****************************************************************************
 * Init for uart debug (compatible ns16550)
 *
 *    8 data bit, 1 stop bit, none parity, 115200 Bauds
 * *****************************************************************************
 */
void uartDebugNs16550_Init (void)
{
    volatile struct uartRegs * uart = (struct uartRegs *)baseAddr;
    const unsigned lcrRegVal = UART_LCR_DLS_8_BIT | UART_LCR_STOP_1_BIT | UART_LCR_PARITY_DISABLE;
    /* baudrate dividor = clock freq / (baudrate*16) = 48Mhz / (115200 * 16) = 26 */
    const unsigned baudrateDividor = 26;

    // disable interrupt
    uart->IER = 0;

    // LDAB = 1, disable clock baud then disable RX and TX for uart
    uart->LCR = UART_LCR_DLAB | lcrRegVal;
    uart->DLH = 0;
    uart->DLL = 0;

    // come back to LDAB=0
    uart->LCR = UART_LCR_DLAB | lcrRegVal;

    // enable fifo & reset fifo
    uart->FCR = UART_FCR_FIFO_ENABLE | UART_FCR_RX_FIFO_RESET | UART_FCR_TX_FIFO_RESET;

    // always enable modem for TX & RX
    uart->MCR = UART_MCR_DTR | UART_MCR_RTS;

    // LDAB = 1 & set baudrate
    uart->LCR = UART_LCR_DLAB | lcrRegVal;
    uart->DLH = (baudrateDividor >> 8) & 0xFF;
    uart->DLL = baudrateDividor & 0xFF;

    // come back to LDAB=0
    uart->LCR = lcrRegVal;
}

/** ****************************************************************************
 * Put char for uart debug
 *
 * @param TxChar : char to put on serial link - RO
 *
 * *****************************************************************************
 */
void uartDebugNs16550_Putc (char TxChar)
{
    volatile struct uartRegs * uart = (struct uartRegs *)baseAddr;

    // wait tx fifo empty
    while ((uart->LSR & UART_LSR_THRE) == 0);
    // put char on output
    uart->THR = TxChar;
}
