#include "battery.h"

uint8_t BATTERY_isConnected(void) {

	return BatteryInfo.connection;
}

void BATTERY_updateBatteryInfo(void) {

	// Check if battery is connected
	uint8_t _isConnected = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0);
	// Update BatteryInfo
	BatteryInfo.connection = _isConnected;

	if (_isConnected) {
		// Check battery level
		HAL_ADC_Start(&hadc);
		if (HAL_ADC_PollForConversion(&hadc, 10) == HAL_OK) {
			// Pull date from and, convert do milivolts and update BatteryInfo
			BatteryInfo.value = BATTERY_convertToMiliVolts(HAL_ADC_GetValue(&hadc));
			// Convert do percentage and update BatteryInfo
			BatteryInfo.level = BATTERY_convertToPercentage(BatteryInfo.value);
		}
		// Conversions and updating BatteryInfo
	}
}

uint16_t BATTERY_convertToMiliVolts(uint16_t adc) {

	return ((adc * 3300) / 4095);
}


uint8_t BATTERY_convertToPercentage(uint16_t voltage) {

	return ((voltage - 3400) / 6);
}
