/** ****************************************************************************
 * @file    UartDebugNs16550.h
 * @date    29-05-2012
 * @author  Jean-Christophe Gillet
 * @brief   Header for uart16550 driver for debug in Spear 1380 RAS
 * 
 * Copyright (C) 2012 Schneider Automation, Carros
 * All Rights Reserved
 * 
 * *****************************************************************************
 */

#ifndef __UARTDEBUGNS16550_H__
#define __UARTDEBUGNS16550_H__


#ifdef __cplusplus
extern "C" {
#endif

struct uartRegs {
    unsigned RBR;        // 0x00
    unsigned IER;        // 0x04
    unsigned IIR;        // 0x08
    unsigned LCR;        // 0x0C
    unsigned MCR;        // 0x10
    unsigned LSR;        // 0x14
    unsigned MSR;        // 0x18
    unsigned SCR;        // 0x1C
};

// Alias on registers
#define THR RBR
#define DLL RBR
#define DLH IER
#define FCR IIR

// LSR register
#define UART_LSR_THRE (0x1 << 5)

// LCR register
#define UART_LCR_DLS_5_BIT (0x0)     // 5 bit data length select
#define UART_LCR_DLS_6_BIT (0x1)     // 8 bit data length select
#define UART_LCR_DLS_7_BIT (0x2)     // 7 bit data length select
#define UART_LCR_DLS_8_BIT (0x3)     // 8 bit data length select
#define UART_LCR_STOP_1_BIT (0x0)    // 1 stop bit
#define UART_LCR_PARITY_DISABLE (0x0)// 1 stop bit
#define UART_LCR_DLAB      (0x1 << 7)// Divisor latch access bit

// MCR register
#define UART_MCR_DTR    (0x1 << 0)         // DTR 
#define UART_MCR_RTS    (0x1 << 1)         // RTS 

// FCR register
#define UART_FCR_FIFO_ENABLE      (0x1 << 0)  
#define UART_FCR_RX_FIFO_RESET    (0x1 << 1)  
#define UART_FCR_TX_FIFO_RESET    (0x1 << 2)  

void uartDebugNs16550_SetBaseAddr(unsigned baseAddr);
void uartDebugNs16550_Init (void);
void uartDebugNs16550_Putc (char TxChar);

#ifdef __cplusplus
}
#endif

#endif // __UARTDEBUGNS16550_H__
