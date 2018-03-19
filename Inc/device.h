/*
 * device.h
 *
 *  Created on: Mar 19, 2018
 *      Author: Kajetan Spionek
 */

#ifndef DEVICE_H_
#define DEVICE_H_

typedef struct {

	float soft_version;
	float pcb_version;

} DeviceStruct;

DeviceStruct DeviceInfo;

float DEVICE_getSoftVersion(void);
float DEVICE_getPcbVarsion(void);

#endif /* DEVICE_H_ */
