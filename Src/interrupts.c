/*
 * interrupts.c
 *
 *  Created on: Mar 21, 2018
 *      Author: Kajetan Spionek
 */

#include "interrupts.h"

/* GPIO interrupts */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {

	/* SD Card input interrupt */
	if(GPIO_Pin == GPIO_PIN_13) {

		SD_changedSocket_IT();
	}
}

/* Alarm interrupts */
void HAL_RTC_AlarmAEventCallback(RTC_HandleTypeDef *hrtc) {

	HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_4);
}



