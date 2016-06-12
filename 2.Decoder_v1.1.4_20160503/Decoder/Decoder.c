/*----------------------------------------------------------------------------
 *      Skuo LPC1768 12 Ports Decoder
 *----------------------------------------------------------------------------
 *      Name:    Decoder.c
 *      Purpose: 12 Ports decoder demo@Fei,Hui
 *----------------------------------------------------------------------------
 *      This code is use the RealView Run-Time Library.
 *      2013.12.05
 *---------------------------------------------------------------------------*/

#include <rtl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <lpc17xx.h>
#include <i2s.h>
#include <dma.h>
#include <iap.h>
#include <adc.h>
#include <wdt.h>
#include <uart.h>
#include <gpio.h>
#include <timer.h>
#include "main.h"

/*--------------------------- Systick IRQ ------------------------------------*/

void SysTick_Handler (void) {
	/* SysTick Handler */
	msTick++;
} 

/*--------------------------- timer_poll ------------------------------------*/

static void timer_poll (void) {
  /* System tick timer running in poll mode */
	static uint32_t msTickLast;
  
	/*if (!(msTick%100))
		timer_tick ();*/
	if (msTickLast != msTick/10) {
		WDTFeed;
		msTickLast = msTick/10;
		tick = __TRUE;
		timer_tick ();                   // timer tick every 100ms for TCPnet stack
	}
}

/*---------------------- sleep time*tick_interval ----------------------------*/

void sleep (uint32_t time)
{
	tick = __FALSE;
	while(1) {
		timer_poll();
		if (tick) {
			tick = __FALSE;
			time--;
		}
		if (!time)
			break;
	}
}

/*--------------------------- UDP Process send data  ------------------------*/

void udpsend (uint8_t *buf, uint16_t LEN) {
  uint8_t *sendbuf;
	
	  /* UDP */
  if (0 != socket_udp) {
    /* Start Connection */
    sendbuf = udp_get_buf (LEN);
    memcpy (sendbuf, buf, LEN);
    udp_send (socket_udp, Rem.IP, PORTUDP, sendbuf, LEN);
  }	
}

/*--------------------------- TCP Process send data  ------------------------*/

void tcpsend (uint8_t soc, uint16_t port, uint8_t *buf, uint16_t LEN) {
	int i;
	uint8_t *sendbuf;
	
  /* TCP */
  if (0 != soc) {
    /* Start Connection */
    switch (tcp_get_state(soc)) {
      case TCP_STATE_FREE:
			case TCP_STATE_CLOSED:
				tcp_connect (soc, Rem.IP, port, 0);
        break;

      case TCP_STATE_CONNECT:
        if (tcp_check_send (soc) == __TRUE) {
					sendbuf = tcp_get_buf(LEN);
					memcpy(sendbuf, buf, LEN);
					tcp_send(soc, sendbuf, LEN);
					switch(buf[0]) {
						case 0x0f:
							break;
						
						case 0x0c:
							ComState = LastState;
							LastState = IDLE;
							break;
						
						case 0xfb:
							indoor[crtport].state[0] = 0;
							if (CallState == __TRUE) {
								ComState = INTERCOM;
								sleep(10);
							}
							break;
							
						case 0xfc:
							if (Hangoff) {
								Hangoff = __FALSE;
								ComState = IDLE;
							}
							else if (CallState) {
								ComState = IDLE;
							}
							else if (Monitor) {
								Monitor = __FALSE;
								ComState = IDLE;
							}
							Rem.Port = PORTTCP;
							indoor[crtport].state[1] = 0;
							for(i=0; i<PortNum; i++) {
								memset(&indoor[i].keyval, 0, sizeof(indoor[i].keyval));
								memset(&indoor[i].state, 0, sizeof(indoor[i].state));
							}
							if ((EMERG1 & (1<<crtport)) || (EMERG2 & (1<<crtport))) {
								tcpbuf[0] = 0xfc;
								ComState = CONFIRM;
								AlarmStart(indoor[crtport].port);
							}
							else {
								ClosePort(indoor[crtport].port);
							}
							disTimer(1);
							disAudio();
							CallState = __FALSE;
							ADMIN = __FALSE;
							Busy = __FALSE;
							crtport = -1;
							break;
							
						case 0xfd:
							tcpbuf[0] = 0x0f;
						  memset(&my, 0, TCPLEN);
							my.state = 0x0f;
							memcpy(&my.ip, LOC_IP, sizeof(LOC_IP));
							memcpy(tcpbuf, (uint8_t *)&my, TCPLEN);
							Rem.Port = Admin.Port;
							break;
						
						case 0xdf:
							video = 0;
							OpenPort(indoor[crtport].port);
							Monitor = __FALSE;
							TimerInit(1, CALL_INTERVAL+CON_INTERVAL);
							enTimer(1);
							break;
						
						case 0x0e:
							tcpbuf[0] = 0xfb;
							ComState = WAITANS;
							DMAConfig();
							enAudio();
							AudioFlag = AUD_RING;
							break;
						
						case 0x11:
							TCPLEN = sizeof(my);
							memset(&my, 0, TCPLEN);
							my.state = 0x0f;
							memcpy(&my.ip, LOC_IP, sizeof(LOC_IP));
							memcpy(tcpbuf, (uint8_t *)&my, TCPLEN);
							Unlock = __FALSE;
							break;
						
						case 0x8a:
							tcpbuf[0] = 0x0f;
							ComState = IDLE;
							TimerInit(1, TIM1_INTERVAL);
							disTimer(1);
							GETINFO = __FALSE;
							break;
						
						case 0x49:
							TCPLEN = sizeof(my);
							memset(&my, 0, TCPLEN);
							my.state = 0x0f;
							memcpy(&my.ip, LOC_IP, sizeof(LOC_IP));
							memcpy(tcpbuf, (uint8_t *)&my, TCPLEN);
							//Alarm &= ~(1<<crtport);//20160519
							Alarm &= ~(1<<almport);	//20160519
							break;
							
						default:
							break;
					}
				}
        break;
    }
  }
	return;
}

/*--------------------------- UDP socket ------------------------------------*/

uint16_t udp_callback (uint8_t soc, uint8_t *rip, uint16_t rport, uint8_t *buf, uint16_t len) {
  /*Rem_IP[0]  = rip[0];
	Rem_IP[1]  = rip[1];
	Rem_IP[2]  = rip[2];
	Rem_IP[3]  = rip[3];
  Rem_PORT = rport;*/
  UDPLEN  = len;

  if (soc != socket_udp) {
    /* Check if this is the socket we are connected to */
    return 0;
  }

	memcpy(udprxbuf+udpwrptr*len, buf, len);
	if (udpwrptr != udprdptr) {
		udpwrptr = (udpwrptr + 1)%RINGBUFSIZE;
	}
	
  return 0;
}

/*--------------------------- TCP socket ------------------------------------*/

uint16_t tcp_callback (uint8_t soc, uint8_t evt, uint8_t *ptr, uint16_t par) {
  /* This function is called by the TCP module on TCP event */
  /* Check the 'Net_Config.h' for possible events.          */
	int i, tmp, flag = __FALSE;
	char *p,*p1,*p2,*p3;
  par = par;

  if ((soc != socket_tcps) && (soc != socket_tcpc)) {
    return 0;
  }
	
  switch (evt) {
    case TCP_EVT_DATA:
      /* TCP data frame has arrived, data is located at *par1, */
      /* data length is par2. Allocate buffer to send reply.   */
			
			memcpy(&my, ptr, sizeof(my));
      switch (my.state) {
				case 0x0c:
					tcp_close(socket_tcpc);
					ComState = IDLE;
					DMAConfig();
					enAudio();
					AudioFlag = AUD_BUSY;
					break;
				
				case 0x0e:
					tcp_close(socket_tcpc);
					DMAConfig();
					enAudio();
					AudioFlag = AUD_RING;
					tcpbuf[0] = 0xfb;
					ComState = IDLE;
					break;
				
				case 0x0f:
					LastState = ComState;
					if(!Busy) {
						Busy = __TRUE;
						tcpbuf[0] = 0x0e;
						if (my.roomnum[0] == 0xff) {
							sscanf((const char *)&my.title, "%d",&crtroom);
							video = 0;
						}
						else {
							sscanf((const char *)&my.roomnum, "%d",&crtroom);
						}
						for (i=0; i<PortNum; i++) {
							if (indoor[i].room == crtroom) {
								crtport = i;
								if ((EMERG1 & (1<<i)) || (EMERG2 &  (1<<i))) {	// if under alarm
									if (ADMIN)	{				// if this call is made by admin, then stop alarm and pick up.
										AlarmStop(indoor[i].port);
									}
									else {
										crtport = -1;
										break;
									}
								}
								OpenPort(indoor[i].port);
								TimerInit(1, CALL_INTERVAL);
								enTimer(1);
							}
						}
						if (crtport == -1) {
							video = 1;
							Busy = __FALSE;
							tcpbuf[0] = 0x0c;
						}
					}
					else {
						tcpbuf[0] = 0x0c;
					}
					ComState = CONFIRM;
					break;
				
				case 0xfb:
					memset((uint8_t *)I2STXBuf0, 0x00, I2SSIZE);
					memset((uint8_t *)I2STXBuf1, 0x00, I2SSIZE);
					if (CallState == __TRUE) {
						ComState = CONFIRM;
					}
					else if (CallState == __FALSE) {
						ComState = INTERCOM;
						sleep(10);
					}
					AudioFlag = AUD_INTERCOM;
					TimerInit(1, TIM1_INTERVAL);
					enTimer(1);
				  break;
				
				case 0xfc:
					if (ComState == INTERCOM || ComState == WAITANS || ComState == MONITOR) {
							Hangoff = __TRUE;
					}
					tcp_close(socket_tcpc);
				  break;
					
				case 0xfd:
					sscanf((const char *)&my.ip, "%d.%d.%d.%d", (int *)&Admin.IP[0], (int *)&Admin.IP[1], (int *)&Admin.IP[2], (int *)&Admin.IP[3]);
					memcpy(&Rem.IP, &Admin.IP, sizeof(Admin.IP));
					Admin.Port = PORTADMIN;
					video = 0;
					break;
					
				case 0xdf:
					video = 1;
					OpenPort(indoor[crtport].port);
					break;
					
				case 0xfe:
					ComState = IDLE;
					DMAConfig();
					enAudio();
					AudioFlag = AUD_BUSY;
					break;
					
				case 0xff:
					if (ComState == MONITOR) {
						Busy = __FALSE;
						Monitor = __FALSE;
						ComState = IDLE;
						TimerInit(1, TIM1_INTERVAL);
						disTimer(1);
						DMAConfig();
						enAudio();
						AudioFlag = AUD_BUSY;
					}
					break;
					
				case 0x8a:
					GETINFO = 0;
					p = my.ip;
					i = 0;
					while (*p != 0 && i < 12) {
						p1 = strchr(p, '[');
						if (p1 == 0) {
							break;
						}
						p2 = strchr(p1 + 1, '|');
						if (p2 == 0) {
							break;
						}
						p3 = strchr(p2+1, ']');
						if (p3 == 0) {
							break;
						}
						p = p3 + 1;
						*p2 = *p3 = 0;
						if (strlen(p1 + 1) > 0 && strlen(p1 + 1) < 8) {
							sscanf(p1 + 1, "%d", &tmp);
							if (tmp != indoor[i].room) {
								indoor[i].room = tmp;
								flag = __TRUE;
							}
						}
						else {
							indoor[i].room = 0;
						}
						if (strlen(p2 + 1) > 0 && strlen(p2 + 1) < 8) {
							sscanf(p2 + 1, "%d", &indoor[i].id);
						}
						else {
							indoor[i].id = -1;
						}	
						i++;	
					}
					if (flag)
						refresh_update(__FALSE);
					//val=i;
					break;
					
				case 0x49:
					almport = -1;
					break;
					
				default:
					break;
				}
      break;

    case TCP_EVT_CONREQ:
      /* Remote peer requested connect, accept it */
			GETINFO = 0;
		  Rem.IP[0] = ptr[0];
      Rem.IP[1] = ptr[1];
      Rem.IP[2] = ptr[2];
      Rem.IP[3] = ptr[3];
		  if (Rem.IP[3] == Admin.IP[3]) {
				Rem.Port = Admin.Port;
				ADMIN = __TRUE;
			}
			else
				Rem.Port = PORTTCP;
		
      return 1;
		
    case TCP_EVT_CONNECT:
      /* The TCP socket is connected */
      return 1;
		
		case TCP_EVT_ACK:
      /* Our sent data has been acknowledged by remote peer */
      break;
		
		case TCP_EVT_ABORT:
      return 1;
		
		case TCP_EVT_CLOSE:
      return 1;
  }
  return 0;
}

/*--------------------------- init ------------------------------------------*/

void init (void) {
  /* Set the clocks. */
  SystemInit();
	
  /* Setup and enable the SysTick timer for 10ms. */
  if (SysTick_Config(SystemCoreClock/100)) {
     while(1);
	}
	
#ifdef DEBUG
	UARTInit(0, 115200);
#endif
	
	GPIOInit();
	/* Initial ADC */
	ADCInit();
	
	/* Initial TCPnet. */
	init_TcpNet();
	
	TCPLEN = sizeof(my);
	memset(tcpbuf, 0, TCPMAXLEN);
	my.state = 0x0f;
	memcpy(&my.ip, LOC_IP, sizeof(LOC_IP));
	memcpy(tcpbuf, (uint8_t *)&my, TCPLEN);
	
  /* Initialize UDP Socket and start listening */
  socket_udp = udp_get_socket(0, UDP_OPT_SEND_CS | UDP_OPT_CHK_CS, udp_callback);
  if (0 != socket_udp) {
    udp_open(socket_udp, LOCUDP);
  }
	
  /* Initialize TCP Socket and start listening */
  socket_tcps = tcp_get_socket(TCP_TYPE_SERVER, 0, 5, tcp_callback);
  if (0 != socket_tcps) {
    tcp_listen(socket_tcps, PORTTCP);
  }
	
	/* Initialize TCP Client Socket */
  socket_tcpc = tcp_get_socket(TCP_TYPE_CLIENT, 0, 5, tcp_callback);
	
	/* Initialize I2S for cx20707 */
	if (0 == I2SInit())	{
		while(1);
  }
	memset(udprxbuf, 0xD5, UDPMAXLEN);
	sleep(1);
	
	/* Enable watchdog timer */
	WDTInit();
	
	/* Initialize and enable Timer0 for adc */
	TimerInit(0, TIM0_INTERVAL);
	enTimer(0);
	
	/* Initialize Timer1 for 120s calling timing */
	TimerInit(1, CON_INTERVAL);
	enTimer(1);
	
	TimerInit(2, 2500);
	return;
}


/*--------------------------- main ------------------------------------------*/

int main (int argc, char* argv[]) {
	uint32_t i, cnt = 0;
	
	/* restore configuration infos(networking & room/port mapping) */
	restore_config();
	/* Init system */
  init();
	
  while(1) {
    timer_poll();
    main_TcpNet();
		
		/* state machine for tcp calling control */
		switch (ComState) {
			case IDLE:															// idle, break
			  break;
				
			case CONFIRM:														// send confirm/hangoff message to client peer
				tcpsend(socket_tcps, Rem.Port, tcpbuf, TCPLEN);
			  break;
				
			case WAITANS:													// send intercom message to start a communication
				if (indoor[crtport].state[0]) {
					tcpsend(socket_tcpc, Rem.Port, tcpbuf, TCPLEN);
				}
				else if (indoor[crtport].state[1]) {
						ClosePort(indoor[crtport].port);
						disTimer(1);
						disAudio();
						CallState = __FALSE;
						Busy = __FALSE;
						tcpbuf[0] = 0xfc;
						tcpsend(socket_tcpc, Rem.Port, tcpbuf, TCPLEN);
				}
				else if (Hangoff) {
					tcpbuf[0] = 0xfc;
					tcpsend(socket_tcps, Rem.Port, tcpbuf, TCPLEN);
				}
				break;
				
		  case INTERCOM:
				if (indoor[crtport].state[1]) {
					ClosePort(indoor[crtport].port);
					disTimer(1);
					disAudio();
					CallState = __FALSE;
					Busy = __FALSE;
					tcpbuf[0] = 0xfc;
					tcpsend(socket_tcpc, Rem.Port, tcpbuf, TCPLEN);
				}
				else {
					if (Hangoff) {
						tcpbuf[0] = 0xfc;
						tcpsend(socket_tcps, Rem.Port, tcpbuf, TCPLEN);
					}
				}
			  break;
				
			case CALLOUT:															// call adminitration centre
				if (tcpbuf[0] == 0xfd) {
					CallState = __TRUE;
					ADMIN = __TRUE;
					Server.IP[0]=0xC0;
					memcpy(&Rem.IP, &Server.IP, sizeof(Server.IP));
					my.state = 0xfd;
					sprintf(my.roomnum, "%d", indoor[crtport].room);
					my.ltime = indoor[crtport].id;
					my.title[0] = 0x01;
					memcpy(tcpbuf, (uint8_t *)&my, TCPLEN);
				}
				tcpsend(socket_tcpc, Rem.Port, tcpbuf, TCPLEN);
			  break;
			
			case MONITOR:
				if (Monitor) {
					if(0x00 != Outdoor.IP[3])
						memcpy(&Rem.IP, &Outdoor.IP, sizeof(Outdoor.IP));
					Rem.Port = PORTTCP;
					tcpsend(socket_tcpc, Rem.Port, tcpbuf, TCPLEN);
				}
				else {
					if (Hangoff) {
						tcpbuf[0] = 0xfc;
						tcpsend(socket_tcps, Rem.Port, tcpbuf, TCPLEN);
					}
				}
				break;
			
			default:
				break;
		}
		
		/* audio stream handler, channel 0,1 for tx; 2,3 for rx */
		if (AudioFlag == AUD_INTERCOM) {
			if (I2SDMA2Done) {
				//memcpy(udptxbuf, (uint8_t *)I2SRXBuf0, I2SSIZE);
				memcpy(udptxbuf, &seqnum, sizeof(int));
				for (i=0; i<HI2SSIZE; i++) {
					udptxbuf[i+sizeof(int)] = I2SRXBuf0[i*2+1];
				}
				seqnum++;
				I2SDMA2Done = 0;
				udpsend(udptxbuf, HI2SSIZE+4);
			}
			else if (I2SDMA3Done) {
				//memcpy(udptxbuf, (uint8_t *)I2SRXBuf1, I2SSIZE);
				memcpy(udptxbuf, &seqnum, sizeof(int));
				for (i=0; i<HI2SSIZE; i++) {
					udptxbuf[i+sizeof(int)] = I2SRXBuf1[i*2+1];
				}
				seqnum++;
				I2SDMA3Done = 0;
				udpsend(udptxbuf, HI2SSIZE+4);
			}
			
			if (I2SDMA0Done) {
				for (i=0; i<HI2SSIZE; i++) {
					//I2STXBuf0[i*2] = udprxbuf[i+sizeof(int)];
					//I2STXBuf0[i*2] = udprxbuf[i+sizeof(int)+udprdptr*132];
					I2STXBuf0[i*2+1] = udprxbuf[i+sizeof(int)+udprdptr*132];
				}
				udprdptr = (udprdptr + 1)%RINGBUFSIZE;
				I2SDMA0Done = 0;
			}
			else if (I2SDMA1Done) {
				for (i=0; i<HI2SSIZE; i++) {
					//I2STXBuf1[i*2] = udprxbuf[i+sizeof(int)];
					//I2STXBuf1[i*2] = udprxbuf[i+sizeof(int)+udprdptr*132];
					I2STXBuf1[i*2+1] = udprxbuf[i+sizeof(int)+udprdptr*132];
				}
				udprdptr = (udprdptr + 1)%RINGBUFSIZE;
				I2SDMA1Done = 0;
			}
		}
		
		else if (AudioFlag == AUD_RING) {
			if (I2SDMA0Done) {
				for (i=0; i<HI2SSIZE; i++) {
					I2STXBuf0[i*2+1] = Ring[i+ringptr*HI2SSIZE];
				}
				ringptr = (ringptr + 1)%149;
				I2SDMA0Done = 0;
			}
			else if (I2SDMA1Done) {
				for (i=0; i<HI2SSIZE; i++) {
					I2STXBuf1[i*2+1] = Ring[i+ringptr*HI2SSIZE];
				}
				ringptr = (ringptr + 1)%149;
				I2SDMA1Done = 0;
			}
		}
		else if (AudioFlag == AUD_BUSY) {
			if (I2SDMA0Done) {
				for (i=0; i<HI2SSIZE; i++) {
					I2STXBuf0[i*2+1] = busytone[i+ringptr*HI2SSIZE];
				}
				ringptr = ringptr + 1;
				I2SDMA0Done = 0;
			}
			else if (I2SDMA1Done) {
				for (i=0; i<HI2SSIZE; i++) {
					I2STXBuf1[i*2+1] = busytone[i+ringptr*HI2SSIZE];
				}
				ringptr = ringptr + 1;
				I2SDMA1Done = 0;
			}
			
			if (ringptr >= 54) {
				cnt++;
				ringptr = 0;
			}
			if (cnt == 3) {
				cnt = 0;
				disTimer(1);
				disAudio();
				ClosePort(indoor[crtport].port);
				CallState = __FALSE;
				Busy = __FALSE;
				crtport = -1;
			}
		}
		
		/* Alarm control */
		if (Alarm && (almport != -1)) {
			if (EMERG1 || EMERG2) {	// emergency, inform immediately
				memcpy(&Rem.IP, &Admin.IP, sizeof(Admin.IP));
				TCPLEN = sizeof(my);
				my.state = 0x49;
				sprintf(my.roomnum, "%d", indoor[almport].room);
				my.ltime = indoor[almport].id;
				my.title[0] = 0x01;
				memcpy(tcpbuf, (uint8_t *)&my, TCPLEN);
				tcpsend(socket_tcpc, Rem.Port, tcpbuf, TCPLEN);
			}
			/*else {	// normal alarm, inform admin 40s later
				if ((msTick - systime) >= 4000) {
					memcpy(&Rem.IP, &Admin.IP, sizeof(Admin.IP));
					TCPLEN = sizeof(my);
					my.state = 0x49;
					sprintf(my.roomnum, "%d", indoor[almport].room);
					my.ltime = indoor[almport].id;
					my.title[0] = 0x0;
					memcpy(tcpbuf, (uint8_t *)&my, TCPLEN);
					tcpsend(socket_tcpc, Rem.Port, tcpbuf, TCPLEN);
				}
			}*/
		}
		
		if (Unlock) {
			if(ComState == MONITOR) {
				if(0x00 != Outdoor.IP[3])
					memcpy(&Rem.IP, &Outdoor.IP, sizeof(Outdoor.IP));
			}
			TCPLEN = sizeof(my);
			my.state = 0x11;
			sprintf(my.roomnum, "%d", indoor[crtport].room);
			memcpy(tcpbuf, (uint8_t *)&my, TCPLEN);
			tcpsend(socket_tcpc, Rem.Port, tcpbuf, TCPLEN);
		}
		
		if (GETINFO) {
			memcpy(&Rem.IP, &Server.IP, sizeof(Server.IP));
			tcpbuf[0] = 0x8a;
			Rem.Port = 10002;
			tcpsend(socket_tcpc, Rem.Port, tcpbuf, TCPLEN);
		}
  }
}

/*------------------------------------------------------------------------------
--                            End Of File
------------------------------------------------------------------------------*/
