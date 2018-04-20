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

enum EspStates {
	esp_idle = 0,
	esp_route,
	esp_set_time,
	esp_set_date,
	esp_ping
};

#define ESP_STARTBYTE 0x7E

/* Commands sent to ESP */
#define ESP_CMD_ECG 			0x40
#define ESP_CMD_PPG_RED 		0x41
#define ESP_CMD_PPG_IR 			0x42

/* Comands incoming from ESP */
#define ESP_SET_CLOCK			0xA1
#define ESP_SET_DATE			0xA2
#define ESP_PING				0xA4


void ESP_startReceivingData(void);
void ESP_receiveHandler(uint8_t msg);







#endif /* ESP_H_ */
