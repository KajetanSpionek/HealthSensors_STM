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

	uint8_t static rec = 0;
	uint8_t static in_case_cnt = 0;
	uint8_t static box[3];

	switch(rec) {
	case 0: // Search for starting byte (0x7E)
			if (msg == ESP_STARTBYTE) rec = 1; break;
	case 1: // Decide type of msg
			if (msg == ESP_SET_CLOCK) rec = 2;
			if (msg == ESP_SET_DATE) rec = 3;
			break;
	case 2: // Set time
			box[in_case_cnt] = msg;
			in_case_cnt+= 1;
			if(in_case_cnt == 3) {
				in_case_cnt = 0;
				rec = 0;
				CLOCK_setTime(box);
			}
			break;
	case 3: // Set date
			box[in_case_cnt] = msg;
			in_case_cnt+= 1;
			if(in_case_cnt == 4) {
				in_case_cnt = 0;
				box[1]+= 1;
				box[2]-= 100;
				rec = 0;
				CLOCK_setDate(box);
			}
			break;
	default: break;

	}

}
