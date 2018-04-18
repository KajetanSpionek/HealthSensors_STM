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
	uint8_t static time_cnt = 0;
	uint8_t static timer[3];
	uint8_t static data[50];
	uint8_t static size;

	switch(rec) {
	case 0: if (msg == 0x7E) rec = 1; break;
	case 1: if (msg == 0xAB) rec = 2; break;
	case 2:
			timer[time_cnt] = msg;
			time_cnt+=1;
			if(time_cnt == 3) {
				time_cnt = 0;
				rec = 0;
				CLOCK_setTime(timer);
			}
			break;
	default: break;
	}

}
