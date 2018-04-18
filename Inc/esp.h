/*
 * esp.h
 *
 *  Created on: Mar 26, 2018
 *      Author: Kajetan Spionek
 */

#ifndef ESP_H_
#define ESP_H_

#include "stm32l1xx_hal.h"
#include "clock.h"

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart3;


#define ESP_STARTBYTE 0xAB

/* ESP <-> STM commands */
#define ESP_CMD_ECG 			0x10
#define ESP_CMD_PPG_RED 		0x11
#define ESP_CMD_PPG_IR 			0x12


void ESP_startReceivingData(void);
void ESP_receiveHandler(uint8_t msg);







#endif /* ESP_H_ */
