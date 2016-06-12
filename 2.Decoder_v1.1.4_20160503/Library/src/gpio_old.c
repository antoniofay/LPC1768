/*----------------------------------------------------------------------------
 *      Skuo LPC1768 12 Ports Decoder
 *----------------------------------------------------------------------------
 *      Name:    gpio.c
 *      Purpose: 12 Ports decoder demo@Fei,Hui
 *----------------------------------------------------------------------------
 *      This code is use the RealView Run-Time Library.
 *      2013.12.05
 *---------------------------------------------------------------------------*/

#include <lpc17xx.h>
#include <gpio.h>
#include <adc.h>

extern uint8_t video;
/*----------------------------------------------------------------------------*
-- Function name:		GPIOInit
-- Descriptions:		Initialize GPIO
-- parameters:			None
-- Returned value:	None
-----------------------------------------------------------------------------*/
void GPIOInit (void) {
	int i;
	// GPIO pin selected
	LPC_PINCON->PINSEL0 &= ~((3UL<< 0)
													|(3UL<< 2)
													|(3UL<<20)
													|(3UL<<22)
													|(3UL<<30));			// Pin0.0, Pin0.1, Pin0.10, Pin0.11, 0.15
	LPC_PINCON->PINSEL1 &= ~((3UL<< 0)
													|(3UL<< 2)
													|(3UL<< 4)
													|(3UL<< 6)
													|(3UL<< 8)
													|(3UL<<10)
													|(3UL<<12)
													|(3UL<<22)
													|(3UL<<24)
													|(3UL<<26)
													|(3UL<<28));			// Pin0.16-0.22, 0.27-0.30
	LPC_PINCON->PINSEL3 &= ~((3UL<< 4)
													|(3UL<< 6)
													|(3UL<< 8)
													|(3UL<<10)
													|(3UL<<12)
													|(3UL<<14)
													|(3UL<<16)
													|(3UL<<18)
													|(3UL<<20)
													|(3UL<<22)
													|(3UL<<24)
													|(3UL<<26));			// Pin1.18-1.29
	LPC_PINCON->PINSEL4 &= ~((3UL<< 0)
													|(3UL<< 2)
													|(3UL<< 4)
													|(3UL<< 6)
													|(3UL<< 8)
													|(3UL<<10)
													|(3UL<<12)
													|(3UL<<14)
													|(3UL<<16)
													|(3UL<<18)
													|(3UL<<22)
													|(3UL<<24)
													|(3UL<<26));			// Pin2.0-2.9, 2.11-2.13
	LPC_PINCON->PINSEL7 &= ~((3UL<<18)
													|(3UL<<20));			// Pin3.25-3.26
	LPC_PINCON->PINSEL9 &= ~((3UL<<24)
													|(3UL<<26));			// Pin4.28-4.29
	
	// set GPIO direction
	LPC_GPIO0->FIODIR   |= 0x787F8C03;
	LPC_GPIO1->FIODIR   |= 0x3FFC0000;
	LPC_GPIO2->FIODIR   |= 0x00003BFF;
	LPC_GPIO3->FIODIR   |= 0x06000000;
	LPC_GPIO4->FIODIR   |= 0x30000000;
	
	// init GPIO values 
	LPC_GPIO0->FIOPIN   &= ~((1<<10)					// VideoChn
													|(1<<16)					// CX20707_RST
													|(1<<17)					// AD1L
													|(1<<19)					// AUDI-CS1-B
													|(1<<20)					// AUDI-CS1-C
													|(1<<21)					// AUDI-CS2-B
													|(1<<22)					// AUDI-CS2-C
													|(1<<27));					// AUDI-CS1-A
	rst20707_hi;
	VideoChn0;
	LPC_GPIO1->FIOPIN   &= ~((1<<24)					// SK020-1
													|(1<<25)					// SK020-2
													|(1<<27)					// VIDEO-RELAY-CTL
													|(1<<29));				// enADSEL1
	enADSEL1;
	LPC_GPIO2->FIOPIN   &= ~((1<< 2)					// AD2L
													|(1<< 3)					// enADSEL2
													|(1<<11)					// AUDI-CS4-A
													|(1<<12)					// AUDI-CS4-B
													|(1<<13));				// AUDI-CS4-C
	LPC_GPIO3->FIOPIN   &= ~((1<<25)					// AUDI-CS3-A
													|(1<<26));				// AUDI-CS3-B
	LPC_GPIO4->FIOPIN   &= ~((1<<28)					// AUDI-CS3-C
													|(1<<29));				// AUDI-CS2-A
	for(i=0;i<12;i++)
		ClosePort(i+1);
	disADSEL2;
}

/*----------------------------------------------------------------------------
  Here defined the control functions
 *----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*
-- Function name:		OpenPort
-- Descriptions:		open aim port
-- parameters:			port
-- Returned value:	None
-----------------------------------------------------------------------------*/
void OpenPort (uint32_t port) {
	int i;
	
	if (video) {
		if ((port>=1 && port<=3) || (port>=10 && port <=12))
			VideoChn0;
		else
			VideoChn1;
		for (i=0; i<25000; i++);
		enVideo;
	}
	switch(port) {
		case 1:
			LCD_DATA0_en;				// port1: 0 and 12
			LCD_DATA12_en;
			break;
		case 2:
			LCD_DATA1_en;
			LCD_DATA13_en;
			break;
		case 3:
			LCD_DATA2_en;
			LCD_DATA14_en;
			break;
		case 4:
			LCD_DATA3_en;
			LCD_DATA15_en;
			break;
		case 5:
			LCD_DATA4_en;
			LCD_DATA16_en;
			break;
		case 6:
			LCD_DATA5_en;
			LCD_DATA17_en;
			break;
		case 7:
			LCD_DATA6_en;
			LCD_DATA18_en;
			break;
		case 8:
			LCD_DATA7_en;
			LCD_DATA19_en;
			break;
		case 9:
			LCD_DATA8_en;
			LCD_DATA20_en;
			break;
		case 10:
			LCD_DATA9_en;
			LCD_DATA21_en;
			break;
		case 11:
			LCD_DATA10_en;
			LCD_DATA22_en;
			break;
		case 12:
			LCD_DATA11_en;
			LCD_DATA23_en;
			break;
		default:
			break;
	}
	ringptr = 0;
	return;
}

/*----------------------------------------------------------------------------*
-- Function name:		ClosePort
-- Descriptions:		close aim port
-- parameters:			port
-- Returned value:	None
-----------------------------------------------------------------------------*/
void ClosePort (uint32_t port) {
	int i;
	
	if ((!(EMERG1 & (1<<port))) && (!(EMERG2 & (1<<port)))) {
		if (video) {
			disVideo;
			for (i=0; i<25000; i++);
			VideoChn0;
		}
		switch(port) {
			case 1:
				LCD_DATA0_dis;				// port1: 0 and 12
				LCD_DATA12_dis;
				break;
			case 2:
				LCD_DATA1_dis;
				LCD_DATA13_dis;
				break;
			case 3:
				LCD_DATA2_dis;
				LCD_DATA14_dis;
				break;
			case 4:
				LCD_DATA3_dis;
				LCD_DATA15_dis;
				break;
			case 5:
				LCD_DATA4_dis;
				LCD_DATA16_dis;
				break;
			case 6:
				LCD_DATA5_dis;
				LCD_DATA17_dis;
				break;
			case 7:
				LCD_DATA6_dis;
				LCD_DATA18_dis;
				break;
			case 8:
				LCD_DATA7_dis;
				LCD_DATA19_dis;
				break;
			case 9:
				LCD_DATA8_dis;
				LCD_DATA20_dis;
				break;
			case 10:
				LCD_DATA9_dis;
				LCD_DATA21_dis;
				break;
			case 11:
				LCD_DATA10_dis;
				LCD_DATA22_dis;
				break;
			case 12:
				LCD_DATA11_dis;
				LCD_DATA23_dis;
				break;
			default:
				break;
		}
		video = 1;
	}
	else {
		disVideo;
		for (i=0; i<25000; i++);
		VideoChn0;
		AlarmStart(port);
	}
	return;
}

/*----------------------------------------------------------------------------*
-- Function name:		AlarmStart
-- Descriptions:		start alarm play for aim port
-- parameters:			port
-- Returned value:	None
-----------------------------------------------------------------------------*/
void AlarmStart (uint32_t port) {
	switch(port) {
		case 1:
			AUD1_ALM_en;
			LCD_DATA0_en;
			LCD_DATA12_en;
			break;
		case 2:
			AUD2_ALM_en;
			LCD_DATA1_en;
			LCD_DATA13_en;
			break;
		case 3:
			AUD3_ALM_en;
			LCD_DATA2_en;
			LCD_DATA14_en;
			break;
		case 4:
			AUD4_ALM_en;
			LCD_DATA3_en;
			LCD_DATA15_en;
			break;
		case 5:
			AUD5_ALM_en;
			LCD_DATA4_en;
			LCD_DATA16_en;
			break;
		case 6:
			AUD6_ALM_en;
			LCD_DATA5_en;
			LCD_DATA17_en;
			break;
		case 7:
			AUD7_ALM_en;
			LCD_DATA6_en;
			LCD_DATA18_en;
			break;
		case 8:
			AUD8_ALM_en;
			LCD_DATA7_en;
			LCD_DATA19_en;
			break;
		case 9:
			AUD9_ALM_en;
			LCD_DATA8_en;
			LCD_DATA20_en;
			break;
		case 10:
			AUD10_ALM_en;
			LCD_DATA9_en;
			LCD_DATA21_en;
			break;
		case 11:
			AUD11_ALM_en;
			LCD_DATA10_en;
			LCD_DATA22_en;
			break;
		case 12:
			AUD12_ALM_en;
			LCD_DATA11_en;
			LCD_DATA23_en;
			break;
	}
	return;
}

/*----------------------------------------------------------------------------*
-- Function name:		AlarmStop
-- Descriptions:		stop alarm play for aim port
-- parameters:			port
-- Returned value:	None
-----------------------------------------------------------------------------*/
void AlarmStop (uint32_t port) {
	switch(port) {
		case 1:
			AUD1_ALM_dis;
			LCD_DATA0_dis;
			LCD_DATA12_dis;
			break;
		case 2:
			AUD2_ALM_dis;
			LCD_DATA1_dis;
			LCD_DATA13_dis;
			break;
		case 3:
			AUD3_ALM_dis;
			LCD_DATA2_dis;
			LCD_DATA14_dis;
			break;
		case 4:
			AUD4_ALM_dis;
			LCD_DATA3_dis;
			LCD_DATA15_dis;
			break;
		case 5:
			AUD5_ALM_dis;
			LCD_DATA4_dis;
			LCD_DATA16_dis;
			break;
		case 6:
			AUD6_ALM_dis;
			LCD_DATA5_dis;
			LCD_DATA17_dis;
			break;
		case 7:
			AUD7_ALM_dis;
			LCD_DATA6_dis;
			LCD_DATA18_dis;
			break;
		case 8:
			AUD8_ALM_dis;
			LCD_DATA7_dis;
			LCD_DATA19_dis;
			break;
		case 9:
			AUD9_ALM_dis;
			LCD_DATA8_dis;
			LCD_DATA20_dis;
			break;
		case 10:
			AUD10_ALM_dis;
			LCD_DATA9_dis;
			LCD_DATA21_dis;
			break;
		case 11:
			AUD11_ALM_dis;
			LCD_DATA10_dis;
			LCD_DATA22_dis;
			break;
		case 12:
			AUD12_ALM_dis;
			LCD_DATA11_dis;
			LCD_DATA23_dis;
			break;
	}
	return;
}

/*----------------------------------------------------------------------------*
-- Function name:		AlarmInit
-- Descriptions:		Initialize ADC
-- parameters:			None
-- Returned value:	None
-----------------------------------------------------------------------------*/
void AlarmInit (void) {
	uint32_t i;
	
	SK020_SEL_hi;
	for(i=0; i<2500; i++);
	SK020_SEL_lo;
		for(i=0; i<2500; i++);
	SK020_SEL_hi;
	for(i=0; i<2500; i++);
	SK020_SEL_lo;
		for(i=0; i<2500; i++);
	SK020_SEL_hi;
	for(i=0; i<2500; i++);
	SK020_SEL_lo;
	
	return;
}

/*------------------------------------------------------------------------------
--                            End Of File
------------------------------------------------------------------------------*/
