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
}

void CONTROL_idleHandler(void) {

}

