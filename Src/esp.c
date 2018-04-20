/*
 * esp.c
 *
 *  Created on: Mar 26, 2018
 *      Author: Kajetan Spionek
 */

#include "esp.h"

uint8_t Received;

void ESP_startReceivingData(void) {

	HAL_UART_Receive_IT(&huart3, &Received, 1);
}

void ESP_receiveHandler(uint8_t msg) {

	uint8_t static rec = esp_idle;
	uint8_t static in_case_cnt = 0;
	uint8_t static box[3];

	switch(rec) {
	case esp_idle: // Search for starting byte (0x7E)
			if (msg == ESP_STARTBYTE) rec = esp_route;
			break;
	case esp_route: // Decide type of msg
			if (msg == ESP_SET_CLOCK) rec = esp_set_time;
			else if (msg == ESP_SET_DATE) rec = esp_set_date;
			else if (msg == ESP_PING) rec = esp_ping;
			else rec = esp_idle;
			break;
	case esp_set_time: // Set time
			//HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_4);
			box[in_case_cnt] = msg;
			in_case_cnt+= 1;
			if(in_case_cnt == 3) {
				in_case_cnt = 0;
				rec = esp_idle;
				CLOCK_setTime(box);
			}
			break;
	case esp_set_date: // Set date
			box[in_case_cnt] = msg;
			in_case_cnt+= 1;
			if(in_case_cnt == 4) {
				in_case_cnt = 0;
				box[1]+= 1;
				box[2]-= 100;
				rec = esp_idle;
				CLOCK_setDate(box);
			}
			break;
	case esp_ping: // Ping back
			HAL_UART_Transmit_IT(&huart1, &msg, 1);
			rec = esp_idle;
	default: break;

	}

}
