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

/* Card status:
 * 0 - Not mounted
 * 1 - Mounted
 * 2 - File is opened
 */

typedef struct {

	uint8_t status;			// Returns SD card status
	uint8_t is_inserted;	// Positive if SD card is inserted in slot
	uint8_t file_name[15];  // Holds name of currently opened file

} SDCardStruct;

SDCardStruct SDCardInfo;

/* SD path variable */
extern char SD_Path[4];

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

/**
   * @brief Called by interrupt when SD card is inserted or removed from socket;
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






#endif /* SD_H_ */
