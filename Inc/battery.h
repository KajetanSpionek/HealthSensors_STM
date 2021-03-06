/*
 * battery.h
 *
 *  Created on: Mar 19, 2018
 *      Author: Kajetan Spionek
 */

#ifndef BATTERY_H_
#define BATTERY_H_

#include "stm32l1xx_hal.h"

extern ADC_HandleTypeDef hadc;

typedef struct {

	uint16_t value; 			// Battery level in miliVolts
	uint8_t level;				// Battery level percentage
	uint8_t is_charging; 		// Positive if battery is charging

} BatteryStruct;

BatteryStruct BatteryInfo;

uint8_t BATTERY_isCharging(void);
void BATTERY_updateBatteryInfo(void);
uint16_t BATTERY_convertToMiliVolts(uint16_t adc);
uint8_t BATTERY_convertToPercentage(uint16_t voltage);

uint16_t BATTERY_getValue(void);
uint8_t BATTERY_getIsCharging(void);
uint8_t BATTERY_getLevel(void);


#endif /* BATTERY_H_ */
