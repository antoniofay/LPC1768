/*----------------------------------------------------------------------------
 *      Skuo LPC1768 12 Ports Decoder
 *----------------------------------------------------------------------------
 *      Name:    adc.c
 *      Purpose: 12 Ports decoder demo@Fei,Hui
 *----------------------------------------------------------------------------
 *      This code is use the RealView Run-Time Library.
 *      2013-12.16
 *---------------------------------------------------------------------------*/
 
#ifndef __TIMER_H 
#define __TIMER_H

// tcp intercom state machine
#define IDLE        0
#define CONFIRM     1
#define WAITANS			2
#define INDICATION  3
#define INTERCOM		4
#define CALLOUT			5
#define MONITOR			6

#define TCPMAXLEN   1460

#define TIM0_INTERVAL		250000						// val = t*Fpclk/(PR+1), t=10ms, 240ms/cycle
#define TIM1_INTERVAL		(3025000000UL)		// val = t*Fpclk/(PR+1), t=120s
#define CALL_INTERVAL		(750000000UL)			// 30s
#define CON_INTERVAL		(75000000UL)			// 3s

extern volatile uint32_t msTick, systime;
extern volatile uint32_t timer1_counter;

extern uint8_t	GETINFO, ADMIN, ALMDELAY;
extern uint32_t TimerInit 		(uint8_t timer_num, uint32_t TimerInterval);
extern void enTimer 					(uint8_t timer_num);
extern void disTimer 					(uint8_t timer_num);
extern void TimerReset 				(uint8_t timer_num);
extern void TIMER0_IRQHandler (void);
extern void TIMER1_IRQHandler (void);

#endif

/*------------------------------------------------------------------------------
--                            End Of File
------------------------------------------------------------------------------*/
