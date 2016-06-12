/*----------------------------------------------------------------------------
 *      Skuo LPC1768 12 Ports Decoder
 *----------------------------------------------------------------------------
 *      Name:    dma.h
 *      Purpose: 12 Ports decoder demo@Fei,Hui
 *----------------------------------------------------------------------------
 *      This code is use the RealView Run-Time Library.
 *      2013-12.05
 *---------------------------------------------------------------------------*/
 
#ifndef __DMA_H 
#define __DMA_H

// dma source and destination
#define DMA_I2S_TX0			0x20080000	
#define DMA_I2S_TX1			0x20080100
#define DMA_I2S_RX0     0x20080200
#define DMA_I2S_RX1     0x20080300
// I2S Tx/Rx FIFO address
#define DMA_I2S_TX_FIFO	0x400A8008
#define	DMA_I2S_RX_FIFO	0x400A800C

// dma data size
#define DMA_SIZE		0x40

// DMA mode
#define M2M				0x00
#define M2P				0x01
#define P2M				0x02
#define P2P				0x03

extern void DMA_IRQHandler	(void);
extern uint32_t DMAConfig		(void);
extern uint32_t DMADisable	(void);
extern uint32_t DMAInit			(uint32_t ChannelNum, uint32_t DMAMode);

#endif

/*------------------------------------------------------------------------------
--                            End Of File
------------------------------------------------------------------------------*/
