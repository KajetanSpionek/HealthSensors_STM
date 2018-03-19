/*
 * battery.c
 *
 *  Created on: Mar 19, 2018
 *      Author: Kajetan Spionek
 */

#include "battery.h"

uint8_t BATTERY_isConnected(void) {

	return BatteryInfo.is_charging;
}

void BATTERY_updateBatteryInfo(void) {

	// Check if battery is connected
	uint8_t _isCharging = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0);
	// Update BatteryInfo
	BatteryInfo.is_charging = _isCharging;

	if (_isCharging) {
		// Check battery level
		HAL_ADC_Start(&hadc);
		if (HAL_ADC_PollForConversion(&hadc, 10) == HAL_OK) {
			// Pull date from adc, convert to milivolts and update BatteryInfo
			BatteryInfo.value = BATTERY_convertToMiliVolts(HAL_ADC_GetValue(&hadc));
			// Convert to percentage and update BatteryInfo
			BatteryInfo.level = BATTERY_convertToPercentage(BatteryInfo.value);
		}
	}
}

uint16_t BATTERY_convertToMiliVolts(uint16_t adc) {

	return ((adc * 3300) / 4095);
}

uint8_t BATTERY_convertToPercentage(uint16_t voltage) {

	return ((voltage - 3400) / 6);
}

uint16_t BATTERY_getValue(void){

	return BatteryInfo.value;
}

uint8_t BATTERY_getIsConnected(void) {

	return BatteryInfo.is_charging;
}

uint8_t BATTERY_getLevel(void) {

	return BatteryInfo.level;
}











