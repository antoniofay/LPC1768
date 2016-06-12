/*----------------------------------------------------------------------------
 *      Skuo LPC1768 12 Ports Decoder
 *----------------------------------------------------------------------------
 *      Name:    gpio.h
 *      Purpose: 12 Ports decoder demo@Fei,Hui
 *----------------------------------------------------------------------------
 *      This code is use the RealView Run-Time Library.
 *      2013-12.05
 *---------------------------------------------------------------------------*/

#ifndef __GPIO_H
#define __GPIO_H

/*-------------------------PORT DEFININITION ---------------------------------*/
/* AUDI-CS1-A/B/C: 0.27 0.19 0.20
* AUDI-CS2-A/B/C: 4.29 0.21 0.22
* AUDI-CS3-A/B/C: 3.25 3.26 4.28
* AUDI-CS4-A/B/C: 2.11 2.12 2.13
* LCD_DATA0-11:  P2.1  P2.0  P1.28 P1.26 P0.15 P0.11 P1.18 P1.19 P1.20 P1.21 P1.22 P1.23
* LCD_DATA12-23: P0.28 P0.29 P0.30 P0.0  P0.1  P2.4  P2.5  P2.6  P2.7  P2.8  P2.9  P0.18
* VIDEO_RELAY_CNTL1/2: P0.10 P1.27
* SK020-TG1/2: P1.24 P1.25
* AUDI-CNTL1-A: P1.29
* AUDI-CNTL1-INH: P0.17
* UI_SW1: P2.2
* CMOS_PWR_DIS: P2.3
* CX20707RESET: P0.16
*----------------------------------------------------------------------------*/
#define		INVERSE
// Audio thread control
#ifdef	INVERSE
#define		LCD_DATA0_dis		(LPC_GPIO2->FIOPIN|=(1<<1))
#define		LCD_DATA0_en		(LPC_GPIO2->FIOPIN&=~(1<<1))

#define		LCD_DATA1_dis		(LPC_GPIO2->FIOPIN|=(1<<0))
#define		LCD_DATA1_en		(LPC_GPIO2->FIOPIN&=~(1<<0))

#define		LCD_DATA2_dis		(LPC_GPIO1->FIOPIN|=(1<<28))
#define		LCD_DATA2_en		(LPC_GPIO1->FIOPIN&=~(1<<28))

#define		LCD_DATA3_dis		(LPC_GPIO1->FIOPIN|=(1<<26))
#define		LCD_DATA3_en		(LPC_GPIO1->FIOPIN&=~(1<<26))

#define		LCD_DATA4_dis		(LPC_GPIO0->FIOPIN|=(1<<15))
#define		LCD_DATA4_en		(LPC_GPIO0->FIOPIN&=~(1<<15))

#define		LCD_DATA5_dis		(LPC_GPIO0->FIOPIN|=(1<<11))
#define		LCD_DATA5_en		(LPC_GPIO0->FIOPIN&=~(1<<11))

#define		LCD_DATA6_dis		(LPC_GPIO1->FIOPIN|=(1<<18))
#define		LCD_DATA6_en		(LPC_GPIO1->FIOPIN&=~(1<<18))

#define		LCD_DATA7_dis		(LPC_GPIO1->FIOPIN|=(1<<19))
#define		LCD_DATA7_en		(LPC_GPIO1->FIOPIN&=~(1<<19))

#define		LCD_DATA8_dis		(LPC_GPIO1->FIOPIN|=(1<<20))
#define		LCD_DATA8_en		(LPC_GPIO1->FIOPIN&=~(1<<20))

#define		LCD_DATA9_dis		(LPC_GPIO1->FIOPIN|=(1<<21))
#define		LCD_DATA9_en		(LPC_GPIO1->FIOPIN&=~(1<<21))

#define		LCD_DATA10_dis	(LPC_GPIO1->FIOPIN|=(1<<22))
#define		LCD_DATA10_en		(LPC_GPIO1->FIOPIN&=~(1<<22))

#define		LCD_DATA11_dis	(LPC_GPIO1->FIOPIN|=(1<<23))
#define		LCD_DATA11_en		(LPC_GPIO1->FIOPIN&=~(1<<23))

#define		LCD_DATA12_dis	(LPC_GPIO0->FIOPIN|=(1<<28))
#define		LCD_DATA12_en		(LPC_GPIO0->FIOPIN&=~(1<<28))

#define		LCD_DATA13_dis	(LPC_GPIO0->FIOPIN|=(1<<29))
#define		LCD_DATA13_en		(LPC_GPIO0->FIOPIN&=~(1<<29))

#define		LCD_DATA14_dis	(LPC_GPIO0->FIOPIN|=(1<<30))
#define		LCD_DATA14_en		(LPC_GPIO0->FIOPIN&=~(1<<30))

#define		LCD_DATA15_dis	(LPC_GPIO0->FIOPIN|=(1<<0))
#define		LCD_DATA15_en		(LPC_GPIO0->FIOPIN&=~(1<<0))

#define		LCD_DATA16_dis	(LPC_GPIO0->FIOPIN|=(1<<1))
#define		LCD_DATA16_en		(LPC_GPIO0->FIOPIN&=~(1<<1))

#define		LCD_DATA17_dis	(LPC_GPIO2->FIOPIN|=(1<<4))
#define		LCD_DATA17_en		(LPC_GPIO2->FIOPIN&=~(1<<4))

#define		LCD_DATA18_dis	(LPC_GPIO2->FIOPIN|=(1<<5))
#define		LCD_DATA18_en		(LPC_GPIO2->FIOPIN&=~(1<<5))

#define		LCD_DATA19_dis	(LPC_GPIO2->FIOPIN|=(1<<6))
#define		LCD_DATA19_en		(LPC_GPIO2->FIOPIN&=~(1<<6))

#define		LCD_DATA20_dis	(LPC_GPIO2->FIOPIN|=(1<<7))
#define		LCD_DATA20_en		(LPC_GPIO2->FIOPIN&=~(1<<7))

#define		LCD_DATA21_dis	(LPC_GPIO2->FIOPIN|=(1<<8))
#define		LCD_DATA21_en		(LPC_GPIO2->FIOPIN&=~(1<<8))

#define		LCD_DATA22_dis	(LPC_GPIO2->FIOPIN|=(1<<9))
#define		LCD_DATA22_en		(LPC_GPIO2->FIOPIN&=~(1<<9))

#define		LCD_DATA23_dis	(LPC_GPIO0->FIOPIN|=(1<<18))
#define		LCD_DATA23_en		(LPC_GPIO0->FIOPIN&=~(1<<18))

#else

#define		LCD_DATA0_en		(LPC_GPIO2->FIOPIN|=(1<<1))
#define		LCD_DATA0_dis		(LPC_GPIO2->FIOPIN&=~(1<<1))

#define		LCD_DATA1_en		(LPC_GPIO2->FIOPIN|=(1<<0))
#define		LCD_DATA1_dis		(LPC_GPIO2->FIOPIN&=~(1<<0))

#define		LCD_DATA2_en		(LPC_GPIO1->FIOPIN|=(1<<28))
#define		LCD_DATA2_dis		(LPC_GPIO1->FIOPIN&=~(1<<28))

#define		LCD_DATA3_en		(LPC_GPIO1->FIOPIN|=(1<<26))
#define		LCD_DATA3_dis		(LPC_GPIO1->FIOPIN&=~(1<<26))

#define		LCD_DATA4_en		(LPC_GPIO0->FIOPIN|=(1<<15))
#define		LCD_DATA4_dis		(LPC_GPIO0->FIOPIN&=~(1<<15))

#define		LCD_DATA5_en		(LPC_GPIO0->FIOPIN|=(1<<11))
#define		LCD_DATA5_dis		(LPC_GPIO0->FIOPIN&=~(1<<11))

#define		LCD_DATA6_en		(LPC_GPIO1->FIOPIN|=(1<<18))
#define		LCD_DATA6_dis		(LPC_GPIO1->FIOPIN&=~(1<<18))

#define		LCD_DATA7_en		(LPC_GPIO1->FIOPIN|=(1<<19))
#define		LCD_DATA7_dis		(LPC_GPIO1->FIOPIN&=~(1<<19))

#define		LCD_DATA8_en		(LPC_GPIO1->FIOPIN|=(1<<20))
#define		LCD_DATA8_dis		(LPC_GPIO1->FIOPIN&=~(1<<20))

#define		LCD_DATA9_en		(LPC_GPIO1->FIOPIN|=(1<<21))
#define		LCD_DATA9_dis		(LPC_GPIO1->FIOPIN&=~(1<<21))

#define		LCD_DATA10_en			(LPC_GPIO1->FIOPIN|=(1<<22))
#define		LCD_DATA10_dis		(LPC_GPIO1->FIOPIN&=~(1<<22))

#define		LCD_DATA11_en			(LPC_GPIO1->FIOPIN|=(1<<23))
#define		LCD_DATA11_dis		(LPC_GPIO1->FIOPIN&=~(1<<23))

#define		LCD_DATA12_en			(LPC_GPIO0->FIOPIN|=(1<<28))
#define		LCD_DATA12_dis		(LPC_GPIO0->FIOPIN&=~(1<<28))

#define		LCD_DATA13_en			(LPC_GPIO0->FIOPIN|=(1<<29))
#define		LCD_DATA13_dis		(LPC_GPIO0->FIOPIN&=~(1<<29))

#define		LCD_DATA14_en			(LPC_GPIO0->FIOPIN|=(1<<30))
#define		LCD_DATA14_dis		(LPC_GPIO0->FIOPIN&=~(1<<30))

#define		LCD_DATA15_en			(LPC_GPIO0->FIOPIN|=(1<<0))
#define		LCD_DATA15_dis		(LPC_GPIO0->FIOPIN&=~(1<<0))

#define		LCD_DATA16_en			(LPC_GPIO0->FIOPIN|=(1<<1))
#define		LCD_DATA16_dis		(LPC_GPIO0->FIOPIN&=~(1<<1))

#define		LCD_DATA17_en			(LPC_GPIO2->FIOPIN|=(1<<4))
#define		LCD_DATA17_dis		(LPC_GPIO2->FIOPIN&=~(1<<4))

#define		LCD_DATA18_en			(LPC_GPIO2->FIOPIN|=(1<<5))
#define		LCD_DATA18_dis		(LPC_GPIO2->FIOPIN&=~(1<<5))

#define		LCD_DATA19_en			(LPC_GPIO2->FIOPIN|=(1<<6))
#define		LCD_DATA19_dis		(LPC_GPIO2->FIOPIN&=~(1<<6))

#define		LCD_DATA20_en			(LPC_GPIO2->FIOPIN|=(1<<7))
#define		LCD_DATA20_dis		(LPC_GPIO2->FIOPIN&=~(1<<7))

#define		LCD_DATA21_en			(LPC_GPIO2->FIOPIN|=(1<<8))
#define		LCD_DATA21_dis		(LPC_GPIO2->FIOPIN&=~(1<<8))

#define		LCD_DATA22_en			(LPC_GPIO2->FIOPIN|=(1<<9))
#define		LCD_DATA22_dis		(LPC_GPIO2->FIOPIN&=~(1<<9))

#define		LCD_DATA23_en			(LPC_GPIO0->FIOPIN|=(1<<18))
#define		LCD_DATA23_dis		(LPC_GPIO0->FIOPIN&=~(1<<18))

#endif

// Alarm thread control
#define		AUD1_ALM_en		((LPC_GPIO2->FIOPIN)|=(1<<11))
#define		AUD1_ALM_dis	((LPC_GPIO2->FIOPIN)&=~(1<<11))

#define		AUD2_ALM_en		((LPC_GPIO2->FIOPIN)|=(1<<12))
#define		AUD2_ALM_dis	((LPC_GPIO2->FIOPIN)&=~(1<<12))

#define		AUD3_ALM_en		((LPC_GPIO2->FIOPIN)|=(1<<13))
#define		AUD3_ALM_dis	((LPC_GPIO2->FIOPIN)&=~(1<<13))

#define		AUD4_ALM_en		((LPC_GPIO3->FIOPIN)|=(1<<25))
#define		AUD4_ALM_dis	((LPC_GPIO3->FIOPIN)&=~(1<<25))

#define		AUD5_ALM_en		((LPC_GPIO3->FIOPIN)|=(1<<26))
#define		AUD5_ALM_dis	((LPC_GPIO3->FIOPIN)&=~(1<<26))

#define		AUD6_ALM_en		((LPC_GPIO4->FIOPIN)|=(1<<28))
#define		AUD6_ALM_dis	((LPC_GPIO4->FIOPIN)&=~(1<<28))

#define		AUD7_ALM_en		((LPC_GPIO4->FIOPIN)|=(1<<29))
#define		AUD7_ALM_dis	((LPC_GPIO4->FIOPIN)&=~(1<<29))

#define		AUD8_ALM_en		((LPC_GPIO0->FIOPIN)|=(1<<21))
#define		AUD8_ALM_dis	((LPC_GPIO0->FIOPIN)&=~(1<<21))

#define		AUD9_ALM_en		((LPC_GPIO0->FIOPIN)|=(1<<22))
#define		AUD9_ALM_dis	((LPC_GPIO0->FIOPIN)&=~(1<<22))

#define		AUD10_ALM_en	((LPC_GPIO0->FIOPIN)|=(1<<27))
#define		AUD10_ALM_dis	((LPC_GPIO0->FIOPIN)&=~(1<<27))

#define		AUD11_ALM_en	((LPC_GPIO0->FIOPIN)|=(1<<19))
#define		AUD11_ALM_dis	((LPC_GPIO0->FIOPIN)&=~(1<<19))

#define		AUD12_ALM_en	((LPC_GPIO0->FIOPIN)|=(1<<20))
#define		AUD12_ALM_dis	((LPC_GPIO0->FIOPIN)&=~(1<<20))

/*-------------------------MACRO FUNCTIONS -----------------------------------*/
#define		VideoChn1		((LPC_GPIO0->FIOPIN)|=(1<<10))
#define		VideoChn0		((LPC_GPIO0->FIOPIN)&=~(1<<10))
#define		enVideo			((LPC_GPIO1->FIOPIN)|=(1<<27))
#define		disVideo		((LPC_GPIO1->FIOPIN)&=~(1<<27))

// SK020 control
#define		SK020_RST_hi	((LPC_GPIO1->FIOPIN)|=(1<<25))
#define		SK020_RST_lo	((LPC_GPIO1->FIOPIN)&=~(1<<25))
#define		SK020_RST			SK020_RST_hi;\
												for(i=0; i<2500; i++);\
												SK020_RST_lo;\
												for(i=0; i<1250000; i++)
#define		SK020_SEL_hi	((LPC_GPIO1->FIOPIN)|=(1<<24))
#define		SK020_SEL_lo	((LPC_GPIO1->FIOPIN)&=~(1<<24))
#define		SK020_SEL			SK020_SEL_hi;\
												for(i=0; i<2500; i++);\
												SK020_SEL_lo;\

// CX20707 reset
#define		rst20707_lo ((LPC_GPIO0->FIOPIN)&=~(1<<16))
#define		rst20707_hi	((LPC_GPIO0->FIOPIN)|=(1<<16))

// 4053 selection
#define		disADSEL1		(LPC_GPIO0->FIOPIN|=(1<<17))
#define		enADSEL1		(LPC_GPIO0->FIOPIN&=~(1<<17))
#define		disADSEL2		(LPC_GPIO2->FIOPIN|=(1<<3))
#define		enADSEL2		(LPC_GPIO2->FIOPIN&=~(1<<3))
// 4053 hi/low switch control
#define		AD1L				(LPC_GPIO1->FIOPIN&=~(1<<29))
#define		AD1H				(LPC_GPIO1->FIOPIN|=(1<<29))
#define		AD2L				(LPC_GPIO2->FIOPIN&=~(1<<2))
#define		AD2H				(LPC_GPIO2->FIOPIN|=(1<<2))

extern unsigned int ringptr;

extern void GPIOInit	(void);
extern void OpenPort	(uint32_t port);
extern void ClosePort	(uint32_t port);
extern void AlarmInit (void);
extern void AlarmStart(uint32_t port);
extern void AlarmStop	(uint32_t port);

#endif

/*------------------------------------------------------------------------------
--                            End Of File
------------------------------------------------------------------------------*/
