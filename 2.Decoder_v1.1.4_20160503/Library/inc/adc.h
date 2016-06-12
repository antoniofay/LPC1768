/*----------------------------------------------------------------------------
 *      Skuo LPC1768 12 Ports Decoder
 *----------------------------------------------------------------------------
 *      Name:    adc.h
 *      Purpose: 12 Ports decoder demo@Fei,Hui
 *----------------------------------------------------------------------------
 *      This code is use the RealView Run-Time Library.
 *      2013-12.05
 *---------------------------------------------------------------------------*/
 
#ifndef __ADC_H
#define __ADC_H

// ADC Threshold
/* 50m net cable test result:
4" key value(V): 0.33   0.36 1.14
7" 2107 key value: 0.54   0.54 1.28
7" 2207 key value: */
/*#define Key1Thresh		550
#define Key2Thresl		800
#define Key2Thresh		1450
#define AlmThresl			1750
#define AlmThresh			2500
#define NormThresl		2800*/

//160520
#define Key1Thresh		700
#define Key2Thresl		800
#define Key2Thresh		1650
#define AlmThresl			1750
#define AlmThresh			2500
#define NormThresl		2800

// ADC channel
#define ADC0          0x1
#define ADC1          0x2
#define ADC2          0x4
#define ADC3          0x8
#define ADC4          0x10
#define ADC5          0x20
#define ADC6          0x40
#define ADC7          0x80
// 6 channels, 12 ports, 24 AD values total
#define ChnNum        6
#define PortNum       12
#define ValNum        24
// 8 filter order, flat filtered
#define FilterOrder   8
// 12 bits ADC
#define ADC_VALUE_MAX 0xFFF

// structure for indoor unit
extern struct Indoor {
	int id;
	int room;
	int port;
	uint32_t keyval[2];
	uint32_t state[4];
} indoor[PortNum];

extern volatile uint32_t adcount;
extern const uint32_t admap[6];
extern uint32_t Alarm, EMERG1, EMERG2;
extern int almport;

extern void 		ADCInit   (void);
extern uint32_t ADCGetCnv (void);
extern uint32_t ADCRead		(uint8_t chn);

#endif 

/*------------------------------------------------------------------------------
--                            End Of File
------------------------------------------------------------------------------*/
