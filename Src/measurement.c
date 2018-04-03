/*
 * measurement.c
 *
 *  Created on: Mar 26, 2018
 *      Author: Kajetan Spionek
 */

#include "measurement.h"

uint8_t MEASUREMENT_setMeasurement(uint32_t id, uint8_t mode, uint8_t type, uint8_t freq, uint8_t duration,
									uint8_t length, uint8_t* start_time) {

	// Check if measurement session in progress
	if (MeasurementInfo.is_active == 1) return 1;

	// Check if SDCard is inserted
	if (SD_getIsinserted() == 1) return 2;

	// Check if SDCard is mounted
	//if (SD_getStatus() == 0) return 3;

	// Set basic measurement parameters
	MeasurementInfo.mode = mode;
	MeasurementInfo.type = type;
	MeasurementInfo.freq = freq;
	MeasurementInfo.duration = duration;
	MeasurementInfo.length = length;
	MeasurementInfo.start_time[0] = start_time[0];
	MeasurementInfo.start_time[1] = start_time[1];
	MeasurementInfo.start_time[2] = start_time[2];
	MeasurementInfo.no = 0;
	MeasurementInfo.finished = 0;
	MeasurementInfo.id = id;

	// Calculate left_measurements
	MeasurementInfo.amount = length * 60 / freq;

	// Set next measurement to starting time
	MeasurementInfo.next_time[0] = start_time[0];
	MeasurementInfo.next_time[1] = start_time[1];
	MeasurementInfo.next_time[2] = start_time[2];

	// Set Alarm
	CLOCK_setAlarm(start_time);

	// Set is_active and flag
	MeasurementInfo.flag = 0;
	MeasurementInfo.is_active = 1;
	return 0;
}

void MEASUREMENT_setFlag(uint8_t value) {

	MeasurementInfo.flag = value;
}

uint8_t MEASUREMENT_getFlag(void) {

	return MeasurementInfo.flag;
}

uint8_t MEASUREMENT_getNo(void) {

	return MeasurementInfo.no;
}

void MEASUREMENT_incNo(void) {

	MeasurementInfo.no+=1;
}

uint8_t MEASUREMENT_getIsActive(void) {

	return MeasurementInfo.is_active;
}

uint8_t MEASUREMENT_getType(void) {

	return MeasurementInfo.type;
}

uint8_t MEASUREMENT_getAmount(void) {

	return MeasurementInfo.amount;
}

uint8_t MEASUREMENT_getFreq(void) {

	return MeasurementInfo.freq;
}

uint8_t MEASUREMENT_getPPG(void) {

	// Initialize variables
	uint32_t red,ir;
	uint16_t cnt = 0;
	uint16_t alternative_cnt = 0;
	// Open proper files
	SD_createFile((uint8_t*) "ppg/1.txt");
	// Save name of file to variable
	MAX30102_init();
	// PPG loop
	while(cnt < 1000) {
		if (MAX30102_getRegValue(MAX30102_INT_STATUS1) & 0x40) {
			MAX30102_read(&red, &ir);
			SD_savePPG(&red, &ir);
			cnt+=1;
			HAL_Delay(2);
		}
		else {
			alternative_cnt+=1;
		}
	}
	// Close file
	SD_closeFile();
	HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_4);
	return 0;
}
uint8_t MEASUREMENT_getECG(void) {

	return 0;
}

void MEASUREMENT_reschedule(void) {

	// Check measurement session should continue
	// Total amount of measurements needed - how many has been performed
	if ((MEASUREMENT_getAmount() - MEASUREMENT_getNo()) == 0) MeasurementInfo.finished = 1;
	else {
		// Reschedule next measurement
		uint8_t time[3]; /* H/M/S */
		CLOCK_getTime(time);
		time[2]+= MEASUREMENT_getFreq();
		if (time[2] >= 60) {
			time[2]-= 60;
			time[1]+=1;
			if (time[1] >= 24) time[1]-=24;
		}
		CLOCK_setAlarm(time);
	}
}
























