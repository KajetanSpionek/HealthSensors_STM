/*
 * util.h
 *
 *  Created on: Mar 19, 2018
 *      Author: Kajetan Spionek
 */

#ifndef UTIL_H_
#define UTIL_H_

#include "stm32l1xx_hal.h"
#include <stdio.h>
#include <stdlib.h>
#include "measurement.h"

extern UART_HandleTypeDef huart1;

void UTIL_powerShutdown(uint8_t mode, uint8_t time);
void UTIL_convertAsciiToHexStream(uint8_t* input, uint8_t* output, uint8_t bytes);
void UTIL_convertAsciiToDec(uint8_t* input, uint8_t* output);
void UTIL_convertAsciiToHexDouble(uint8_t* input, uint8_t* output);
void UTIL_convertAsciiToHexSingle(uint8_t* input, uint8_t* output);

void UTIL_printMeasurementStats(void);

#endif /* UTIL_H_ */
