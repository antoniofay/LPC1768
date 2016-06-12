/*----------------------------------------------------------------------------
 *      Skuo LPC1768 12 Ports Decoder
 *----------------------------------------------------------------------------
 *      Name:    adc.c
 *      Purpose: 12 Ports decoder demo@Fei,Hui
 *----------------------------------------------------------------------------
 *      This code is use the RealView Run-Time Library.
 *      2013.12.16
 *---------------------------------------------------------------------------*/
 
#include <string.h>
#include <lpc17xx.h>
#include <timer.h>
#include <uart.h>
#include <gpio.h>
#include <adc.h>
#include <i2s.h>
#include <dma.h>
#include <rtl.h>

uint8_t video = 1;
volatile uint32_t key1_counter = 0, key2_counter = 0, key3_counter = 0, disarm_counter;
volatile uint32_t timer1_counter = 0, mon_cnt = 0;
uint32_t key1_tim = 0, key2_tim = 0, alm_tim = 0, disarm = 0;
int almport = -1;
extern uint8_t  ComState, Busy, CallState, Hangoff, Unlock, Monitor;
extern int  crtroom, crtport, lastport;
extern uint8_t tcpbuf[TCPMAXLEN];
extern uint8_t socket_tcpc;
uint8_t banding = 0;

/*------------------------------------------------------------------------------
*  Function name:		Timer0_IRQHandler
*  Descriptions:		Timer/Counter 0 interrupt handler
*  parameters:			None
*  Returned value:	None
------------------------------------------------------------------------------*/
void TIMER0_IRQHandler (void) {
	int adport, adval;
	
	adport = adcount%PortNum;
	adval = adcount/PortNum;
	disarm_counter++;
	key1_counter++;
	key2_counter++;
	key3_counter++;
	mon_cnt++;
	
  indoor[adport].keyval[adval] = ADCRead (1<<(admap[adcount%ChnNum]%ChnNum));
	// Key value less key1 threshold, No.1,3
	if (indoor[adport].keyval[adval] < Key1Thresh) {
		//indoor[adport].keyval[adval] = 3300;
		if (((!(EMERG1 & (1<<adport))) && (!(EMERG2 & (1<<adport)))) || ComState == WAITANS) {
			key2_tim = 0;
			alm_tim = 0;
			disarm = 0;
			if (!key1_tim) {
				lastport = adport;
				key1_tim = 1;
				key1_counter = 0;
			}
			else {
				if (key1_counter >= 10 && lastport == adport) {
					key1_tim = 0;
					key1_counter = 0;
					if (adval == 0) { // key 1: call
						if (ComState == WAITANS) {
							indoor[adport].state[adval*2] = 1;
						}
						else if (!Busy) {
							video = 0;
							crtport = adport;
							tcpbuf[0] = 0xfd;
							ComState = CALLOUT;
							Busy = 1;
							TimerInit(1, CALL_INTERVAL);
							enTimer(1);
							OpenPort(indoor[crtport].port);
						}
						print(0, "Key1 call    : port ", adport + 1);
					}
					else if (adval == 1) { // key 3: monitor
						if (!Busy) {
							if (mon_cnt >= 192) {
								tcpbuf[0] = 0xdf;
								crtport = adport;
								ComState = MONITOR;
								Monitor = 1;
								TimerInit(1, CALL_INTERVAL);
								enTimer(1);
								Busy = 1;
								mon_cnt = 0;
							}
						}
						else if (ComState == MONITOR && crtport == adport) {
							if (mon_cnt >= 192) {
								Monitor = 1;
								tcpbuf[0] = 0xfc;
								mon_cnt = 0;
							}
						}
						print(0, "Key3 monitor : port ", adport + 1);
					}
				}
				if (key1_counter >= 24 && lastport != adport) {
					key1_tim = 0;
					key1_counter = 0;
				}
			}
		}
		if (!indoor[adport].state[adval*2]) {
			LPC_TIM0->IR = 1;
			return;
		}
			//UARTSendDec(0, indoor[adport].keyval[adval]);
	}
	
	// Key value between key2 threshold, No.2,4
	else if ((indoor[adport].keyval[adval] > Key2Thresl) && 
					 (indoor[adport].keyval[adval] < Key2Thresh)) {
		if (((!(EMERG1 & (1<<adport))) && (!(EMERG2 & (1<<adport)))) || ComState == INTERCOM || ComState == WAITANS) {
			key1_tim = 0;
			alm_tim = 0;
			disarm = 0;
			if (!key2_tim) {
				lastport = adport;
				key2_tim = 1;
				key2_counter = 0;
			}
			else {
				if (key2_counter >= 10 && lastport == adport) {
					key2_tim = 0;
					key2_counter = 0;
					if (adval == 0) { // key 2: hang off
						if (crtport == adport) {
							if (ComState == INTERCOM || ComState == WAITANS) {
								indoor[adport].state[adval*2 + 1] = 1;
								TimerInit(1, CON_INTERVAL);
								enTimer(1);
							}
							else if (ComState == CALLOUT) {
								ClosePort(indoor[crtport].port);
								disTimer(1);
								disAudio();
								CallState = 0;
								Busy = 0;
								ComState = IDLE;
								crtport = -1;		//20160524 不接管理中心呼叫后无法报警
							}
							else if (ComState == IDLE && CallState == 1) {
								tcpbuf[0] = 0xfc;
								ComState = CALLOUT;
								ClosePort(indoor[crtport].port);
							}
						}
						print(0, "Key2 hang off: port ", adport + 1);
					}
					else if (adval == 1) { // key 4: unlock
						if ((ComState == INTERCOM || ComState == MONITOR) && crtport == adport) {
							Unlock = 1;
						}
						print(0, "Key4 unlock  : port ", adport + 1);
					}
				}
				if (key2_counter >= 24 && lastport != adport) {
					key2_tim = 0;
					key2_counter = 0;
				}
			}
		}
		if (!indoor[adport].state[adval*2 + 1]) {
			LPC_TIM0->IR = 1;
			return;
		}
	}
	
	// key value between key3(alarm) threshold, alarm ad.
	else if ((indoor[adport].keyval[adval] > AlmThresl) && 
					 (indoor[adport].keyval[adval] < AlmThresh)) {
		//indoor[adport].keyval[adval] = 3300;
		// Alarm
		UARTSendDec(0, indoor[adport].keyval[adval]);
		key1_tim = 0;
		key2_tim = 0;
		disarm = 0;
		if (!alm_tim) {
				almport = adport;
				alm_tim = 1;
				key3_counter = 0;
		}
		else {
			if (key3_counter >= 96 && almport == adport) { // 1s timing
				alm_tim = 0;
				key3_counter = 0;
				if (adval == 0) { // alarm emerg1
					/*if (almport == crtport) {
						tcpbuf[0] = 0xfc;
						ComState = CALLOUT;
					}*/
					if (!(EMERG1 & (1<<adport))) {
						Alarm |= (1<<adport);
						if (almport != crtport) {	// if not, play alarm
							AlarmStart(adport + 1);
						}
						EMERG1 |= (1<<adport);
						systime = msTick;
						print(0, "Emerg1 start  : port ", adport + 1);
						print(0, "Alarm value  : ", Alarm);
					}
				}
				else if (adval == 1) { // alarm emergency2
					/*if (almport == crtport) {
						tcpbuf[0] = 0xfc;
						ComState = CALLOUT;
					}*/
					if (!(EMERG2 & (1<<adport))) {
						Alarm |= (1<<adport);
						if (almport != crtport) {	// if not, play alarm
							AlarmStart(adport + 1);
						}
						EMERG2 |= (1<<adport);
						systime = msTick;
						print(0, "Emerg2 start  : port ", adport + 1);
						print(0, "Alarm value  : ", Alarm);
					}
				}
			}
			else if (key3_counter >= 96 && almport != adport) {
				alm_tim = 0;
				key3_counter = 0;
			}
		}
		if ((!(EMERG1 & (1<<adport))) && (!(EMERG2 & (1<<adport)))) {
			LPC_TIM0->IR = 1;
			return;
		}
	}
	else {
		key1_tim = 0;
		key2_tim = 0;
		alm_tim = 0;
		if ((EMERG1 & (1<<adport)) && (adval == 0)) {	// channel 0 alarm
			if (indoor[adport].keyval[adval] > NormThresl) {
				if (!disarm) {
					almport = adport;
					disarm = 1;
					disarm_counter = 0;
				}
				else {
					if (disarm_counter >= 96 && almport == adport) {
						disarm = 0;
						disarm_counter = 0;
						// emergency2 stop
						Alarm &=~(1<<adport);
						//if (almport != crtport) {//20160519
						if ((almport != crtport)||(almport == -1)) {	//20160519
							AlarmStop(adport + 1);
						}
						EMERG1 &=~(1<<adport);
						print(0, "Emerg1 stop  : port ", adport + 1);
					}
					else if (key3_counter >= 96 && almport != adport) {
						disarm = 0;
						disarm_counter = 0;
					}
				}
				LPC_TIM0->IR = 1;
				return;
			}
		}
		else if ((EMERG2 & (1<<adport)) && (adval == 1)) {	// channel 1 alarm
			if (indoor[adport].keyval[adval] > NormThresl) {
				if (!disarm) {
					almport = adport;
					disarm = 1;
					disarm_counter = 0;
				}
				else {
					if (disarm_counter >= 96 && almport == adport) {
						disarm = 0;
						disarm_counter = 0;
						// emergency2 stop
						Alarm &=~(1<<adport);
						//if (almport != crtport) {//20160519
						if ((almport != crtport)||(almport == -1)) {	//20160519
							AlarmStop(adport + 1);
						}
						EMERG2 &=~(1<<adport);
						print(0, "Emerg2 stop  : port ", adport + 1);
					}
					else if (key3_counter >= 96 && almport != adport) {
						disarm = 0;
						disarm_counter = 0;
					}
				}
				LPC_TIM0->IR = 1;
				return;
			}
		}
	}
	
	//if (adport == 6)
		//UARTSendDec(0, indoor[adport].keyval[adval]);
	
	adcount++;
	if (ChnNum == adcount) {
		AD1H;
	}
	else if (PortNum == adcount) {
		AD1L;
		disADSEL1;
		enADSEL2;
	}
	else if (18 == adcount) {
		AD2H;
	}
	else if (ValNum == adcount) {
		adcount = 0;
		disADSEL2;
		enADSEL1;
		AD2L;
		//UARTSendString(0, "OK!");
	}
	
	LPC_TIM0->IR = 1;					// clear interrupt flag
  return;
}


/*------------------------------------------------------------------------------
*  Function name:		Timer1_IRQHandler
*  Descriptions:		Timer/Counter 1 interrupt handler
*  parameters:			None
*  Returned value:	None
------------------------------------------------------------------------------*/
void TIMER1_IRQHandler (void) {
	int i;
	
  LPC_TIM1->IR = 1;			// clear interrupt flag
	disTimer(1);					// 120s time out, close intercom
	Monitor = 0;
  ClosePort(indoor[crtport].port);
	disAudio();
	for(i=0; i<PortNum; i++) {
		ClosePort(indoor[i+1].port);
		memset(&indoor[i].keyval, 0, sizeof(indoor[i].keyval));
		memset(&indoor[i].state, 0, sizeof(indoor[i].state));
	}
	CallState = 0;
	Busy = 0;
	ComState = 0;
	GETINFO = 0;
	tcp_close(socket_tcpc);
	TimerInit(1, TIM1_INTERVAL);
  return;
}

/*------------------------------------------------------------------------------
*  Function name:		Timer2_IRQHandler
*  Descriptions:		Timer/Counter 2 interrupt handler
*  parameters:			None
*  Returned value:	None
------------------------------------------------------------------------------*/
void TIMER2_IRQHandler (void) {
  LPC_TIM2->IR = 1;			// clear interrupt flag
	switch(banding) {
		case 0:
			SK020_RST_lo;
			SK020_SEL_lo;
			banding = 1;
			break;
		case 1:
			SK020_RST_hi;
			banding = 2;
			break;
		case 2:
			SK020_RST_lo;
			banding = 3;
			break;
		case 3:
			SK020_SEL_hi;
			banding = 4;
			break;
		case 4:
			SK020_SEL_lo;
			TimerInit(2, 12500000);
			banding = 0;
			break;
	}
  return;
}

/*------------------------------------------------------------------------------
*  Function name:		enable_timer
*  Descriptions:		Enable timer
*  parameters:			timer number: 0 or 1
*  Returned value:	None
------------------------------------------------------------------------------*/
void enTimer (uint8_t timer_num) {
	TimerReset(timer_num);
  if (timer_num == 0) {
		LPC_TIM0->TCR = 1;
  }
  else {
		LPC_TIM1->TCR = 1;
  }
  return;
}


/*------------------------------------------------------------------------------
*  Function name:		disable_timer
*  Descriptions:		Disable timer
*  parameters:			timer number: 0 or 1
*  Returned value:	None
------------------------------------------------------------------------------*/
void disTimer (uint8_t timer_num) {
  if (timer_num == 0) {
		LPC_TIM0->TCR = 0;
  }
  else {
		LPC_TIM1->TCR = 0;
  }
  return;
}


/*------------------------------------------------------------------------------
*  Function name:		reset_timer
*  Descriptions:		Reset timer
*  parameters:			timer number: 0 or 1
*  Returned value:	None
------------------------------------------------------------------------------*/
void TimerReset (uint8_t timer_num) {
  uint32_t regVal;

  if (timer_num == 0) {
		regVal = LPC_TIM0->TCR;
		regVal |= 0x02;
		LPC_TIM0->TCR = regVal;
  }
  else {
		regVal = LPC_TIM1->TCR;
		regVal |= 0x02;
		LPC_TIM1->TCR = regVal;
  }
  return;
}


/*------------------------------------------------------------------------------
*  Function name:		TimerInit
*  Descriptions:		init timer
*  parameters:			timer number: 0 or 1
*										TimerInterval
*  Returned value:	None
------------------------------------------------------------------------------*/
uint32_t TimerInit (uint8_t timer_num, uint32_t TimerInterval) {
	
  if (0 == timer_num) {
		key1_counter = 0;
		key2_counter = 0;
		key3_counter = 0;
		LPC_TIM0->MR0 = TimerInterval;
		LPC_TIM0->MCR = 3;				// Interrupt and Reset on MR0

		NVIC_SetPriority(TIMER0_IRQn, 1);
		NVIC_EnableIRQ(TIMER0_IRQn);
		return 1;
  }
  else if (1 == timer_num) {
		timer1_counter = 0;
		LPC_TIM1->MR0 = TimerInterval;
		LPC_TIM1->MCR = 3;				// Interrupt and Reset on MR1

		NVIC_EnableIRQ(TIMER1_IRQn);
		return 1;
  }
	else if (2 == timer_num) {
		LPC_TIM2->MR0 = TimerInterval;
		LPC_TIM2->MCR = 3;				// Interrupt and Reset on MR1
		NVIC_EnableIRQ(TIMER2_IRQn);
		LPC_TIM2->TCR = 1;
		return 1;
  }
  return 0;
}


/*------------------------------------------------------------------------------
*  Function name:		Hardfault_Handler
*  Descriptions:		Hardfault
*  parameters:			None
*  Returned value:	None
------------------------------------------------------------------------------*/
void HardFault_Handler (void) {
	NVIC_SystemReset();
}

/*------------------------------------------------------------------------------
--                            End Of File
------------------------------------------------------------------------------*/
