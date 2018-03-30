/*
 * measurement.c
 *
 *  Created on: Mar 26, 2018
 *      Author: Kajetan Spionek
 */

#include "measurement.h"

uint8_t MEASUREMENT_setMeasurement(uint8_t mode, uint8_t type, uint8_t freq, uint8_t duration,
									uint8_t length, uint8_t* start_time) {

	// Check if measurement session in progress
	if (MeasurementInfo.is_active == 1) return 1;

	// Check if SDCard is inserted
	if (SD_getIsinserted() == 1) return 2;

	// Check if SDCard is mounted
	if (SD_getStatus() == 0) return 3;

	// Set basic measurement parameters
	MeasurementInfo.mode = mode;
	MeasurementInfo.type = type;
	MeasurementInfo.freq = freq;
	MeasurementInfo.duration = duration;
	MeasurementInfo.length = length;
	MeasurementInfo.start_time[0] = start_time[0];
	MeasurementInfo.start_time[1] = start_time[1];
	MeasurementInfo.start_time[2] = start_time[2];

	// Calculate left_measurements
	MeasurementInfo.left_measurements = length * 60 / freq;

	// Set next measurement to starting time
	MeasurementInfo.next_time[0] = start_time[0];
	MeasurementInfo.next_time[1] = start_time[1];
	MeasurementInfo.next_time[2] = start_time[2];

	// Set Alarm


	// Set is_active flag
	MeasurementInfo.is_active = 1;
	return 0;
}
