/*
 * clock.h
 *
 *  Created on: Mar 21, 2018
 *      Author: Kajetan Spionek
 */

#ifndef CLOCK_H_
#define CLOCK_H_

#include "stm32l1xx_hal.h"

extern RTC_HandleTypeDef hrtc;
RTC_TimeTypeDef current_time;
RTC_DateTypeDef current_date;

uint8_t CLOCK_getTime(uint8_t* time);
uint8_t CLOCK_getDate(uint8_t* date);
uint8_t CLOCK_updateRTC(void);


#endif /* CLOCK_H_ */
