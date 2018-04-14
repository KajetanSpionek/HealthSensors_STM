/*
 * measurement.h
 *
 *  Created on: Mar 26, 2018
 *      Author: Kajetan Spionek
 */

#ifndef MEASUREMENT_H_
#define MEASUREMENT_H_

#include "stm32l1xx_hal.h"
#include "sd.h"
#include "clock.h"
#include "max30102.h"
#include "control.h"

extern UART_HandleTypeDef huart1;

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
	uint8_t freq; 				/* Frequency of measurements in minutes - 10,30,60 */
	uint8_t duration; 			/* Duration of measurement in seconds */
	uint8_t length; 			/* Length of measurements in hours */
	uint8_t start_time[3];   	/* Time of first measurement (H/M/S) */
	uint8_t amount;  			/* Number of left measurements in this session */
	uint8_t next_time[3];		/* Time of next measurement (H/M/S) */
	uint8_t flag;				/* Interrupt measurement flag */
	uint8_t no;					/* No. of current/last measurement */
	uint8_t finished;			/* Positive if measurement session completed */
	uint16_t id;				/* Measurement ID - unique session identifier */

} MeasurementStruct;

MeasurementStruct MeasurementInfo;

/**
   * @brief Measurements session initialization
   * @param id:
   * @param mode:
   * @param type:
   * @param freq:
   * @param duration:
   * @param length:
   * @param start_time:
   * @retval status: 	0 - Measurements session started correctly
   * 					1 - Session already in progress
   * 					2 - SDCard is not inserted
   * 					3 - SDCard not mounted
*/
uint8_t MEASUREMENT_setMeasurement(uint16_t id, uint8_t mode, uint8_t type, uint8_t freq, uint8_t duration,
									uint8_t length, uint8_t* start_time);

/* Setters and getters */
void MEASUREMENT_setFlag(uint8_t value);
uint8_t MEASUREMENT_getFlag(void);
uint8_t MEASUREMENT_getNo(void);
void MEASUREMENT_incNo(void);
uint8_t MEASUREMENT_getIsActive(void);
uint8_t MEASUREMENT_getType(void);
uint8_t MEASUREMENT_getAmount(void);
uint8_t MEASUREMENT_getFreq(void);
uint16_t MEASUREMENT_getId(void);
uint8_t MEASUREMENT_getDuration(void);

/* Measurement functions */
uint8_t MEASUREMENT_getPPG(void);
uint8_t MEASUREMENT_getECG(void);

/* Other functions */
void MEASUREMENT_reschedule(void);


#endif /* MEASUREMENT_H_ */
