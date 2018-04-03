/*
 * control.c
 *
 *  Created on: Mar 26, 2018
 *      Author: Kajetan Spionek
 */

#include "control.h"

void CONTROL_initHandler(void) {

	// Initialize PPG
	// MAX30102_init();
	// Mount SD card
	SD_mount();
	// Create directories (if do not exists)
	// for ecg data
	SD_makeDirectory((uint8_t*) "ecg");
	// for ppg data
	SD_makeDirectory((uint8_t*) "ppg");
	// Set PcbVersion
	DEVICE_setPcbVersion((float) 1.3);
	// Set software version
	DEVICE_setSoftVersion((float) 0);
	// Read device.id
	//uint8_t val = SD_openFile((uint8_t*)"settings/id.txt");
	//uint8_t data[50];
	//uint8_t size = sprintf(data, "Open: %d", val);
	//HAL_UART_Transmit_IT(&huart1, data, size);
	//HAL_Delay(5);
	// Read data
	// Translate to uint16_t
	// set DEVICE id

}

void CONTROL_idleHandler(void) {

	// Wait for alarm interrupt to trigger
	if(MEASUREMENT_getFlag()) {
		// Increase current measurement number
		MEASUREMENT_incNo();
		// Measure ECG if enabled
		if(MEASUREMENT_getType() & 0x01) MEASUREMENT_getECG();
		// Measure PPG if enabled
		if(MEASUREMENT_getType() & 0x02) MEASUREMENT_getPPG();
		// Reschedule next measurement time
		MEASUREMENT_reschedule();
		// Disable flag
		MEASUREMENT_setFlag(0);
	}
}

