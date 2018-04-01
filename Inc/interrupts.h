/*
 * interrupts.h
 *
 *  Created on: Mar 21, 2018
 *      Author: Kajetan Spionek
 */

#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_

#include "stm32l1xx_hal.h"

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
void HAL_RTC_AlarmAEventCallback(RTC_HandleTypeDef *hrtc);


#endif /* INTERRUPTS_H_ */
