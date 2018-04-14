/*
 * interrupts.h
 *
 *  Created on: Mar 21, 2018
 *      Author: Kajetan Spionek
 */

#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_

#include "stm32l1xx_hal.h"

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart3;
extern uint8_t Received[3];

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
void HAL_RTC_AlarmAEventCallback(RTC_HandleTypeDef *hrtc);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);


#endif /* INTERRUPTS_H_ */
