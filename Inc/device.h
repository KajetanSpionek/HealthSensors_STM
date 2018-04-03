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

	float soft_version;
	float pcb_version;
	uint16_t id;

} DeviceStruct;

DeviceStruct DeviceInfo;

/* Getters */
float DEVICE_getSoftVersion(void);
float DEVICE_getPcbVarsion(void);
uint16_t DEVICE_getId(void);

/* Setters */
void DEVICE_setSoftVersion(float version);
void DEVICE_setPcbVersion(float version);
void DEVICE_setId(uint16_t id);

#endif /* DEVICE_H_ */
