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
	uint8_t static box[26];
	// HAL_UART_Transmit_IT(&huart1, &msg, 1);
	// HAL_Delay(1);

	switch(rec) {
	case esp_idle: // Search for starting byte (0x7E)
			if (msg == ESP_STARTBYTE) {
				rec = esp_route;
			}
			break;
	case esp_route: // Decide type of msg
			if (msg == ESP_SET_CLOCK) rec = esp_set_time;
			else if (msg == ESP_SET_DATE) rec = esp_set_date;
			else if (msg == ESP_WIFI) rec = esp_wifi;
			else if (msg == ESP_CLOUD_RDY) rec = esp_cloud_rdy;
			else if (msg == ESP_DATA_ACK) {
				HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_4);
				ESP_setLastDataStatus(0);
				rec = esp_idle;
			}
			else if (msg == ESP_DATA_NACK) {
				ESP_setLastDataStatus(1);
				rec = esp_idle;
			}
			else if (msg == ESP_REQUEST_MEASUREMENT) rec = esp_request_measurement;
			else rec = esp_idle;
			break;
	case esp_set_time: // Set time
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
	case esp_wifi: // Ping back
			DEVICE_setWifiConnected(msg);
			rec = esp_idle;
			break;
	case esp_cloud_rdy: // Ping back
			DEVICE_setCloudInitialized(msg);
			rec = esp_idle;
			break;
	case esp_request_measurement: // Data about measurement inc
			box[in_case_cnt] = msg;
			in_case_cnt+= 1;
			if(in_case_cnt == 26) {
				in_case_cnt = 0;
				rec = esp_idle;
				uint8_t data[50];
				uint8_t size;
				HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_4);


				//size = sprintf(data, "%c%c%c%c%c%c%c%c", box[0], box[1], box[2], box[3], box[4], box[5], box[6], box[7]);
				//size = sprintf(data, "%c%c%c%c%c%c%c%c", box[8], box[9], box[10], box[11], box[12], box[13], box[14], box[15]);
				size = sprintf(data, "%c%c%c%c%c%c%c%c", box[16], box[17], box[18], box[19], box[20], box[21], box[24], box[25]);
				HAL_UART_Transmit_IT(&huart1, data, size);



			}
			break;
	default: break;

	}
}

void ESP_dataHandler(void) {

	// Data buffer
	uint8_t static buff[16];
	uint8_t static file_status = 0;
	uint8_t static data[50];
	uint8_t static size;
	uint8_t static file_path[30];
	uint8_t static failed_cnt = 0;

	// Check if measurement is active && not blocked
	if (MEASUREMENT_getIsActive() == 0 && MEASUREMENT_getBlocked() == 0) return;
	// Check if connected to wifi, cloud & not busy
	if(DEVICE_getCloudInitialized() == 0) return;
	if(DEVICE_getWifiConnected() == 0) return;
	if(MEASUREMENT_getBusy() == 1) return;
	// Check if there is data to transmit (file)
	if (MEASUREMENT_getNo() < DataInfo.current_file_id) return;
	// Check if all data was transfered
	if (DataInfo.current_file_id > MEASUREMENT_getAmount()) {
		MEASUREMENT_setBlocked(0);
		return;
	}
	// last check - works
	// Check if ESP answered to last data, and if so check status
		// ESP hasn't responded yet
	if (DataInfo.last_data_status == 2) {
		failed_cnt+= 1;
		if (failed_cnt < 10) return;
		failed_cnt = 0;
	}
		// NACK -> Do not move pointer
	else if (DataInfo.last_data_status == 1) DataInfo.read_ptr+= 0;
		// ACK -> move pointer
	else if (DataInfo.last_data_status == 0) DataInfo.read_ptr+= 1;

	// Set correct file_path
		// Check if ECG available
	if((MEASUREMENT_getType() & 0x01) && DataInfo.current_file_type == 0) {
		sprintf(file_path,"ecg/%x_%d.txt ", MEASUREMENT_getId(), DataInfo.current_file_id);

	}
		// Check if PPG_RED available
	else if((MEASUREMENT_getType() & 0x02) && DataInfo.current_file_type == 1) {
		sprintf(file_path,"ppg_red/%x_%d.txt ", MEASUREMENT_getId(), DataInfo.current_file_id);
	}
		// Check if PPG_IR available
	else if((MEASUREMENT_getType() & 0x02) && DataInfo.current_file_type == 2) {
		sprintf(file_path,"ppg_ir/%x_%d.txt ", MEASUREMENT_getId(), MEASUREMENT_getNo());
	}

	// Try to get data from steam
	file_status = SD_streamFilePpg(file_path, buff, DataInfo.read_ptr);

	if (file_status == 0) {
		// We can transfer buffer
			// Send frame
			//HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_4);
			DataInfo.last_data_status = 2;
			ESP_sendPpgFrame(buff);

		// Set waiting for confirmation from esp flag (TODO - remove setting 0)

		//DataInfo.last_data_status = 0;
	}
	else if (file_status == 1) {
		// Whole file was transfered, so we need to assign next one

		// ECG only measurement
		if(MEASUREMENT_getType() == 0x01) {
			DataInfo.read_ptr = 0;
			DataInfo.current_file_id+= 1;
			DataInfo.last_data_status = 4;
		}
		// PPG only measurement
		else if(MEASUREMENT_getType() == 0x02) {
			if (DataInfo.current_file_type == 1) {
				DataInfo.current_file_type = 2;
				DataInfo.read_ptr = 0;
				DataInfo.last_data_status = 4;
			}
			else { // DataInfo.current_file_type == 2
				DataInfo.current_file_type = 1;
				DataInfo.read_ptr = 0;
				DataInfo.current_file_id+= 1;
				DataInfo.last_data_status = 4;
			}
		}
		// Both measurements
		else if(MEASUREMENT_getType() == 0x03) {
			if (DataInfo.current_file_type == 0) {
				DataInfo.current_file_type = 1;
				DataInfo.read_ptr = 0;
				DataInfo.last_data_status = 4;
			}
			else if (DataInfo.current_file_type == 1) {
				DataInfo.current_file_type = 2;
				DataInfo.read_ptr = 0;
				DataInfo.last_data_status = 4;
			}
			else { // DataInfo.current_file_type == 2
				DataInfo.current_file_type = 0;
				DataInfo.current_file_id+= 1;
				DataInfo.read_ptr = 0;
				DataInfo.last_data_status = 4;
			}
		}
	}
}

void ESP_sendPpgFrame(uint8_t* data) {

	//if (DataInfo.last_data_status == 2) return;
	uint8_t header[7] = {0};
	header[0] = 0x7E;
	header[1] = 0x41; // + DataInfo.current_file_type;
	header[2] = 0x00; //MEASUREMENT_getId() & 0xFF;
	header[3] = 0x00; //MEASUREMENT_getId() >> 8;
	header[4] = 0x00; //DataInfo.current_file_id;
	header[5] = 0x00; //DataInfo.read_ptr & 0xFF;
	header[6] = 0x00; //DataInfo.read_ptr >> 8;
	//DataInfo.last_data_status = 2;
	HAL_UART_Transmit_IT(&huart3, header, 7);
	HAL_Delay(1);
	HAL_UART_Transmit_IT(&huart3, data, 16);

}

void ESP_setReadPtr(uint8_t ptr) {

	DataInfo.read_ptr = ptr;
}

void ESP_setCurrentFileId(uint8_t id) {

	DataInfo.current_file_id = id;
}

void ESP_setCurrentFileType(uint8_t type) {

	DataInfo.current_file_type = type;
}

void ESP_setLastDataStatus(uint8_t status) {

	DataInfo.last_data_status = status;
}















