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

	MEASUREMENT_setFlag(1);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {

	uint8_t data[20];
	uint16_t size = 0;
	size = sprintf(data, "Received: %d\n", Received);

	 HAL_UART_Transmit_IT(&huart1, data, size);
	 HAL_Delay(3);
	 HAL_UART_Receive_IT(&huart3, Received, 3);
}


