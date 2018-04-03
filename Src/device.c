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

uint16_t DEVICE_getId(void) {

	return DeviceInfo.id;
}

void DEVICE_setSoftVersion(float version) {

	DeviceInfo.soft_version = version;
}

void DEVICE_setPcbVersion(float version) {

	DeviceInfo.pcb_version = version;
}

void DEVICE_setId(uint16_t id) {

	DeviceInfo.id = id;
}
