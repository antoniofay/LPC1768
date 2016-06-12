/*----------------------------------------------------------------------------
 *      Skuo LPC1768 12 Ports Decoder
 *----------------------------------------------------------------------------
 *      Name:    adc.c
 *      Purpose: 12 Ports decoder demo@Fei,Hui
 *----------------------------------------------------------------------------
 *      This code is use the RealView Run-Time Library.
 *      2013.12.16
 *---------------------------------------------------------------------------*/
 
#include "lpc17xx.h"
#include "wdt.h"

volatile uint32_t wdt_counter;

/*----------------------------------------------------------------------------
*  Function name:		WDT_IRQHandler
*  Descriptions:		Watchdog timer interrupt handler
*  parameters:			None
*  Returned value:	None
----------------------------------------------------------------------------*/
void WDT_IRQHandler (void) {
  LPC_WDT->WDMOD &= ~WDTOF;							// clear the time-out flag, no effect when WDTReset set
  wdt_counter++;
  return;
}

/*----------------------------------------------------------------------------
*  Function name:		WDTInit
*  Descriptions:		Initialize watchdog timer, install the watchdog
* 									timer interrupt handler.
*  parameters:			None
*  Returned value:	true or false, return false if the NVIC table is
* 									full and WDT interrupt handler can be installed.
----------------------------------------------------------------------------*/
uint32_t WDTInit (void) {
  wdt_counter = 0;
	
  NVIC_EnableIRQ(WDT_IRQn);
	LPC_WDT->WDCLKSEL = WDPCLK | WDLOCK;
  LPC_WDT->WDTC 		= WDTC_VALUE;						// once WDEN is set, the WDT will start after feeding
  LPC_WDT->WDMOD 		= WDEN | WDRESET;
  LPC_WDT->WDFEED		= 0xAA;
  LPC_WDT->WDFEED		= 0x55;
  return 0;
}

/*------------------------------------------------------------------------------
--                            End Of File
------------------------------------------------------------------------------*/
