/*----------------------------------------------------------------------------
 *      Skuo LPC1768 12 Ports Decoder
 *----------------------------------------------------------------------------
 *      Name:    adc.c
 *      Purpose: 12 Ports decoder demo@Fei,Hui
 *----------------------------------------------------------------------------
 *      This code is use the RealView Run-Time Library.
 *      2013.12.05
 *---------------------------------------------------------------------------*/
 
#include "lpc17xx.h"
#include "adc.h"

// structure for indoor unit
struct Indoor indoor[PortNum];

volatile uint32_t adcount = 0;
const uint32_t admap[6] = {0,1,2,3,5,4};
uint32_t Alarm = 0, EMERG1 = 0, EMERG2 = 0;

/*----------------------------------------------------------------------------*
-- Function name:		ADCInit
-- Descriptions:		Initialize ADC
-- parameters:			None
-- Returned value:	None
-----------------------------------------------------------------------------*/
void ADCInit (void) {
  LPC_PINCON->PINSEL1  &= ~0x003FC000;
	LPC_PINCON->PINSEL1  |=  0x00154000;
	LPC_PINCON->PINSEL3  &= ~0xF0000000;
  LPC_PINCON->PINSEL3  |=  0xF0000000;				// P0.23-0.26, 1.30, 1.31 AD0.0-0.5
	
	LPC_PINCON->PINMODE1 &= ~0x003FC000;			// No pull-up no pull-down (function 10)
  LPC_PINCON->PINMODE1 |=  0x002A8000;
  LPC_PINCON->PINMODE3 &= ~0xF0000000;
  LPC_PINCON->PINMODE3 |=  0xA0000000;

  LPC_SC->PCONP      	 |=  (1<<12);					// Enable power to ADC block

  LPC_ADC->ADCR        =  (1 << 5)					// select AD0.0 pin
                       |  (24<< 8)					// ADC clock is 25MHz/25
                       |  (1 <<21);					// enable ADC
}

/*----------------------------------------------------------------------------*
-- Function name:		ADCStartCnv
-- Descriptions:		start ADC
-- parameters:			None
-- Returned value:	None
-----------------------------------------------------------------------------*/
#define ADCStartCnv		LPC_ADC->ADCR&=~(7<<24);\
											LPC_ADC->ADCR|=(1<<24)

/*----------------------------------------------------------------------------*
-- Function name:		ADCStopCnv
-- Descriptions:		stop ADC
-- parameters:			None
-- Returned value:	None
-----------------------------------------------------------------------------*/
#define	ADCStopCnv		(LPC_ADC->ADCR&=~(7<<24))

/*----------------------------------------------------------------------------*
-- Function name:		ADCGetCnv
-- Descriptions:		get ADC value
-- parameters:			None
-- Returned value:	None
-----------------------------------------------------------------------------*/
uint32_t ADCGetCnv (void) {
  uint32_t adGdr;

  while (!(LPC_ADC->ADGDR & (1UL<<31)));		// Wait for Conversion end
  adGdr = LPC_ADC->ADGDR;
  return((adGdr >> 4) & ADC_VALUE_MAX);			// read converted value
}

/*----------------------------------------------------------------------------*
-- Function name:		ADCRead
-- Descriptions:		read ADC values with flat filter
-- parameters:			None
-- Returned value:	None
-----------------------------------------------------------------------------*/
uint32_t ADCRead (uint8_t chn) {
	uint32_t i,ADCData = 0;
	volatile uint32_t ADCBuf = 0;
	
	LPC_ADC->ADCR &= (~0x000000FF);						// set adc channel
	LPC_ADC->ADCR |= (chn << 0);

	for(i=0; i<FilterOrder; i++) 
	{
		ADCStartCnv;
		ADCBuf = ADCGetCnv();
		ADCStopCnv;
		ADCData += ADCBuf;
	}
	ADCData = (ADCData / FilterOrder);
	ADCData = (ADCData * 3300)/4096;
	
  return (ADCData);
}

/*------------------------------------------------------------------------------
--                            End Of File
------------------------------------------------------------------------------*/
