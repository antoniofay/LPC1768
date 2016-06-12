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
/*POWER:
*    LCD_DATA12-15: P0.28(A0) P0.29(A1) P0.30(A2) P0.0(NE)
* VIDEO:
*    MS_SD_CLK 4IN1_PWR_EN CF_ADDR2: P2.11(S1) P2.12(S0) P2.13(NE)
*    CF_ADDR1_XD_ALE CF_ADDR0_XD_CLE REMOTE_IN: P3.25 P3.26 P4.28
*    XD_NCD XD_NWP SD_NWP: P4.29 P0.21 P0.22
* AUDIO:
*    LCD_DATA16-23: P0.1 P2.4 P2.5 P2.6 P2.7 P2.8 P2.9 P0.18 P0.10 P0.27 P0.19 P0.20
*    WAN_HOST_WAKE GP_A0 GP_A1 WAN_NDISABLE: P0.10 P0.27 P0.19 P0.20
* VIDEO_RELAY: P1.27
* SK020-TG1/2: P1.24 P1.25
* AUDI-CNTL1-A: P1.29
* AUDI-CNTL1-INH: P0.17
* UI_SW1: P2.2
* CMOS_PWR_DIS: P2.3
* CX20707RESET: P0.16
*----------------------------------------------------------------------------*/
// Channel control
#define	CHNL1_en			(LPC_GPIO2->FIOPIN)&=~((1<< 1)\
																						|(1<<11)\
																						|(1<<12)\
																						|(1<<13));\
											(LPC_GPIO0->FIOPIN)&=~((1<<28)\
																						|(1<<29)\
																						|(1<<30)\
																						|(1<< 0))
#define	CHNL1_dis			(LPC_GPIO2->FIOPIN)|= ((1<< 1)\
																						|(1<<11)\
																						|(1<<12)\
																						|(1<<13));\
											(LPC_GPIO0->FIOPIN)|= ((1<<28)\
																						|(1<<29)\
																						|(1<<30)\
																						|(1<< 0))

#define	CHNL2_en			(LPC_GPIO2->FIOPIN)&=~((1<< 0)\
																						|(1<<11)\
																						|(1<<13));\
											(LPC_GPIO0->FIOPIN)&=~((1<<29)\
																						|(1<<30)\
																						|(1<< 0))
#define	CHNL2_dis			(LPC_GPIO2->FIOPIN)|= ((1<< 0)\
																						|(1<<11)\
																						|(1<<12)\
																						|(1<<13));\
											(LPC_GPIO0->FIOPIN)|= ((1<<28)\
																						|(1<<29)\
																						|(1<<30)\
																						|(1<< 0))

#define	CHNL3_en			(LPC_GPIO1->FIOPIN)&=~(1<<28);\
											(LPC_GPIO2->FIOPIN)&=~((1<<12)\
																						|(1<<13));\
											(LPC_GPIO0->FIOPIN)&=~((1<<28)\
																						|(1<<30)\
																						|(1<< 0))
#define	CHNL3_dis			(LPC_GPIO1->FIOPIN)|= (1<<28);\
											(LPC_GPIO2->FIOPIN)|= ((1<<11)\
																						|(1<<12)\
																						|(1<<13));\
											(LPC_GPIO0->FIOPIN)|= ((1<<28)\
																						|(1<<29)\
																						|(1<<30)\
																						|(1<< 0))
											
#define	CHNL4_en			(LPC_GPIO1->FIOPIN)&=~(1<<26);\
											(LPC_GPIO2->FIOPIN)&=~(1<<13);\
											(LPC_GPIO0->FIOPIN)&=~((1<<30)\
																						|(1<< 0))
#define	CHNL4_dis			(LPC_GPIO1->FIOPIN)|= (1<<26);\
											(LPC_GPIO2->FIOPIN)|= ((1<<11)\
																						|(1<<12)\
																						|(1<<13));\
											(LPC_GPIO0->FIOPIN)|= ((1<<28)\
																						|(1<<29)\
																						|(1<<30)\
																						|(1<< 0))
											
#define	CHNL5_en			(LPC_GPIO3->FIOPIN)&=~((1<<25)\
																						|(1<<26));\
											(LPC_GPIO4->FIOPIN)&=~(1<<28);\
											(LPC_GPIO0->FIOPIN)&=~((1<<15)\
																						|(1<<28)\
																						|(1<<29)\
																						|(1<< 0))
#define	CHNL5_dis			(LPC_GPIO3->FIOPIN)|= ((1<<25)\
																						|(1<<26));\
											(LPC_GPIO4->FIOPIN)|= (1<<28);\
											(LPC_GPIO0->FIOPIN)|= ((1<<15)\
																						|(1<<28)\
																						|(1<<29)\
																						|(1<<30)\
																						|(1<< 0))
											
#define	CHNL6_en			(LPC_GPIO3->FIOPIN)&=~(1<<25);\
											(LPC_GPIO4->FIOPIN)&=~(1<<28);\
											(LPC_GPIO0->FIOPIN)&=~((1<<11)\
																						|(1<<29)\
																						|(1<< 0))
#define	CHNL6_dis			(LPC_GPIO3->FIOPIN)|= ((1<<25)\
																						|(1<<26));\
											(LPC_GPIO4->FIOPIN)|= (1<<28);\
											(LPC_GPIO0->FIOPIN)|= ((1<<11)\
																						|(1<<28)\
																						|(1<<29)\
																						|(1<<30)\
																						|(1<< 0))
											
#define	CHNL7_en			(LPC_GPIO1->FIOPIN)&=~(1<<18);\
											(LPC_GPIO3->FIOPIN)&=~(1<<26);\
											(LPC_GPIO4->FIOPIN)&=~(1<<28);\
											(LPC_GPIO0->FIOPIN)&=~((1<<28)\
																						|(1<< 0))
#define	CHNL7_dis			(LPC_GPIO1->FIOPIN)|= (1<<18);\
											(LPC_GPIO3->FIOPIN)|= ((1<<25)\
																						|(1<<26));\
											(LPC_GPIO4->FIOPIN)|= (1<<28);\
											(LPC_GPIO0->FIOPIN)|= ((1<<28)\
																						|(1<<29)\
																						|(1<<30)\
																						|(1<< 0))
											
#define	CHNL8_en			(LPC_GPIO1->FIOPIN)&=~(1<<19);\
											(LPC_GPIO4->FIOPIN)&=~(1<<28);\
											(LPC_GPIO0->FIOPIN)&=~(1<< 0)
#define	CHNL8_dis			(LPC_GPIO1->FIOPIN)|= (1<<19);\
											(LPC_GPIO3->FIOPIN)|= ((1<<25)\
																						|(1<<26));\
											(LPC_GPIO4->FIOPIN)|= (1<<28);\
											(LPC_GPIO0->FIOPIN)|= ((1<<28)\
																						|(1<<29)\
																						|(1<<30)\
																						|(1<< 0))
											
#define	CHNL9_en			(LPC_GPIO1->FIOPIN)&=~(1<<20);\
											(LPC_GPIO4->FIOPIN)&=~(1<<29);\
											(LPC_GPIO0->FIOPIN)&=~((1<<21)\
																						|(1<<22)\
																						|(1<<28)\
																						|(1<<29)\
																						|(1<<30))
#define	CHNL9_dis			(LPC_GPIO1->FIOPIN)|= (1<<20);\
											(LPC_GPIO0->FIOPIN)|= ((1<<21)\
																						|(1<<22)\
																						|(1<<28)\
																						|(1<<29)\
																						|(1<<30)\
																						|(1<< 0));\
											(LPC_GPIO4->FIOPIN)|= (1<<29)
											
#define	CHNL10_en			(LPC_GPIO1->FIOPIN)&=~(1<<21);\
											(LPC_GPIO4->FIOPIN)&=~(1<<29);\
											(LPC_GPIO0->FIOPIN)&=~((1<<22)\
																						|(1<<29)\
																						|(1<<30))
#define	CHNL10_dis		(LPC_GPIO1->FIOPIN)|= (1<<21);\
											(LPC_GPIO0->FIOPIN)|= ((1<<21)\
																						|(1<<22)\
																						|(1<<28)\
																						|(1<<29)\
																						|(1<<30)\
																						|(1<< 0));\
											(LPC_GPIO4->FIOPIN)|= (1<<29)
											
#define	CHNL11_en			(LPC_GPIO1->FIOPIN)&=~(1<<22);\
											(LPC_GPIO0->FIOPIN)&=~((1<<21)\
																						|(1<<22)\
																						|(1<<28)\
																						|(1<<30))
#define	CHNL11_dis		(LPC_GPIO1->FIOPIN)|= (1<<22);\
											(LPC_GPIO0->FIOPIN)|= ((1<<21)\
																						|(1<<22)\
																						|(1<<28)\
																						|(1<<29)\
																						|(1<<30)\
																						|(1<< 0));\
											(LPC_GPIO4->FIOPIN)|= (1<<29)
											
#define	CHNL12_en			(LPC_GPIO1->FIOPIN)&=~(1<<23);\
											(LPC_GPIO0->FIOPIN)&=~((1<<22)\
																						|(1<<30))
#define	CHNL12_dis		(LPC_GPIO1->FIOPIN)|= (1<<23);\
											(LPC_GPIO0->FIOPIN)|= ((1<<21)\
																						|(1<<22)\
																						|(1<<28)\
																						|(1<<29)\
																						|(1<<30)\
																						|(1<< 0));\
											(LPC_GPIO4->FIOPIN)|= (1<<29)

// Channel control without audio
#define	CHNL1_en_na		(LPC_GPIO2->FIOPIN)&=~((1<<11)\
																						|(1<<12)\
																						|(1<<13));\
											(LPC_GPIO0->FIOPIN)&=~((1<<28)\
																						|(1<<29)\
																						|(1<<30)\
																						|(1<< 0))

#define	CHNL2_en_na		(LPC_GPIO2->FIOPIN)&=~((1<<11)\
																						|(1<<13));\
											(LPC_GPIO0->FIOPIN)&=~((1<<29)\
																						|(1<<30)\
																						|(1<< 0))

#define	CHNL3_en_na		(LPC_GPIO2->FIOPIN)&=~((1<<12)\
																						|(1<<13));\
											(LPC_GPIO0->FIOPIN)&=~((1<<28)\
																						|(1<<30)\
																						|(1<< 0))
							
#define	CHNL4_en_na		(LPC_GPIO2->FIOPIN)&=~(1<<13);\
											(LPC_GPIO0->FIOPIN)&=~((1<<30)\
																						|(1<< 0))
									
#define	CHNL5_en_na		(LPC_GPIO3->FIOPIN)&=~((1<<25)\
																						|(1<<26));\
											(LPC_GPIO4->FIOPIN)&=~(1<<28);\
											(LPC_GPIO0->FIOPIN)&=~((1<<28)\
																						|(1<<29)\
																						|(1<< 0))
										
#define	CHNL6_en_na		(LPC_GPIO3->FIOPIN)&=~(1<<25);\
											(LPC_GPIO4->FIOPIN)&=~(1<<28);\
											(LPC_GPIO0->FIOPIN)&=~((1<<29)\
																						|(1<< 0))
								
#define	CHNL7_en_na		(LPC_GPIO3->FIOPIN)&=~(1<<26);\
											(LPC_GPIO4->FIOPIN)&=~(1<<28);\
											(LPC_GPIO0->FIOPIN)&=~((1<<28)\
																						|(1<< 0))
									
#define	CHNL8_en_na		(LPC_GPIO4->FIOPIN)&=~(1<<28);\
											(LPC_GPIO0->FIOPIN)&=~(1<< 0)
										
#define	CHNL9_en_na		(LPC_GPIO4->FIOPIN)&=~(1<<29);\
											(LPC_GPIO0->FIOPIN)&=~((1<<21)\
																						|(1<<22)\
																						|(1<<28)\
																						|(1<<29)\
																						|(1<<30))
#define	CHNL10_en_na	(LPC_GPIO4->FIOPIN)&=~(1<<29);\
											(LPC_GPIO0->FIOPIN)&=~((1<<22)\
																						|(1<<29)\
																						|(1<<30))
									
#define	CHNL11_en_na	(LPC_GPIO0->FIOPIN)&=~((1<<21)\
																						|(1<<22)\
																						|(1<<28)\
																						|(1<<30))
								
#define	CHNL12_en_na	(LPC_GPIO0->FIOPIN)&=~((1<<22)\
																						|(1<<30))
											
// Alarm thread control
#define		AUD1_ALM_en		(LPC_GPIO0->FIOPIN)|=(1<<1);\
												(LPC_GPIO2->FIOPIN)&=~(1<<1)
#define		AUD1_ALM_dis	(LPC_GPIO0->FIOPIN)&=~(1<<1);\
												(LPC_GPIO2->FIOPIN)|=(1<<1)

#define		AUD2_ALM_en		(LPC_GPIO2->FIOPIN)|=(1<<4);\
												for(i=0;i<25000;i++);\
												(LPC_GPIO2->FIOPIN)&=~(1<<0)
#define		AUD2_ALM_dis	(LPC_GPIO2->FIOPIN)&=~(1<<4);\
												for(i=0;i<25000;i++);\
												(LPC_GPIO2->FIOPIN)|=(1<<0)

#define		AUD3_ALM_en		(LPC_GPIO2->FIOPIN)|=(1<<5);\
												(LPC_GPIO1->FIOPIN)&=~(1<<28)
#define		AUD3_ALM_dis	(LPC_GPIO2->FIOPIN)&=~(1<<5);\
												(LPC_GPIO1->FIOPIN)|=(1<<28)

#define		AUD4_ALM_en		(LPC_GPIO2->FIOPIN)|=(1<<6);\
												(LPC_GPIO1->FIOPIN)&=~(1<<26)
#define		AUD4_ALM_dis	(LPC_GPIO2->FIOPIN)&=~(1<<6);\
												(LPC_GPIO1->FIOPIN)|=(1<<26)

#define		AUD5_ALM_en		(LPC_GPIO2->FIOPIN)|=(1<<7);\
												(LPC_GPIO0->FIOPIN)&=~(1<<15)
#define		AUD5_ALM_dis	(LPC_GPIO2->FIOPIN)&=~(1<<7);\
												(LPC_GPIO0->FIOPIN)|=(1<<15)

#define		AUD6_ALM_en		(LPC_GPIO2->FIOPIN)|=(1<<8);\
												(LPC_GPIO0->FIOPIN)&=~(1<<11)
#define		AUD6_ALM_dis	(LPC_GPIO2->FIOPIN)&=~(1<<8);\
												(LPC_GPIO0->FIOPIN)|=(1<<11)

#define		AUD7_ALM_en		(LPC_GPIO2->FIOPIN)|=(1<<9);\
												(LPC_GPIO1->FIOPIN)&=~(1<<18)
#define		AUD7_ALM_dis	(LPC_GPIO2->FIOPIN)&=~(1<<9);\
												(LPC_GPIO1->FIOPIN)|=(1<<18)

#define		AUD8_ALM_en		(LPC_GPIO0->FIOPIN)|=(1<<18);\
												(LPC_GPIO1->FIOPIN)&=~(1<<19)
#define		AUD8_ALM_dis	(LPC_GPIO0->FIOPIN)&=~(1<<18);\
												(LPC_GPIO1->FIOPIN)|=(1<<19)

#define		AUD9_ALM_en		(LPC_GPIO0->FIOPIN)|=(1<<10);\
												(LPC_GPIO1->FIOPIN)&=~(1<<20)
#define		AUD9_ALM_dis	(LPC_GPIO0->FIOPIN)&=~(1<<10);\
												(LPC_GPIO1->FIOPIN)|=(1<<20)

#define		AUD10_ALM_en	(LPC_GPIO0->FIOPIN)|=(1<<27);\
												(LPC_GPIO1->FIOPIN)&=~(1<<21)
#define		AUD10_ALM_dis	(LPC_GPIO0->FIOPIN)&=~(1<<27);\
												(LPC_GPIO1->FIOPIN)|=(1<<21)

#define		AUD11_ALM_en	(LPC_GPIO0->FIOPIN)|=(1<<19);\
												(LPC_GPIO1->FIOPIN)&=~(1<<22)
#define		AUD11_ALM_dis	(LPC_GPIO0->FIOPIN)&=~(1<<19);\
												(LPC_GPIO1->FIOPIN)|=(1<<22)

#define		AUD12_ALM_en	(LPC_GPIO0->FIOPIN)|=(1<<20);\
												(LPC_GPIO1->FIOPIN)&=~(1<<23)
#define		AUD12_ALM_dis	(LPC_GPIO0->FIOPIN)&=~(1<<20);\
												(LPC_GPIO1->FIOPIN)|=(1<<23)

/*-------------------------MACRO FUNCTIONS -----------------------------------*/
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
extern void AlarmStart(uint32_t port);
extern void AlarmStop	(uint32_t port);

#endif

/*------------------------------------------------------------------------------
--                            End Of File
------------------------------------------------------------------------------*/
