/*
 * sd.h
 *
 *  Created on: Mar 19, 2018
 *      Author: Kajetan Spionek
 */

#ifndef SD_H_
#define SD_H_

#include "stm32l1xx_hal.h"
#include "fatfs.h"

#define SD_READ_BUFF 20

/* Card status:
 * 0 - Not mounted
 * 1 - Mounted
 * 2 - File is opened
 */

typedef struct {

	uint8_t status;			// Returns SD card status
	uint8_t is_inserted;	// Positive if SD card is inserted in slot

} SDCardStruct;

SDCardStruct SDInfo;

/* SD path variable */
char SD_Path[4];
extern UART_HandleTypeDef huart1;

/**
   * @brief SDCardInfo getter, returns status value
   * @param None
   * @retval status: 0 not mounted, 1 mounted, 2 file is opened
*/
uint8_t SD_getStatus(void);

/**
   * @brief SDCardInfo getter, returns is_inserted value
   * @param None
   * @retval status: 0 inserted, 1 not inserted
*/
uint8_t SD_getIsinserted(void);
void SD_setStatus(uint8_t status);
void SD_setIsinserted(uint8_t status);

/**
   * @brief Called by interrupt when SD card is inserted or removed from socket
   * @param None
   * @retval None
*/
void SD_changedSocket(void);

/**
   * @brief Mounts SDCard
   * @param None
   * @retval status: 0 positive outcome, 1 negative outcome
*/
uint8_t SD_mount(void);

uint8_t SD_makeDirectory(uint8_t* name);
uint8_t SD_closeFile(void);
uint8_t SD_openFile(uint8_t* path);
uint8_t SD_createFile(uint8_t* path);
uint8_t SD_movePtrToEnd(void);
void SD_readLine(uint8_t* data, uint8_t* length);
void SD_savePpg(uint32_t* red, uint32_t* ir);
void SD_savePpgEncrypted(uint32_t* data);




#endif /* SD_H_ */
