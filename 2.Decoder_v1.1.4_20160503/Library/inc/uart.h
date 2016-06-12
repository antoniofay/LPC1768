/*----------------------------------------------------------------------------
 *      Skuo LPC1768 12 Ports Decoder
 *----------------------------------------------------------------------------
 *      Name:    uart.h
 *      Purpose: 12 Ports decoder demo@Fei,Hui
 *----------------------------------------------------------------------------
 *      This code is use the RealView Run-Time Library.
 *      2013-12.05
 *---------------------------------------------------------------------------*/
 
#ifndef __UART_H
#define __UART_H

#define FOSC										12000000                            // oscillator frequency
#define FCCLK										(FOSC  * 8)                         // cpu clk frequency <= 100MHz
#define FCCO										(FCCLK * 3)                         // PLL frequency
#define FPCLK										(FCCLK / 4)                         // peripheral clk

extern void UARTInit 				(uint8_t n, uint32_t baudrate);
extern int  UARTSendByte 		(uint8_t n, int ucData);
extern int  UARTGetByte			(uint8_t n);
extern void UARTSendString	(uint8_t n, unsigned char *s);
extern void UARTSendDec 		(uint8_t n, uint32_t disp);
extern void print 					(uint8_t n, unsigned char *s, uint32_t disp);

#endif

/*------------------------------------------------------------------------------
--                            End Of File
------------------------------------------------------------------------------*/
