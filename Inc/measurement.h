/*
 * measurement.h
 *
 *  Created on: Mar 26, 2018
 *      Author: Kajetan Spionek
 */

#ifndef MEASUREMENT_H_
#define MEASUREMENT_H_

#include "stm32l1xx_hal.h"

typedef struct {

	uint8_t is_active; 			/* If device is in measurement mode
	 	 	 	 	 	 	 	 1 - Measurement mode
	 	 	 	 	 	 	 	 0 - Idle */
	uint8_t mode;				/* Device mode:
							 	 0 - Passive (wifi connection not required)
							 	 1 - Active (wifi connection required)
							 	 2 - Single sweep */
	uint8_t type;				/* Measurement type:
							 	 1 - ECG
							 	 2 - PPG
							 	 3 - Both */
	uint8_t freq; 				/* Frequency of measurements in minutes */
	uint8_t duration; 			/* Duration of measurement in seconds */
	uint8_t length; 			/* Length of measurements in hours */
	uint8_t start_time[3];   	/* Time of first measurement (H/M/S) */
	uint8_t left_measurements;  /* Number of left measurements in this session */
	uint8_t next_time[3];		/* Time of next measurement (H/M/S) */

} MeasurementStruct;

MeasurementStruct MeasurementInfo;

/**
   * @brief Measurements session initialization
   * @param mode:
   * @param type:
   * @param freq:
   * @param duration:
   * @param length:
   * @param start_time:
   * @retval status: 	0 - Measurements session started correctly
   * 					1 - Session already in progress
*/
uint8_t MEASUREMENT_setMeasurement(uint8_t mode, uint8_t type, uint8_t freq, uint8_t duration,
									uint8_t length, uint8_t* start_time);


#endif /* MEASUREMENT_H_ */
