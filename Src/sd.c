/*
 * sd.c
 *
 *  Created on: Mar 19, 2018
 *      Author: Kajetan Spionek
 */

#include "sd.h"

// Global SD Card variables
FATFS fatfs;
FIL myfile;
FRESULT fresult;

uint8_t SD_getStatus(void) {

	return SDCardInfo.status;
}

uint8_t SD_getIsinserted(void) {

	return SDCardInfo.is_inserted;
}

uint8_t isInserted(void) {

	return 0;
}

uint8_t SD_mount(void) {

	return f_mount(&fatfs,(TCHAR const*)SD_Path, 1);
}
