/*----------------------------------------------------------------------------
 *      Skuo LPC1768 12 Ports Decoder
 *----------------------------------------------------------------------------
 *      Name:    i2s.c
 *      Purpose: 12 Ports decoder demo@Fei,Hui
 *----------------------------------------------------------------------------
 *      This code is use the RealView Run-Time Library.
 *      2013.12.05
 *---------------------------------------------------------------------------*/
 
#include "lpc17xx.h"
#include "rtl.h"
#include "i2s.h"
#include "dma.h"

/* treat I2S TX and RX as a constant address, make the code and buffer 
easier for both DMA and non-DMA test */
unsigned int AudioFlag = __FALSE;
volatile uint8_t *I2STXBuf0 = (uint8_t *)(DMA_I2S_TX0); 
volatile uint8_t *I2STXBuf1 = (uint8_t *)(DMA_I2S_TX1);
volatile uint8_t *I2SRXBuf0 = (uint8_t *)(DMA_I2S_RX0); 
volatile uint8_t *I2SRXBuf1 = (uint8_t *)(DMA_I2S_RX1);

/*----------------------------------------------------------------------------*
-- Function name:		I2SStart
-- Descriptions:		Start I2S DAI and DAO
-- parameters:			None
-- Returned value:	None
-----------------------------------------------------------------------------*/
__STATIC_INLINE void I2SStart (void) {
  uint32_t DAIValue, DAOValue;
  
  /* Audio output is the master, audio input is the master, */
  /* 8 bit data, mono, reset, master mode, not mute. */
  DAOValue = LPC_I2S->I2SDAO;
  DAIValue = LPC_I2S->I2SDAI;
  LPC_I2S->I2SDAO = DAOValue & (~((0x3 << 0)	// 8 bit
	                  //|(0x01 << 2)							// mono
	                  |(0x01 << 3)							// stop = 0
	                  |(0x01 << 4)							// reset = 0
	                  |(0x03 << 9)));						// sample cycle = 16 bit
  /* 8 bit data, mono, reset, master mode, not mute. */
  LPC_I2S->I2SDAI = DAIValue & (~((0x3 << 0)	// 8 bit
	                  //|(0x01 << 2)							// mono
	                  |(0x01 << 3)							// stop = 0
	                  |(0x01 << 4)							// reset = 0
	                  //|(0x01<<5)								// mode = master
	                  |(0x03 << 9)));						// sample cycle = 16 bit
	//LPC_I2S->I2STXMODE |= 0x2;
  return;
}

/*---------------------------------------------------------------------------*
-- Function name:		I2SStop
-- Descriptions:		Stop I2S DAI and DAO
-- parameters:			None
-- Returned value:	None
----------------------------------------------------------------------------*/
__STATIC_INLINE void I2SStop (void) {
	uint32_t i;
  uint32_t DAIValue, DAOValue;

  /* Stop the I2S to start. Audio output is master, audio input is the slave. */
  /* 16 bit data, set STOP and RESET bits to reset the channels */
  DAOValue = LPC_I2S->I2SDAO;
  /* Switch to master mode, TX channel, no mute */
  DAOValue &= ~((0x01 << 5)|(0x01 << 15));
  DAIValue = LPC_I2S->I2SDAI;
  DAIValue &= ~(0x01 << 15);
  LPC_I2S->I2SDAO = (0x01 << 4) | (0x01 << 3) | DAOValue;	/* Master */
  LPC_I2S->I2SDAI = (0x01 << 4) | (0x01 << 3) | DAIValue;	/* Slave */
	I2SDMA0Done = 1;
	I2SDMA1Done = 1;
	I2SDMA2Done = 0;
	I2SDMA3Done = 0;
	for (i=0; i<I2SSIZE; i++) {
		I2STXBuf0[i] = 0xD5;
		I2STXBuf1[i] = 0xD5;
		I2SRXBuf0[i] = 0xD5;
		I2SRXBuf1[i] = 0xD5;
  }
  return;
}

/*---------------------------------------------------------------------------*
-- Function name:		I2SInit
-- Descriptions:		Initialize I2S controller
-- parameters:			None
-- Returned value:	true or false, return false if the I2S
--									interrupt handler was not installed correctly
----------------------------------------------------------------------------*/
uint32_t I2SInit (void) {
  /*enable I2S in the PCONP register. I2S is disabled on reset*/
  LPC_SC->PCONP |= (1 << 27);

  /*connect the I2S sigals to port pins(P0.4-P0.9)*/
  LPC_PINCON->PINSEL0 &= ~0x000FFF00;
  LPC_PINCON->PINSEL0 |= 0x00055500;

  /* Please note, in order to generate accurate TX/RX clock rate for I2S, 
  PCLK and CCLK needs to be carefully reconsidered. For this test 
  program, the TX is looped back to RX without external I2S device, 
  clock rate is not critical in this matter. */
  //LPC_I2S->I2STXRATE = 0x1FFD; //0x1FFD:1.536Mbps 0X057A:512Kbps 0x05F4:256Kbps 0x02C3:128Kbps
  //LPC_I2S->I2SRXRATE = 0x1FFD;
	LPC_I2S->I2STXRATE = 0x02C3;
	LPC_I2S->I2SRXRATE = 0x02C3;

  I2SStop();
	
  return 1;
}

/*---------------------------------------------------------------------------*
-- Function name:		enAudio
-- Descriptions:		enable stream for I2S Tx & Rx
-- parameters:			None
-- Returned value:	true or false, return false if the I2S
--									interrupt handler was not installed correctly
----------------------------------------------------------------------------*/
int enAudio (void) {
	I2SStart();
	LPC_I2S->I2SDMA2 = (0x01<<0) | (0x08<<8);		//enable audio stream rx
	LPC_I2S->I2SDMA1 = (0x01<<1) | (0x01<<16);	//enable tx
	return 0;
}

/*---------------------------------------------------------------------------*
-- Function name:		disAudio
-- Descriptions:		disaable stream for I2S Tx & Rx
-- parameters:			None
-- Returned value:	true or false, return false if the I2S
--									interrupt handler was not installed correctly
----------------------------------------------------------------------------*/
int disAudio (void) {
	I2SStop();
	DMADisable();
	udpwrptr = 10;
	udprdptr = 0;
	seqnum = 0;
	AudioFlag = __FALSE;
	return 0;
}

/*------------------------------------------------------------------------------
--                            End Of File
------------------------------------------------------------------------------*/
