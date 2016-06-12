/*----------------------------------------------------------------------------
 *      Skuo LPC1768 12 Ports Decoder
 *----------------------------------------------------------------------------
 *      Name:    i2s.h
 *      Purpose: 12 Ports decoder demo@Fei,Hui
 *----------------------------------------------------------------------------
 *      This code is use the RealView Run-Time Library.
 *      2013-12.05
 *---------------------------------------------------------------------------*/
 
#ifndef __I2S_H 
#define __I2S_H

// buffer size
#define I2SSIZE				0x100
#define HI2SSIZE			0x80

extern int seqnum;
extern uint8_t udprdptr, udpwrptr;
extern volatile uint32_t I2SDMA0Done, I2SDMA1Done,I2SDMA2Done, I2SDMA3Done;
extern volatile uint32_t I2SDMA0Done, I2SDMA1Done;
extern unsigned int AudioFlag;
extern void I2S_IRQHandler	(void);
extern void I2SStart				(void);
extern void I2SStop					(void);
extern uint32_t I2SInit			(void);
extern int enAudio					(void);
extern int disAudio					(void);

#endif

/*------------------------------------------------------------------------------
--                            End Of File
------------------------------------------------------------------------------*/
