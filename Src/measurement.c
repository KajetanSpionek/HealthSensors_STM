/*
 * measurement.c
 *
 *  Created on: Mar 26, 2018
 *      Author: Kajetan Spionek
 */

#include "measurement.h"

uint8_t MEASUREMENT_setMeasurement(uint16_t id, uint8_t mode, uint8_t type, uint8_t freq, uint8_t duration,
									uint8_t length, uint8_t* start_time) {

	// Check if measurement session in progress
	if (MeasurementInfo.is_active == 1) return 1;

	// Check if device is blocked (recently finished measurements and data not transfered)
	if (MeasurementInfo.blocked == 1) return 4;

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
	MeasurementInfo.id = id;
	MeasurementInfo.busy = 0;

	// Calculate total measurements
	MeasurementInfo.amount = length * 60 / freq;

	// Set next measurement to starting time
	MeasurementInfo.next_time[0] = start_time[0];
	MeasurementInfo.next_time[1] = start_time[1];
	MeasurementInfo.next_time[2] = start_time[2];

	// Set Alarm
	CLOCK_setAlarm(start_time);

	// Set esp transmission flags
	ESP_setReadPtr(0);
	ESP_setCurrentFileId(1);
	if (type == 0)
		ESP_setCurrentFileType(0);
	else
		ESP_setCurrentFileType(1);
	// Set is_active and flag
	MeasurementInfo.flag = 0;
	MeasurementInfo.is_active = 1;
	return 0;
}

void MEASUREMENT_setFlag(uint8_t value) {

	MeasurementInfo.flag = value;
}

void MEASUREMENT_setBusy(uint8_t busy) {

	MeasurementInfo.busy = busy;
}

void MEASUREMENT_setBlocked(uint8_t fin) {

	MeasurementInfo.blocked = fin;
}

void MEASUREMENT_setIsActive(uint8_t active) {

	MeasurementInfo.is_active = active;
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

uint16_t MEASUREMENT_getId(void) {

	return MeasurementInfo.id;
}

uint8_t MEASUREMENT_getDuration(void) {

	return MeasurementInfo.duration;
}

uint8_t MEASUREMENT_getBusy(void) {
	return MeasurementInfo.busy;
}

uint8_t MEASUREMENT_getBlocked(void) {

	return MeasurementInfo.blocked;
}

uint8_t MEASUREMENT_getPPG(void) {

	// Initialize variables
	uint32_t red,ir;
	uint16_t cnt = 0;
	// Save name of file to variable
	MAX30102_init();
	// PPG loop
	while(cnt < MEASUREMENT_getDuration()*100) {
		if (MAX30102_getRegValue(MAX30102_INT_STATUS1) & 0x40) {
			MAX30102_read(&red, &ir);
			CONTROL_ppgDataHandler(&red, &ir);
			cnt+=1;
			HAL_Delay(1);
		}
	}
	return 0;
}
uint8_t MEASUREMENT_getECG(void) {

	return 0;
}

void MEASUREMENT_reschedule(void) {

	// Check measurement session should continue
	// Total amount of measurements needed - how many has been performed
	if ((MEASUREMENT_getAmount() - MEASUREMENT_getNo()) == 0) {
		MeasurementInfo.blocked = 1;
		MeasurementInfo.is_active = 0;
	}
	else {
		// Reschedule next measurement
		uint8_t time[3]; /* H/M/S */
		CLOCK_getTime(time);
		time[1]+= MEASUREMENT_getFreq();
		if (time[1] >= 60) {
			time[1]-= 60;
			time[0]+=1;
			if (time[0] >= 24) time[0]-=24;
		}
	CLOCK_setAlarm(time);
	}
}
























