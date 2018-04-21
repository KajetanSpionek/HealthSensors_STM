/*
 * device.h
 *
 *  Created on: Mar 19, 2018
 *      Author: Kajetan Spionek
 */

#ifndef DEVICE_H_
#define DEVICE_H_

#include "stm32l1xx_hal.h"

typedef struct {

	/* General settings */
	float soft_version;
	float pcb_version;
	uint16_t id;

	/* Esp & cloud settings */

	uint8_t wifi_connected;
	uint8_t cloud_initialized;

} DeviceStruct;

DeviceStruct DeviceInfo;

/* Getters */
float DEVICE_getSoftVersion(void);
float DEVICE_getPcbVarsion(void);
uint16_t DEVICE_getId(void);
uint8_t DEVICE_getWifiConnected(void);
uint8_t DEVICE_getCloudInitialized(void);

/* Setters */
void DEVICE_setSoftVersion(float version);
void DEVICE_setPcbVersion(float version);
void DEVICE_setId(uint16_t id);
void DEVICE_setWifiConnected(uint8_t wifi);
void DEVICE_setCloudInitialized(uint8_t cloud);

#endif /* DEVICE_H_ */











