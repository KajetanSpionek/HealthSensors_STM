/*
 * sd.c
 *
 *  Created on: Mar 19, 2018
 *      Author: Kajetan Spionek
 */

#include "sd.h"

/* Global SD Card variables */
FATFS fatfs;
FIL myfile;
FRESULT fresult;

/* Getters */
uint8_t SD_getStatus(void) {

	return SDCardInfo.status;
}

uint8_t SD_getIsinserted(void) {

	return SDCardInfo.is_inserted;
}

/* Interrupt handler */
void SD_changedSocket_IT(void) {
	// Check sd_card input;
	// Update SDCardInfo structure
}

/* Basic SDCard integration */
uint8_t SD_mount(void) {

	return f_mount(&fatfs,(TCHAR const*)SD_Path, 1);
}

