/*----------------------------------------------------------------------------
 *      Skuo LPC1768 12 Ports Decoder
 *----------------------------------------------------------------------------
 *      Name:    iap.h
 *      Purpose: 12 Ports decoder demo@Fei,Hui
 *----------------------------------------------------------------------------
 *      This code is use the RealView Run-Time Library.
 *      2013-12.05
 *---------------------------------------------------------------------------*/
 
#ifndef __IAP_H
#define	__IAP_H

#include <stdint.h>

/* IAP Command Status Codes */
#define UPDATE_SECTOR	29
#define UPDATE_SECTOR_ADDRESS	0x78000
#define CMD_SUCCESS										0
#define INVALID_COMMAND								1
#define SRC_ADDR_ERROR								2
#define DST_ADDR_ERROR								3
#define SRC_ADDR_NOT_MAPPED						4
#define DST_ADDR_NOT_MAPPED						5
#define COUNT_ERROR										6
#define INVALID_SECTOR								7
#define SECTOR_NOT_BLANK							8
#define SECTOR_NOT_PREPARED_FOR_WRITE_OPERATION	9
#define COMPARE_ERROR									10
#define BUSY													11
#define INVALD_PARAM									12

/* Define the flash page size, this is the minimum amount of data can be written in one operation */
#define IAP_FLASH_PAGE_SIZE_BYTES							256
#define IAP_FLASH_PAGE_SIZE_WORDS							(IAP_FLASH_PAGE_SIZE_BYTES >> 2)

extern uint8_t MAC[6];

extern void ReinvokeISP(void);
extern uint32_t ReadPartID					(uint32_t *pu32PartID);
extern uint32_t ReadBootVersion		(uint32_t *pu32Major, uint32_t *pu32Minor);
extern uint32_t EraseSectors				(uint32_t u32StartSector, uint32_t u32EndSector);
extern uint32_t PrepareSectors			(uint32_t u32StartSector, uint32_t u32EndSector);
extern uint32_t CopyRAMToFlash			(uint32_t u32DstAddr, uint32_t u32SrcAddr, uint32_t u32Len);
extern uint32_t BlankCheckSectors	(uint32_t u32StartSector, uint32_t u32EndSector, uint32_t *pu32Result);
extern uint32_t Compare						(uint32_t u32DstAddr, uint32_t u32SrcAddr, uint32_t u32Len, uint32_t *pu32Offset);
extern void ReadSerialNumber				(uint32_t *pu32byte0, uint32_t *pu32byte1, uint32_t *pu32byte2, uint32_t *pu32byte3);
extern void refresh_update (uint32_t flag);
extern void restore_config(void);
extern void sleep(uint32_t time);

#endif

/*------------------------------------------------------------------------------
--                            End Of File
------------------------------------------------------------------------------*/
