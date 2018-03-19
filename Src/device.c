/*
 * device.c
 *
 *  Created on: Mar 19, 2018
 *      Author: Kajetan Spionek
 */

#include "device.h"

float DEVICE_getSoftVersion(void){

	return DeviceInfo.soft_version;
}

float DEVICE_getPcbVarsion(void) {

	return DeviceInfo.pcb_version;
}
