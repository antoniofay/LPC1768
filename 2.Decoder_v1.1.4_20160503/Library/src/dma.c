/*----------------------------------------------------------------------------
 *      Skuo LPC1768 12 Ports Decoder
 *----------------------------------------------------------------------------
 *      Name:    dma.c
 *      Purpose: 12 Ports decoder demo@Fei,Hui
 *----------------------------------------------------------------------------
 *      This code is use the RealView Run-Time Library.
 *      2013.12.05
 *---------------------------------------------------------------------------*/
 
#include "lpc17xx.h"
//#include "i2s.h"
#include "dma.h"

volatile uint32_t DMATCCount  = 0;
volatile uint32_t DMAErrCount = 0;
volatile uint32_t I2SDMA0Done = 1;
volatile uint32_t I2SDMA1Done = 1;
volatile uint32_t I2SDMA2Done = 0;
volatile uint32_t I2SDMA3Done = 0;

/*-----------------------------------------------------------------------------
-- Function name:		DMA_IRQHandler
-- Descriptions:		DMA interrupt handler
-- parameters:			None
-- Returned value:	None
-----------------------------------------------------------------------------*/
void DMA_IRQHandler (void) {
  uint32_t regVal;

  regVal = LPC_GPDMA->DMACIntTCStat;
  if (regVal) {
		DMATCCount++;
		LPC_GPDMA->DMACIntTCClear |= regVal;
		if (regVal & 0x01) {
			DMAInit(1, M2P);
			LPC_GPDMACH1->DMACCConfig |= 0x18001			// enable channel, ITC = 1, L = 1
																| (0x00 << 1)		// SSP0Tx
																| (0x05 << 6)		// dest peripheral = I2S0
																| (0x01 << 11);	// memory to peripheral
			I2SDMA0Done = 1;
		}
		else if (regVal & 0x02) {
			DMAInit(0, M2P);
			LPC_GPDMACH0->DMACCConfig |= 0x18001			// enable channel, ITC = 1, L = 1
																| (0x00 << 1)		// SSP0Tx
																| (0x05 << 6)		// dest peripheral = I2S0
																| (0x01 << 11);	// memory to peripheral
			I2SDMA1Done = 1;
		}
		else if (regVal & 0x04) {
			DMAInit(3, P2M);
			LPC_GPDMACH3->DMACCConfig |= 0x08001			// enable channel, ITC = 1
																| (0x06 << 1)		// source peripheral = I2S1
																| (0x00 << 6)		// SSP0Tx
																| (0x02 << 11);	// peripheral to memory
			I2SDMA2Done = 1;
		}
		else if (regVal & 0x08) {
			DMAInit(2, P2M);
			LPC_GPDMACH2->DMACCConfig |= 0x08001			// enable channel, ITC = 1
																| (0x06 << 1)		// source peripheral = I2S1
																| (0x00 << 6)		// SSP0Tx
																| (0x02 << 11);	// peripheral to memory
			I2SDMA3Done = 1;
		}
  } 

  regVal = LPC_GPDMA->DMACIntErrStat;
  if (regVal) {
		DMAErrCount++;
		LPC_GPDMA->DMACIntErrClr |= regVal;
  }
}

/*-----------------------------------------------------------------------------
-- Function name:		DMAInit
-- Descriptions:
-- parameters:	
-- Returned value:
-----------------------------------------------------------------------------*/
uint32_t DMAInit (uint32_t ChannelNum, uint32_t DMAMode) {
  if (ChannelNum == 0) {
		LPC_GPDMA->DMACIntTCClear = 0x01;   
		if (DMAMode == M2P) {
			/* Ch0 set for M2P transfer from memory to I2S TX FIFO. */
			LPC_GPDMACH0->DMACCSrcAddr = DMA_I2S_TX0;
			LPC_GPDMACH0->DMACCDestAddr = DMA_I2S_TX_FIFO;
			/* The burst size is set to 1. Terminal Count Int enable */
			LPC_GPDMACH0->DMACCControl = (DMA_SIZE & 0x0FFF) 
		                             | (0x00 << 12)			// source burst size: 1
		                             | (0x00 << 15)			// dest burst size: 1
		                             | (0x02 << 18)			// source transmit data width: 32 bits
		                             | (0x02 << 21)			// dest transmit data width: 32 bits
		                             | (0x01 << 26)			// source address increment
		                             | 0x80000000;			// enable count interrupt
		}
		else {
			return 0;
		}
  }
  else if (ChannelNum == 1) {   
		LPC_GPDMA->DMACIntTCClear = 0x02;
		if (DMAMode == M2P) {
			/* Ch1 set for M2P transfer from mempry to I2S TX FIFO. */
			LPC_GPDMACH1->DMACCSrcAddr = DMA_I2S_TX1;
			LPC_GPDMACH1->DMACCDestAddr = DMA_I2S_TX_FIFO;
			/* The burst size is set to 1. Terminal Count Int enable. */
			LPC_GPDMACH1->DMACCControl = (DMA_SIZE & 0x0FFF)
		                             | (0x00 << 12)			// source burst size: 1
		                             | (0x00 << 15)			// dest burst size: 1
		                             | (0x02 << 18)			// source transmit data width: 32 bits
		                             | (0x02 << 21)			// dest transmit data width: 32 bits
		                             | (0x01 << 26)			// source address increment
		                             | 0x80000000;			// enable count interrupt
		}
		else {
			return 0;
		}
  }
	else if (ChannelNum == 2) {   
		LPC_GPDMA->DMACIntTCClear = 0x04;
		if (DMAMode == P2M) {
			/* Ch1 set for P2M transfer from I2S RX FIFO to memory. */
			LPC_GPDMACH2->DMACCSrcAddr = DMA_I2S_RX_FIFO;
			LPC_GPDMACH2->DMACCDestAddr = DMA_I2S_RX0;
			/* The burst size is set to 1. Terminal Count Int enable. */
			LPC_GPDMACH2->DMACCControl = (DMA_SIZE & 0x0FFF) 
		                             | (0x00 << 12)			// source burst size: 1
		                             | (0x00 << 15)			// dest burst size: 1
		                             | (0x02 << 18)			// source transmit data width: 32 bits
		                             | (0x02 << 21)			// dest transmit data width: 32 bits
		                             | (0x01 << 27)			// source address increment
		                             | 0x80000000;			// enable count interrupt
		}
		else {
			return 0;
		}
  }
	else if (ChannelNum == 3) {   
		LPC_GPDMA->DMACIntTCClear = 0x08;
		if (DMAMode == P2M) {
			/* Ch1 set for P2M transfer from I2S RX FIFO to memory. */
			LPC_GPDMACH3->DMACCSrcAddr = DMA_I2S_RX_FIFO;
			LPC_GPDMACH3->DMACCDestAddr = DMA_I2S_RX1;
			/* The burst size is set to 1. Terminal Count Int enable. */
			LPC_GPDMACH3->DMACCControl = (DMA_SIZE & 0x0FFF)
		                             | (0x00 << 12)			// source burst size: 1
		                             | (0x00 << 15)			// dest burst size: 1
		                             | (0x02 << 18)			// source transmit data width: 32 bits
		                             | (0x02 << 21)			// dest transmit data width: 32 bits
		                             | (0x01 << 27)			// source address increment
		                             | 0x80000000;			// enable count interrupt
		}
		else {
			return 0;
		}
  }
  return 1;
}

/*---------------------------------------------------------------------------*
-- Function name:		DMADisable
-- Descriptions:		Disable DMA transfer
-- parameters:			None
-- Returned value:	true or false, return false if the I2S
--									interrupt handler was not installed correctly
----------------------------------------------------------------------------*/
uint32_t DMADisable (void) {
	LPC_SC->PCONP &= ~(1 << 29);
	LPC_GPDMA->DMACConfig &= ~(1 << 0);
	NVIC_DisableIRQ(DMA_IRQn);
	return 1;
}
	
/*---------------------------------------------------------------------------*
-- Function name:		DMAConfig
-- Descriptions:		Configure DMA for I2S Tx & Rx
-- parameters:			None
-- Returned value:	true or false, return false if the I2S
--									interrupt handler was not installed correctly
----------------------------------------------------------------------------*/
uint32_t DMAConfig (void) {
	/* USB RAM is used for test.
  Please note, Ethernet has its own SRAM, but GPDMA can't access
  that. GPDMA can access USB SRAM and IRAM. Ethernet DMA controller can 
  access both IRAM and Ethernet SRAM. */
  LPC_SC->PCONP |= (1 << 29);	/* Enable GPDMA clock */
	
  LPC_GPDMA->DMACIntTCClear = 0x0F;
  LPC_GPDMA->DMACIntErrClr = 0x0F;

  LPC_GPDMA->DMACConfig = 0x01;	/* Enable DMA channels, little endian */
  while (!(LPC_GPDMA->DMACConfig & 0x01));

  /* on DMA channel 0, Source is memory, destination is I2S TX FIFO, 
  on DMA channel 1, source is I2S RX FIFO, Destination is memory */
  /* Enable channel and IE bit */
  DMAInit(0, M2P);
  LPC_GPDMACH0->DMACCConfig |= 0x18001			// enable channel, ITC = 1, L = 1
	                          | (0x00 << 1)		// source = memory, ignored
	                          | (0x05 << 6)		// dest peripheral = I2S0
	                          | (0x01 << 11);	// memory to peripheral
  DMAInit(2, P2M);
  LPC_GPDMACH2->DMACCConfig |= 0x08001			// enable channel, ITC = 1
	                          | (0x06 << 1)		// source peripheral = I2S1
														| (0x00 << 6)		// destination = memory, ignored
														| (0x02 << 11);	// peripheral to memory
  
  NVIC_EnableIRQ(DMA_IRQn);
	return 1;
}

/*------------------------------------------------------------------------------
--                            End Of File
------------------------------------------------------------------------------*/
