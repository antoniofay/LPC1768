/*----------------------------------------------------------------------------
 *      Skuo LPC1768 12 Ports Decoder
 *----------------------------------------------------------------------------
 *      Name:    usart.c
 *      Purpose: 12 Ports decoder demo@Fei,Hui
 *----------------------------------------------------------------------------
 *      This code is use the RealView Run-Time Library.
 *      2013.12.05
 *---------------------------------------------------------------------------*/
 
#include "lpc17xx.h"                              /* LPC17xx definitions    */
#include "uart.h"

/*---------------------------------------------------------------------------
*  Function name:       UART_Init
*  Descriptions:        Initialize UARTn, 8 data bit, 1 stop bit, no polarity
*  input parameters:    n, baudrate
*  output parameters:   None
*  Returned value:      None
----------------------------------------------------------------------------*/
void UARTInit (uint8_t n, uint32_t baudrate) {
	uint16_t usFdiv;
	
	switch (n) {
		case 0:
			LPC_PINCON->PINSEL0 |= (1 << 4);								// Pin P0.2 used as TXD0 (Com0)
			LPC_PINCON->PINSEL0 |= (1 << 6);								// Pin P0.3 used as RXD0 (Com0)
			LPC_UART0->LCR  		 = 0x83;										// enable bautrate setting
			usFdiv							 = (FPCLK / 16) / baudrate;	// bautrate @baudrate
			LPC_UART0->DLM 			 = usFdiv / 256;
			LPC_UART0->DLL 			 = usFdiv % 256; 
			LPC_UART0->LCR		   = 0x03;										// lock baudrate
			LPC_UART0->FCR		   = 0x06;
			break;
		case 1:
			LPC_PINCON->PINSEL0 |= (1 << 30);								// Pin P0.15
			LPC_PINCON->PINSEL1 |= (1 << 0);								// Pin P0.16
			LPC_SC->PCONP				 = LPC_SC->PCONP|(1<<3);
			LPC_UART1->LCR  		 = 0x83;
			usFdiv							 = (FPCLK / 16) / baudrate;
			LPC_UART1->DLM 			 = usFdiv / 256;
			LPC_UART1->DLL		   = usFdiv % 256; 
			LPC_UART1->LCR  		 = 0x03;
			LPC_UART1->FCR 			 = 0x06;
			break;
		case 2:
			LPC_PINCON->PINSEL0 |= (1 << 20);								// Pin P0.10
			LPC_PINCON->PINSEL0 |= (1 << 22);								// Pin P0.11
			LPC_SC->PCONP				 = LPC_SC->PCONP|(1<<24);		// Power supply
			LPC_UART2->LCR  		 = 0x83;
			usFdiv							 = (FPCLK / 16) / baudrate;
			LPC_UART2->DLM 			 = usFdiv / 256;
			LPC_UART2->DLL		   = usFdiv % 256; 
			LPC_UART2->LCR  		 = 0x03;
			LPC_UART2->FCR 			 = 0x06;
			break;
		case 3:
			LPC_PINCON->PINSEL9 |= (3 << 24);								// Pin P4.28
			LPC_PINCON->PINSEL9 |= (3 << 26);								// Pin P4.29
			LPC_SC->PCONP				 = LPC_SC->PCONP|(1<<25);
			LPC_UART3->LCR  		 = 0x83;
			usFdiv							 = (FPCLK / 16) / baudrate;
			LPC_UART3->DLM 			 = usFdiv / 256;
			LPC_UART3->DLL		   = usFdiv % 256; 
			LPC_UART3->LCR  		 = 0x03;
			LPC_UART3->FCR 			 = 0x06;
			break;
		default:
			break;
	}
  	
  UARTSendString(n, "UART init OK!");
}

/*---------------------------------------------------------------------------
*  Function name:       UARTSendByte
*  Descriptions:        UARTn send data
*  input parameters:    n, data
*  output parameters:   None
*  Returned value:      None
----------------------------------------------------------------------------*/
int UARTSendByte (uint8_t n, int ucData) {
	switch (n) {
		case 0:
			while (!(LPC_UART0->LSR & 0x20));
				return (LPC_UART0->THR = ucData);
		case 1:
			while (!(LPC_UART1->LSR & 0x20));
				return (LPC_UART1->THR = ucData);
		case 2:
			while (!(LPC_UART2->LSR & 0x20));
				return (LPC_UART2->THR = ucData);
		case 3:
			while (!(LPC_UART3->LSR & 0x20));
				return (LPC_UART3->THR = ucData);
		default:
			return 1;
	}
}

/*----------------------------------------------------------------------------
  Read character from Serial Port   (blocking read)
 *----------------------------------------------------------------------------*/
int UARTGetByte (uint8_t n) {
	switch (n) {
		case 0:
			while (!(LPC_UART0->LSR & 0x01));
				return (LPC_UART0->RBR);
		case 1:
			while (!(LPC_UART1->LSR & 0x01));
				return (LPC_UART1->RBR);
		case 2:
			while (!(LPC_UART2->LSR & 0x01));
				return (LPC_UART2->RBR);
		case 3:
			while (!(LPC_UART3->LSR & 0x01));
				return (LPC_UART3->RBR);
		default:
			return 1;
	}
}

/*----------------------------------------------------------------------------
Write character to Serial Port
*  Function name:		UARTSendString
*  Descriptions:		send string to UARTn
*  input parameters:	n, s
*  output parameters:	None
*  Returned value:		None
----------------------------------------------------------------------------*/
void UARTSendString (uint8_t n, unsigned char *s) {
	while (*s != 0) {
		UARTSendByte(n, *s++);
	}
	UARTSendByte(n, '\r');
	UARTSendByte(n, '\n');
}

/*----------------------------------------------------------------------------
Write Decimal to Serial Port
*  Function name:		UARTSendDec
*  Descriptions:		send decimal to UARTn
*  input parameters:	n, disp
*  output parameters:	None
*  Returned value:		None
----------------------------------------------------------------------------*/
void UARTSendDec (uint8_t n, uint32_t disp) {
	uint16_t dispbuf[4];
	uint8_t i;

	dispbuf[3] = disp%10 + '0';
	dispbuf[2] = disp/10%10 + '0';
	dispbuf[1] = disp/10/10%10 + '0';
	dispbuf[0] = disp/10/10/10%10 + '0';
	for(i=0;i<4;i++)
		UARTSendByte(n, dispbuf[i]);
	
	UARTSendByte(n, ' ');
}

/*----------------------------------------------------------------------------
Print infomations to port n
*  Function name:		printf
*  Descriptions:		print infos UARTn
*  input parameters:	n, s, disp
*  output parameters:	None
*  Returned value:		None
----------------------------------------------------------------------------*/
void print (uint8_t n, unsigned char *s, uint32_t disp) {
	uint16_t dispbuf[4];
	uint8_t i;
	
	while (*s != 0) {
		UARTSendByte(n, *s++);
	}
	dispbuf[3] = disp%10 + '0';
	dispbuf[2] = disp/10%10 + '0';
	dispbuf[1] = disp/10/10%10 + '0';
	dispbuf[0] = disp/10/10/10%10 + '0';
	for(i=0;i<4;i++)
		UARTSendByte(n, dispbuf[i]);
	UARTSendByte(n, '\r');
	UARTSendByte(n, '\n');
}

/*------------------------------------------------------------------------------
--                            End Of File
------------------------------------------------------------------------------*/
