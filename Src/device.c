/*
 * device.c
 *
 *  Created on: Mar 19, 2018
 *      Author: Kajetan Spionek
 */

#include "device.h"

/* Getters */

float DEVICE_getSoftVersion(void){

	return DeviceInfo.soft_version;
}

float DEVICE_getPcbVarsion(void) {

	return DeviceInfo.pcb_version;
}

uint16_t DEVICE_getId(void) {

	return DeviceInfo.id;
}

uint8_t DEVICE_getWifiConnected(void) {

	return DeviceInfo.wifi_connected;
}

uint8_t DEVICE_getCloudInitialized(void) {

	return DeviceInfo.cloud_initialized;
}

/* Setters */

void DEVICE_setSoftVersion(float version) {

	DeviceInfo.soft_version = version;
}

void DEVICE_setPcbVersion(float version) {

	DeviceInfo.pcb_version = version;
}

void DEVICE_setId(uint16_t id) {

	DeviceInfo.id = id;
}

void DEVICE_setWifiConnected(uint8_t wifi) {

	DeviceInfo.wifi_connected = wifi;
}

void DEVICE_setCloudInitialized(uint8_t cloud) {

	DeviceInfo.cloud_initialized = cloud;
}














