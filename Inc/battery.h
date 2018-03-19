/*
 * battery.h
 *
 *  Created on: Mar 19, 2018
 *      Author: Kajetan
 */

#ifndef BATTERY_H_
#define BATTERY_H_

#include "stm32l1xx_hal.h"

extern ADC_HandleTypeDef hadc;

typedef struct {

	uint16_t value; 			// Battery level in miliVolts
	uint8_t level;				// Battery level percentage
	uint8_t connection; 		// Positive if battery is connected

} BatteryStruct;

BatteryStruct BatteryInfo;

uint8_t BATTERY_isConnected(void);
void BATTERY_updateBatteryInfo(void);
uint16_t BATTERY_convertToMiliVolts(uint16_t);
uint8_t BATTERY_convertToPercentage(uint16_t);


#endif /* BATTERY_H_ */
