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

	return SDInfo.status;
}

uint8_t SD_getIsinserted(void) {

	return SDInfo.is_inserted;
}

/* Setters */
void SD_setStatus(uint8_t status) {

	SDInfo.status = status;
}

void SD_setIsinserted(uint8_t status) {

	SDInfo.is_inserted = status;
}

/* Interrupt handler */
void SD_changedSocket_IT(void) {
	// Check sd_card input and update SDStructure
	SD_setIsinserted(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13));
}

/* Basic SDCard integration */
uint8_t SD_mount(void) {

	return f_mount(&fatfs,(TCHAR const*)SD_Path, 1);
}

uint8_t SD_makeDirectory(uint8_t* name) {

	return f_mkdir((TCHAR const*)name);
}

uint8_t SD_closeFile(void) {

	return f_close(&myfile);
}

uint8_t SD_openFile(uint8_t* path) {

	return f_open(&myfile,(TCHAR const*)path, FA_OPEN_ALWAYS | FA_WRITE | FA_READ);
}

uint8_t SD_createFile(uint8_t* path) {

	return f_open(&myfile, (TCHAR const*)path, FA_CREATE_NEW | FA_WRITE | FA_READ);
}

uint8_t SD_movePtrToEnd(void) {

	return f_lseek(&myfile, f_size(&myfile));
}

void SD_readLine(uint8_t* data, uint8_t* length) {

	uint8_t _cnt = 0;
	uint8_t value = 0;
	UINT* bytes_read = 0;

	while(_cnt < SD_READ_BUFF) {
		f_read(&myfile, &value, 1, bytes_read);
		if (value == 13 || value == 10) break;
		data[_cnt] = value;
		_cnt++;
	}
	*length = _cnt;
}

void SD_savePpg(uint32_t* red_stash, uint32_t* ir_stash) {

	uint32_t static byteswritten;
	uint8_t static wtext[30];
	uint8_t static  msg_size = 0;
	for(uint8_t _i = 0; _i<10; _i++) {
		msg_size = sprintf(wtext,  "%lu,%lu\r\n", *(red_stash + _i), *(ir_stash + _i));
		f_write(&myfile, wtext, msg_size, (void*)&byteswritten);
	}
}

void SD_savePpgEncrypted(uint32_t* data) {

	uint32_t static byteswritten;
	uint8_t static wtext[20];
	uint8_t static  msg_size = 0;
	for(uint8_t _i = 0; _i<4; _i++) {
			msg_size = sprintf(wtext,  "%08lx ", *(data+_i));
			f_write(&myfile, wtext, msg_size, (void*)&byteswritten);
	}
}

uint8_t SD_streamFilePpg(uint8_t* path, uint8_t* data, uint8_t offset) {

	SD_openFile(path);
	UINT* bytes_read = 0;
	uint32_t eof = f_size(&myfile);

	if(offset*16 >= eof) {
		f_close(&myfile);
		return 1;
	}
	else {
		f_lseek(&myfile, offset*16);
		f_read(&myfile, data, 16, bytes_read); // 4 bytes = 1 sample; 4 samples = 16 bytes
		f_close(&myfile);
		return 0;
	}
}








