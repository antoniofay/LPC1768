/*----------------------------------------------------------------------------
 *      Skuo LPC1768 12 Ports Decoder
 *----------------------------------------------------------------------------
 *      Name:    iap.c
 *      Purpose: 12 Ports decoder demo@Fei,Hui
 *----------------------------------------------------------------------------
 *      This code is use the RealView Run-Time Library.
 *      2013.12.05
 *---------------------------------------------------------------------------*/
 
#include <string.h>
#include <iap.h>
#include <lpc17xx.h>
#include <Net_Config.h>
#include <adc.h>
#include <uart.h>
/* IAP Command Definitions */
#define	IAP_CMD_PREPARE_SECTORS				50
#define	IAP_CMD_COPY_RAM_TO_FLASH			51
#define	IAP_CMD_ERASE_SECTORS					52
#define	IAP_CMD_BLANK_CHECK_SECTORS		53
#define	IAP_CMD_READ_PART_ID					54
#define	IAP_CMD_READ_BOOT_ROM_VERSION	55
#define	IAP_CMD_COMPARE								56
#define	IAP_CMD_REINVOKE_ISP					57
#define IAP_CMD_READ_SERIAL_NUMBER		58

/* IAP boot ROM location and access function */
#define IAP_ROM_LOCATION				0x1FFF1FF1UL
#define IAP_EXECUTE_CMD(a, b)			((void (*)())(IAP_ROM_LOCATION))(a, b)

uint8_t table[512];

extern LOCALM nlocalm;
extern struct RemotePeer {
	uint8_t	 IP[4];
	uint16_t Port;
} Server, Admin;
extern struct RemotePeer Outdoor;
#define PortNum       12

/*----------------------------------------------------------------------------
*  Function name:		refresh_update
*  Descriptions:		save configuration data and restart system
*  parameters:			None
*  Returned value:	None
----------------------------------------------------------------------------*/
void refresh_update (uint32_t flag) {
	uint32_t i = 0;
	__disable_irq ();
	
	table[0] = flag;																											//set update flag
	memcpy(table + 1, &nlocalm, sizeof(nlocalm));													//copy IP table
	memcpy(table + sizeof(nlocalm) + 1, &indoor, sizeof(indoor)); 				//copy room/port mapping
	memcpy(table + sizeof(nlocalm) + sizeof(indoor) + 1, &Server.IP, sizeof(Server.IP));
	memcpy(table + sizeof(nlocalm) + sizeof(indoor) + sizeof(Server.IP) + 1, &Admin.IP, sizeof(Admin.IP));
	memcpy(table + sizeof(nlocalm) + sizeof(indoor) + sizeof(Server.IP) + sizeof(Admin.IP) + 1, &Outdoor.IP, sizeof(Outdoor.IP));
	
	if (PrepareSectors(UPDATE_SECTOR, UPDATE_SECTOR) == CMD_SUCCESS) {
		if (EraseSectors (UPDATE_SECTOR, UPDATE_SECTOR) == CMD_SUCCESS) {
			if (PrepareSectors(UPDATE_SECTOR, UPDATE_SECTOR) == CMD_SUCCESS) {
				if (CopyRAMToFlash(UPDATE_SECTOR_ADDRESS, (uint32_t)&table, 512) == CMD_SUCCESS) {
					if(flag) {
						for(i=0; i<0x6FFFFFF; i++);																					//delay 6s
					}
					NVIC_SystemReset();
				}
			}
		}
	}
}

/*----------------------------------------------------------------------------
*  Function name:		restore_config
*  Descriptions:		restore IP address and room/port mapping
*  parameters:			None
*  Returned value:	None
----------------------------------------------------------------------------*/
void restore_config (void) {
	int i, N = sizeof(nlocalm) + sizeof(indoor) + sizeof(Server.IP) + sizeof(Admin.IP) + sizeof(Outdoor.IP) + 1;
	uint32_t result[3];
	
	for(i=0; i<PortNum; i++) {
		indoor[i].room = 101 + i;
		indoor[i].port = i + 1;
	}
	
	//read flash data to table
	for (i=0; i<N; i++) {
		table[i] = *(uint8_t *)(UPDATE_SECTOR_ADDRESS + i);
	}
	
	//fill the config infos
	if (BlankCheckSectors(UPDATE_SECTOR, UPDATE_SECTOR, result) == SECTOR_NOT_BLANK) {
		memcpy(&nlocalm, table + 1, sizeof(nlocalm));
		memcpy(&indoor, table + sizeof(nlocalm) + 1, sizeof(indoor));
		memcpy(&Server.IP, table + sizeof(nlocalm) + sizeof(indoor) + 1, sizeof(Server.IP));
		memcpy(&Admin.IP, table + sizeof(nlocalm) + sizeof(indoor) + sizeof(Server.IP) + 1, sizeof(Admin.IP));
		memcpy(&Outdoor.IP, table + sizeof(nlocalm) + sizeof(indoor) + sizeof(Server.IP) + sizeof(Admin.IP) + 1, sizeof(Outdoor.IP));
	}
	Server.IP[0]=0xC0;
	for(i=0; i<PortNum; i++) {
		memset(&indoor[i].keyval, 0, sizeof(indoor[i].keyval));
		memset(&indoor[i].state, 0, sizeof(indoor[i].state));
	}
}

/**----------------------------------------------------------------------------
** Function name:	u32IAP_PrepareSectors
**
** Description:		Prepares sector(s) for erasing or write operations. This
** 					command must be executed before executing the "Copy RAM to
** 					Flash" or "Erase Sector(s)" commands.
**
** Parameters:		u32StartSector - Number of first sector to prepare.
** 					u32EndSector - Number of last sector to prepare.
**
** Returned value:	Status code returned by IAP ROM function.
**
----------------------------------------------------------------------------**/
uint32_t PrepareSectors (uint32_t u32StartSector, uint32_t u32EndSector) {
	uint32_t u32Status;
	uint32_t au32Result[5];
	uint32_t au32Command[5];

	if (u32EndSector < u32StartSector) {
		u32Status = INVALD_PARAM;
	}
	else {
		au32Command[0] = IAP_CMD_PREPARE_SECTORS;
		au32Command[1] = u32StartSector;
		au32Command[2] = u32EndSector;

		IAP_EXECUTE_CMD(au32Command, au32Result);

		u32Status = au32Result[0];
	}
	return u32Status;
}

/**----------------------------------------------------------------------------
** Function name:	u32IAP_CopyRAMToFlash  IAP RAM->Flash
**
** Description:		Program the flash memory with data stored in RAM.
**
** Parameters:	   	u32DstAddr - Destination Flash address, should be a 256
**                               byte boundary.
**			 		u32SrcAddr - Source RAM address, should be a word boundary
**			 		u32Len     - Number of 8-bit bytes to write, must be 256
**								 512, 1024, or 4096.
*
** Returned value:	Status code returned by IAP ROM function.
**
----------------------------------------------------------------------------**/
uint32_t CopyRAMToFlash (uint32_t u32DstAddr, uint32_t u32SrcAddr, uint32_t u32Len) {
	uint32_t au32Result[5];
	uint32_t au32Command[5];

	au32Command[0] = IAP_CMD_COPY_RAM_TO_FLASH;
	au32Command[1] = u32DstAddr;
	au32Command[2] = u32SrcAddr;
	au32Command[3] = u32Len;
//	au32Command[4] = SystemFrequency / 1000UL;	/* Core clock frequency in kHz */
	
	au32Command[4] = SystemCoreClock / 1000UL;
	IAP_EXECUTE_CMD(au32Command, au32Result);
	return au32Result[0];
}

/**----------------------------------------------------------------------------
** Function name:	u32IAP_EraseSectors
**
** Description:		Erase a sector or multiple sectors of on-chip Flash memory.
**
** Parameters:		u32StartSector - Number of first sector to erase.
** 					u32EndSector - Number of last sector to erase.
*
** Returned value:	Status code returned by IAP ROM function.
**
----------------------------------------------------------------------------**/
uint32_t EraseSectors (uint32_t u32StartSector, uint32_t u32EndSector) {
	uint32_t u32Status;
	uint32_t au32Result[5];
	uint32_t au32Command[5];

	if (u32EndSector < u32StartSector) {
		u32Status = INVALD_PARAM;
	}
	else {
		au32Command[0] = IAP_CMD_ERASE_SECTORS;
		au32Command[1] = u32StartSector;
		au32Command[2] = u32EndSector;
//		au32Command[3] = SystemFrequency / 1000UL;	/* Core clock frequency in kHz */
   	    au32Command[3] = SystemCoreClock / 1000UL;
		IAP_EXECUTE_CMD(au32Command, au32Result);

		u32Status = au32Result[0];
	}
	return u32Status;
}

/**----------------------------------------------------------------------------
** Function name:	u32IAP_BlankCheckSectors
**
** Description:		Blank check a sector or multiple sectors of on-chip flash
** 					memory.
**
** Parameters:		u32StartSector - Number of first sector to check.
** 					u32EndSector - Number of last sector to check.
** 					pu32Result[0] - Offset of the first non blank word location
**                  if the Status Code is SECTOR_NOT_BLANK.
** 					pu32Result[1] - Contents of non blank word location.
**
** Returned value:	Status code returned by IAP ROM function.
**
----------------------------------------------------------------------------**/
uint32_t BlankCheckSectors (uint32_t u32StartSector, uint32_t u32EndSector, uint32_t *pu32Result) {
	uint32_t u32Status;
	uint32_t au32Result[5];
	uint32_t au32Command[5];

	if (u32EndSector < u32StartSector) {
		u32Status = INVALD_PARAM;
	}
	else {
		au32Command[0] = IAP_CMD_BLANK_CHECK_SECTORS;
		au32Command[1] = u32StartSector;
		au32Command[2] = u32EndSector;

		IAP_EXECUTE_CMD(au32Command, au32Result);

		if (au32Result[0] == SECTOR_NOT_BLANK) {
			*pu32Result       = au32Result[0];
			*(pu32Result + 1) = au32Result[1];
		}
		u32Status = au32Result[0];
	}
	return u32Status;
}

/**----------------------------------------------------------------------------
** Function name:	u32IAP_ReadPartID
**
** Description:		Read the part identification number.
**
** Parameters:		pu32PartID - Pointer to storage for part ID number.
*
** Returned value:	Status code returned by IAP ROM function.
**
----------------------------------------------------------------------------**/
uint32_t ReadPartID (uint32_t *pu32PartID) {
	uint32_t au32Result[5];
	uint32_t au32Command[5];

	au32Command[0] = IAP_CMD_READ_PART_ID;

	IAP_EXECUTE_CMD(au32Command, au32Result);

	*pu32PartID = au32Result[1];

	return au32Result[0];
}

/**----------------------------------------------------------------------------
** Function name:	u32IAP_ReadBootVersion
**
** Description:		Read the boot code version number.
**
** Parameters:		pu32Major - Major version number in ASCII format.
** 					pu32Minor - Minor version number in ASCII format.
**
** Returned value:	Status code returned by IAP ROM function.
**
----------------------------------------------------------------------------**/
uint32_t ReadBootVersion (uint32_t *pu32Major, uint32_t *pu32Minor) {
	uint32_t au32Result[5];
	uint32_t au32Command[5];

	au32Command[0] = IAP_CMD_READ_BOOT_ROM_VERSION;

	IAP_EXECUTE_CMD(au32Command, au32Result);

	*pu32Major = (au32Result[1] & 0x0000FF00UL) >> 8;
	*pu32Minor = au32Result[1] & 0x000000FFUL;

	return au32Result[0];
}

/**----------------------------------------------------------------------------
** Function name:	u32IAP_ReadBootVersion
**
** Description:		Read the boot code version number.
**
** Parameters:		pu32Major - Major version number in ASCII format.
** 					pu32Minor - Minor version number in ASCII format.
**
** Returned value:	Status code returned by IAP ROM function.
**
----------------------------------------------------------------------------**/
void ReadSerialNumber (uint32_t *pu32byte0, uint32_t *pu32byte1,
											 uint32_t *pu32byte2, uint32_t *pu32byte3) {
	uint32_t au32Result[5];
	uint32_t au32Command[5];

	au32Command[0] = IAP_CMD_READ_SERIAL_NUMBER;

	IAP_EXECUTE_CMD(au32Command, au32Result);

	*pu32byte0 = au32Result[0];
	*pu32byte1 = au32Result[1];
	*pu32byte2 = au32Result[2];
	*pu32byte3 = au32Result[3];

	return;
}

/**----------------------------------------------------------------------------
** Function name:	u32IAP_Compare
**
** Description:		Compares the memory contents at two locations.
**
** Parameters:		u32Len - Number of bytes to compare, must be a multiple of 4.
**					pu32Offset - Offset of the first mismatch if the Status Code is COMPARE_ERROR
**
** Returned value:	Status code returned by IAP ROM function.
**
----------------------------------------------------------------------------**/
uint32_t Compare (uint32_t u32DstAddr, uint32_t u32SrcAddr,
									uint32_t u32Len, uint32_t *pu32Offset) {
	uint32_t au32Result[5];
	uint32_t au32Command[5];

	au32Command[0] = IAP_CMD_COMPARE;
	au32Command[1] = u32DstAddr;
	au32Command[2] = u32SrcAddr;
	au32Command[3] = u32Len;

	IAP_EXECUTE_CMD(au32Command, au32Result);

	if (au32Result[0] == COMPARE_ERROR) {
		if (pu32Offset != 0) {
			*pu32Offset = au32Result[1];
		}
	}
	return au32Result[0];
}

/**----------------------------------------------------------------------------
** Function name:	vIAP_ReinvokeISP
**
** Description:		Invoke the bootloader in ISP mode.
**
** Parameters:		None.
*
** Returned value:	None.
**
----------------------------------------------------------------------------**/
void ReinvokeISP (void) {
	uint32_t au32Result[5];
	uint32_t au32Command[5];

	au32Command[0] = IAP_CMD_REINVOKE_ISP;

	IAP_EXECUTE_CMD(au32Command, au32Result);
}

/*------------------------------------------------------------------------------
--                            End Of File
------------------------------------------------------------------------------*/
