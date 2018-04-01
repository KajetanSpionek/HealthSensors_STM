/*
 * control.c
 *
 *  Created on: Mar 26, 2018
 *      Author: Kajetan Spionek
 */

#include "control.h"

void CONTROL_initHandler(void) {

	// Initialize PPG
	//MAX30102_init();
	// Mount SD card
	SD_mount();
	// Create directories (if do not exists)
	// for ecg data
	SD_makeDirectory((uint8_t*) "ecg");
	// for ppg data
	SD_makeDirectory((uint8_t*) "ppg");
	// for settings data
	SD_makeDirectory((uint8_t*) "settings");
}

void CONTROL_idleHandler(void) {

	// Wait for alarm interrupt to trigger
	if(MEASUREMENT_getFlag()) {
		// Disable flag
		MEASUREMENT_setFlag(0);
		// Increase current measurement number
		MEASUREMENT_incNo();
		// Measure ECG if enabled
		if(MEASUREMENT_getType() & 0x01) MEASUREMENT_getECG();
		// Measure PPG if enabled
		if(MEASUREMENT_getType() & 0x02) MEASUREMENT_getPPG();
	}
}

