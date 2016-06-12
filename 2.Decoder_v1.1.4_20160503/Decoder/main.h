/*----------------------------------------------------------------------------
 *      Skuo LPC1768 12 Ports Decoder
 *----------------------------------------------------------------------------
 *      Name:    main.h
 *      Purpose: 12 Ports decoder demo@Fei,Hui
 *----------------------------------------------------------------------------
 *      This code is use the RealView Run-Time Library.
 *      2013-12.05
 *---------------------------------------------------------------------------*/
 
#ifndef __MAIN_H
#define __MAIN_H

#define DEBUG
// TCP/UDP port/max. pkt len definitions
#define PORTADMIN		10000			// admin server port
#define LOCUDP      6810			// local UDP port
#define LOCTCP      10001			// local TCP port
#define PORTUDP     6811			// remote udp port
#define PORTTCP     10002			// TCP server port, either local or remote
#define TCPMAXLEN   1460			// TCP max. packet length
#define UDPMAXLEN   1472			// UDP max. packet length
// tcp intercom state machine
#define IDLE        0
#define CONFIRM     1
#define WAITANS			2
#define INDICATION  3
#define INTERCOM		4
#define CALLOUT			5
#define MONITOR			6

#define AUD_INTERCOM		1
#define AUD_RING				2
#define AUD_BUSY				3

#define RINGBUFSIZE			5
// structure tcp intercom
struct tcppacket{
    unsigned int   state;
    unsigned int   ltime;
    char  roomnum[7];
    char  password[5];
    char  title[20];
    char  ip[1024];
} my;

// structure remote peer, Admin for remote adminitration centre
struct RemotePeer {
	uint8_t	 IP[4];
	uint16_t Port;
} Rem = {
	{192, 168, 0, 0},
	{10002},
}, Outdoor = {
	{192, 168, 4, 0},
	{10002},
}, Admin = {
	{192, 168, 4, 78},
	{10000},
}, Server = {
	{192, 168, 4, 77},
	{10002},
};

// TCP/UDP initializer
uint8_t socket_tcps, socket_tcpc;
uint8_t socket_udp;
uint8_t LOC_IP[16];											// local IP
int			seqnum;
uint8_t udptxbuf[UDPMAXLEN];						// UDP tx/rx buffer for Audio display
uint8_t udprxbuf[UDPMAXLEN];
uint8_t udpwrptr = 10, udprdptr = 0;		// UDP ring buffer r/w pointer, do not need mutex
uint8_t tcpbuf[TCPMAXLEN];							// TCP tx buffer for intercom state machine
uint16_t UDPLEN, TCPLEN;
volatile uint32_t msTick = 0, systime = 0;						// systick counter

uint8_t GETINFO = __TRUE, ADMIN = __FALSE;
uint8_t LastState = IDLE, ComState = IDLE, CallState = __FALSE, Busy = __FALSE, Hangoff = __FALSE, Monitor = __FALSE, Unlock = __FALSE;		// communication/calling/busy flag
BOOL tick = __FALSE;										// systick flag

int crtroom, crtport = -1, lastport = -1;
char version[20] = "v1.1.4";

// Ring audio source
extern uint8_t video;
extern unsigned int ringptr;
extern const unsigned char Ring[24000];
extern const unsigned char busytone[7000];
/* CX20707 I2S */
extern volatile uint8_t *I2STXBuf0, *I2STXBuf1, *I2SRXBuf0, *I2SRXBuf1;

#endif

/*------------------------------------------------------------------------------
--                            End Of File
------------------------------------------------------------------------------*/
