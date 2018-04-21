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
#include "device.h"
#include "measurement.h"

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart3;

enum EspStates {
	esp_idle = 0,
	esp_route,
	esp_set_time,
	esp_set_date,
	esp_wifi,
	esp_cloud_rdy,
	esp_data_ack,
	esp_data_nack
};

typedef struct {
	// Transmission cycle: ppg_red -> ppg_ir -> ppg_ecg
	uint32_t read_ptr;
	uint8_t current_file_id;
} DataStruct;

DataStruct DataInfo;

#define ESP_STARTBYTE 0x7E

/* Commands sent to ESP */
#define ESP_CMD_ECG 			0x40
#define ESP_CMD_PPG_RED 		0x41
#define ESP_CMD_PPG_IR 			0x42
	// cmd ack/nack by STM
#define ESP_ACK					0x11
#define ESP_NACK				0x14

/* Comands incoming from ESP */
#define ESP_SET_CLOCK			0xA1			// Followed by 3 bytes of date data
#define ESP_SET_DATE			0xA2			// Followed by 3 bytes of time data
#define ESP_WIFI				0xA4			// Followed by 1 byte -> 1 or 0 (1 CONNECTED / 0 NOT CONNECTED)
#define ESP_CLOUD_RDY			0xA8			// Followed by 1 byte -> 1 or 0 (1 CONNECTED / 0 NOT CONNECTED)
	// Data ack/nack by esp/cloud
#define ESP_DATA_ACK			0xC1
#define ESP_DATA_NACK			0xC4


void ESP_startReceivingData(void);
void ESP_receiveHandler(uint8_t msg);

void ESP_dataHandler(void);







#endif /* ESP_H_ */
