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
extern uint8_t ComState;
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
	LPC_GPIO0->FIOPIN		 =  0xF7E1FBFD;
	LPC_GPIO1->FIOPIN		 =  0xD4FFFFFF;
	LPC_GPIO2->FIOPIN		 =  0xFFFFFFFF;
	LPC_GPIO3->FIOPIN		 =  0xFFFFFFFF;
	LPC_GPIO4->FIOPIN		 =  0xFFFFFC03;
	LPC_GPIO0->FIOPIN   &= ~((1<< 1)					// LCD_DATA16
													|(1<<10)					// WAN_HOST_WAKE
													|(1<<17)					// AD1L
													|(1<<18)					// LCD_DATA23
													|(1<<19)					// WAN_NDISABLE
													|(1<<20)					// GP_A1
													|(1<<27));				// GP_A0
	rst20707_hi;
	LPC_GPIO1->FIOPIN   &= ~((1<<24)					// SK020-1
													|(1<<25)					// SK020-2
													|(1<<27)					// VIDEO-RELAY-CTL
													|(1<<29));				// enADSEL1*/
	enADSEL1;
	LPC_GPIO2->FIOPIN   &= ~((1<< 2)					// AD2L
													|(1<< 3)					// enADSEL2
													|(1<< 4)					// LCD_DATA17
													|(1<< 5)					// LCD_DATA18
													|(1<< 6)					// LCD_DATA19
													|(1<< 7)					// LCD_DATA20
													|(1<< 8)					// LCD_DATA21
													|(1<< 9));				// LCD_DATA22
	for(i=0;i<12;i++)
		ClosePort(i+1);
	disADSEL2;
}

/*----------------------------------------------------------------------------
  Here defined the control functions
 *----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*
-- Function name:		OpenPort
-- Descriptions:		open relative port
-- parameters:			port
-- Returned value:	None
-----------------------------------------------------------------------------*/
void OpenPort (uint32_t port) {
	
	if (video) {
		enVideo;
	}
	if (ComState == 6) {
		switch(port) {
			case 1:
				CHNL1_en_na;
				break;
			case 2:
				CHNL2_en_na;
				break;
			case 3:
				CHNL3_en_na;
				break;
			case 4:
				CHNL4_en_na;
				break;
			case 5:
				CHNL5_en_na;
				break;
			case 6:
				CHNL6_en_na;
				break;
			case 7:
				CHNL7_en_na;
				break;
			case 8:
				CHNL8_en_na;
				break;
			case 9:
				CHNL9_en_na;
				break;
			case 10:
				CHNL10_en_na;
				break;
			case 11:
				CHNL11_en_na;
				break;
			case 12:
				CHNL12_en_na;
				break;
			default:
				break;
		}
	}
	else {
		switch(port) {
			case 1:
				CHNL1_en;
				break;
			case 2:
				CHNL2_en;
				break;
			case 3:
				CHNL3_en;
				break;
			case 4:
				CHNL4_en;
				break;
			case 5:
				CHNL5_en;
				break;
			case 6:
				CHNL6_en;
				break;
			case 7:
				CHNL7_en;
				break;
			case 8:
				CHNL8_en;
				break;
			case 9:
				CHNL9_en;
				break;
			case 10:
				CHNL10_en;
				break;
			case 11:
				CHNL11_en;
				break;
			case 12:
				CHNL12_en;
				break;
			default:
				break;
		}
	}
	ringptr = 0;
	return;
}

/*----------------------------------------------------------------------------*
-- Function name:		ClosePort
-- Descriptions:		close relative port
-- parameters:			port
-- Returned value:	None
-----------------------------------------------------------------------------*/
void ClosePort (uint32_t port) {
	
	if ((!(EMERG1 & (1<<port))) && (!(EMERG2 & (1<<port)))) {
		if (video) {
			disVideo;
		}
		switch(port) {
			case 1:
				CHNL1_dis;
				break;
			case 2:
				CHNL2_dis;
				break;
			case 3:
				CHNL3_dis;
				break;
			case 4:
				CHNL4_dis;
				break;
			case 5:
				CHNL5_dis;
				break;
			case 6:
				CHNL6_dis;
				break;
			case 7:
				CHNL7_dis;
				break;
			case 8:
				CHNL8_dis;
				break;
			case 9:
				CHNL9_dis;
				break;
			case 10:
				CHNL10_dis;
				break;
			case 11:
				CHNL11_dis;
				break;
			case 12:
				CHNL12_dis;
				break;
			default:
				break;
		}
		video = 1;
	}
	else {
		disVideo;
		AlarmStart(port);
	}
	return;
}

/*----------------------------------------------------------------------------*
-- Function name:		AlarmStart
-- Descriptions:		start alarm play for relative port
-- parameters:			port
-- Returned value:	None
-----------------------------------------------------------------------------*/
void AlarmStart (uint32_t port) {
	int i;
	
	switch(port) {
		case 1:
			AUD1_ALM_en;
			//for(i=0;i<25000;i++);
			//CHNL1_en;
			break;
		case 2:
			AUD2_ALM_en;
			//for(i=0;i<25000;i++);
			//CHNL2_en;
			break;
		case 3:
			AUD3_ALM_en;
			//for(i=0;i<25000;i++);
			//CHNL3_en;
			break;
		case 4:
			AUD4_ALM_en;
			//for(i=0;i<25000;i++);
			//CHNL4_en;
			break;
		case 5:
			AUD5_ALM_en;
			//for(i=0;i<25000;i++);
			//CHNL5_en;
			break;
		case 6:
			AUD6_ALM_en;
			//for(i=0;i<25000;i++);
			//CHNL6_en;
			break;
		case 7:
			AUD7_ALM_en;
			//for(i=0;i<25000;i++);
			//CHNL7_en;
			break;
		case 8:
			AUD8_ALM_en;
			//for(i=0;i<25000;i++);
			//CHNL8_en;
			break;
		case 9:
			AUD9_ALM_en;
			//for(i=0;i<25000;i++);
			//CHNL9_en;
			break;
		case 10:
			AUD10_ALM_en;
			//for(i=0;i<25000;i++);
			//CHNL10_en;
			break;
		case 11:
			AUD11_ALM_en;
			//for(i=0;i<25000;i++);
			//CHNL11_en;
			break;
		case 12:
			AUD12_ALM_en;
			//for(i=0;i<25000;i++);
			//CHNL12_en;
			break;
	}
	return;
}

/*----------------------------------------------------------------------------*
-- Function name:		AlarmStop
-- Descriptions:		stop alarm play for relative port
-- parameters:			port
-- Returned value:	None
-----------------------------------------------------------------------------*/
void AlarmStop (uint32_t port) {
	int i;
	
	switch(port) {
		case 1:
			AUD1_ALM_dis;
			//for(i=0;i<25000;i++);
			//CHNL1_dis;
			break;
		case 2:
			AUD2_ALM_dis;
			//for(i=0;i<25000;i++);
			//CHNL2_dis;
			break;
		case 3:
			AUD3_ALM_dis;
			//for(i=0;i<25000;i++);
			//CHNL3_dis;
			break;
		case 4:
			AUD4_ALM_dis;
			//for(i=0;i<25000;i++);
			//CHNL4_dis;
			break;
		case 5:
			AUD5_ALM_dis;
			//for(i=0;i<25000;i++);
			//CHNL5_dis;
			break;
		case 6:
			AUD6_ALM_dis;
			//for(i=0;i<25000;i++);
			//CHNL6_dis;
			break;
		case 7:
			AUD7_ALM_dis;
			//for(i=0;i<25000;i++);
			//CHNL7_dis;
			break;
		case 8:
			AUD8_ALM_dis;
			//for(i=0;i<25000;i++);
			//CHNL8_dis;
			break;
		case 9:
			AUD9_ALM_dis;
			//for(i=0;i<25000;i++);
			//CHNL9_dis;
			break;
		case 10:
			//CHNL10_dis;
			//for(i=0;i<25000;i++);
			AUD10_ALM_dis;
			break;
		case 11:
			AUD11_ALM_dis;
			//for(i=0;i<25000;i++);
			//CHNL11_dis;
			break;
		case 12:
			AUD12_ALM_dis;
			//for(i=0;i<25000;i++);
			//CHNL12_dis;
			break;
	}
	return;
}

/*------------------------------------------------------------------------------
--                            End Of File
------------------------------------------------------------------------------*/
