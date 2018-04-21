/*
 * control.c
 *
 *  Created on: Mar 26, 2018
 *      Author: Kajetan Spionek
 */

#include "control.h"

void CONTROL_initHandler(void) {
	// Initialize PPG
	MAX30102_init();
	// Mount SD card
	SD_mount();
	// Create directories (if do not exists)
	// for ecg data
	SD_makeDirectory((uint8_t*) "ecg");
	// for ppg red data
	SD_makeDirectory((uint8_t*) "ppg_red");
	// for ppg ir data
	SD_makeDirectory((uint8_t*) "ppg_ir");
	// Set PcbVersion
	DEVICE_setPcbVersion((float) 1.3);
	// Set software version
	DEVICE_setSoftVersion((float) 0);
	// Set wifi status
	DEVICE_setWifiConnected(0);
	// Set cloud status
	DEVICE_setCloudInitialized(0);
}

void CONTROL_idleHandler(void) {

	// Wait for alarm interrupt to trigger
	if(MEASUREMENT_getFlag()) {
		// Increase current measurement number
		MEASUREMENT_incNo();
		// Measure ECG if enabled
		if(MEASUREMENT_getType() & 0x01) {
			// TODO: Create Ecg file
			MEASUREMENT_getECG();
		}
		// Measure PPG if enabled
		if(MEASUREMENT_getType() & 0x02) {
			MEASUREMENT_getPPG();
		}
		// Reschedule next measurement time
		MEASUREMENT_reschedule();
		// Disable flag & allow data transmission
		MEASUREMENT_setFlag(0);
		MEASUREMENT_setBusy(0);
	}
}

void CONTROL_ppgDataHandler(uint32_t* red, uint32_t* ir) {
	// Package counter, counts how many data pairs were delivered
	uint8_t static cnt = 0;
	// Data holder
	uint32_t static red_stash[4];
	uint32_t static ir_stash[4];
	uint32_t static encrypted_data_red[4];
	uint32_t static encrypted_data_ir[4];
	uint8_t static file_path[30];
	// Load data to stash
	red_stash[cnt] = *red;
	ir_stash[cnt] = *ir;
	// Increase counter
	cnt+= 1;
	// Check if stashes are full
	if (cnt == 4) {
		// Encrypt red diode data
		AES_encryptPpgData(encrypted_data_red, red_stash);
		sprintf(file_path,"ppg_red/%x_%d.txt ", MEASUREMENT_getId(), MEASUREMENT_getNo());
		// Open proper file and move ptr to end
		SD_openFile((uint8_t*) file_path);
		SD_movePtrToEnd();
		// Save encrypted data
		SD_savePpgEncrypted(encrypted_data_red);
		// Close file
		SD_closeFile();
		// Encrypt ir diode data
		AES_encryptPpgData(encrypted_data_ir, ir_stash);
		sprintf(file_path,"ppg_ir/%x_%d.txt ", MEASUREMENT_getId(), MEASUREMENT_getNo());
		// Open proper files
		SD_openFile((uint8_t*) file_path);
		SD_movePtrToEnd();
		// Save encrypted data
		SD_savePpgEncrypted(encrypted_data_ir);
		// Close file
		SD_closeFile();
		// Note: Here we can also send encrypted_data to cloud right away
		// Reset counter
		cnt = 0;
	}
}



