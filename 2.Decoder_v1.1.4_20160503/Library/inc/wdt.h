/*----------------------------------------------------------------------------
 *      Skuo LPC1768 12 Ports Decoder
 *----------------------------------------------------------------------------
 *      Name:    wdt.h
 *      Purpose: 12 Ports decoder demo@Fei,Hui
 *----------------------------------------------------------------------------
 *      This code is use the RealView Run-Time Library.
 *      2013-12.05
 *---------------------------------------------------------------------------*/
#ifndef __WDT_H 
#define __WDT_H

#define WDRC				0x00000000
#define WDPCLK			0x00000001
#define WDRTC				0x00000002
#define WDLOCK			0x80000000
#define WDEN				0x00000001
#define WDRESET			0x00000002
#define WDTOF				0x00000004
#define WDINT				0x00000008
#define WDTC_VALUE	0x03B9ACA0			//WDTC_VALUE = t*Fpclk/4, t=10s

#define WDTFeed			LPC_WDT->WDFEED = 0xAA;\
										LPC_WDT->WDFEED = 0x55

extern void WDT_IRQHandler	(void);
extern uint32_t WDTInit			(void);

#endif

/*------------------------------------------------------------------------------
--                            End Of File
------------------------------------------------------------------------------*/
