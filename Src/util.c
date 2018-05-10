/*
 * util.c
 *
 *  Created on: Mar 19, 2018
 *      Author: Kajetan Spionek
 */

#include "util.h"

/* Modes:
 * 0 - default, blocking shutdown - happens immediately
 * 1 - after short delay - in non blocking behaviour
 * Time:
 * Value in ms, only available when (mode == 1)
 */
void UTIL_powerShutdown(uint8_t mode, uint8_t time) {

	switch(mode) {
		case 0:
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_SET);
			break;
		case 1:
			// TODO:
			break;
		default:
			break;
	}
}

void UTIL_convertAsciiToHexStream(uint8_t* input, uint8_t* output, uint8_t bytes) {
// TODO: Add conversion if abcdef are capital!


		for(uint8_t _i = 0; _i < bytes; _i++) {
			if (input[2 * _i] > 57)
				input[2 * _i]-= 39;

			if (input[(2 * _i) + 1] > 57)
				input[(2 * _i) + 1]-= 39;

			input[2 * _i]-= 48;
			input[(2 * _i) + 1]-= 48;

			output[_i] = input[2 * _i] << 4 | input[(2 * _i) + 1];
		}
}

void UTIL_convertAsciiToDec(uint8_t* input, uint8_t* output) {
	if (input[0] > 57)
		input[0]-= 39;
	if (input[1] > 57)
		input[1]-= 39;

	input[0]-= 48;
	input[1]-= 48;
	*output = input[0] * 10 + input[1];
}

void UTIL_convertAsciiToHexDouble(uint8_t* input, uint8_t* output) {
// TODO: Add conversion if abcdef are capital!

	if (input[0] > 57)
		input[0]-= 39;

	if (input[1] > 57)
		input[1]-= 39;

	input[0]-= 48;
	input[1]-= 48;

	*output = input[0] << 4 | input[1];
}

void UTIL_convertAsciiToHexSingle(uint8_t* input, uint8_t* output) {
// TODO: Add conversion if abcdef are capital!

	if (*input > 57)
		*input-= 39;
	*input-= 48;
	*output = *input;
}

void UTIL_printMeasurementStats(void) {

	uint8_t data[50];
	uint8_t size;

	size = sprintf(data, "is_active: %d\n", MEASUREMENT_getIsActive());
		HAL_UART_Transmit_IT(&huart1, data, size);
		HAL_Delay(100);

	size = sprintf(data, "mode: %d\n", MEASUREMENT_getMode());
		HAL_UART_Transmit_IT(&huart1, data, size);
		HAL_Delay(100);

	size = sprintf(data, "type: %d\n", MEASUREMENT_getType());
		HAL_UART_Transmit_IT(&huart1, data, size);
		HAL_Delay(100);

	size = sprintf(data, "freq: %d\n", MEASUREMENT_getFreq());
		HAL_UART_Transmit_IT(&huart1, data, size);
		HAL_Delay(100);

	size = sprintf(data, "duration: %d\n", MEASUREMENT_getDuration());
		HAL_UART_Transmit_IT(&huart1, data, size);
		HAL_Delay(100);

	size = sprintf(data, "length: %d\n", MEASUREMENT_getLength());
		HAL_UART_Transmit_IT(&huart1, data, size);
		HAL_Delay(100);

	size = sprintf(data, "amount: %d\n", MEASUREMENT_getAmount());
		HAL_UART_Transmit_IT(&huart1, data, size);
		HAL_Delay(100);

	size = sprintf(data, "No: %d\n", MEASUREMENT_getNo());
		HAL_UART_Transmit_IT(&huart1, data, size);
		HAL_Delay(100);

	size = sprintf(data, "blocked: %d\n", MEASUREMENT_getBlocked());
		HAL_UART_Transmit_IT(&huart1, data, size);
		HAL_Delay(100);

	size = sprintf(data, "length: %lx\n", MEASUREMENT_getId());
		HAL_UART_Transmit_IT(&huart1, data, size);
		HAL_Delay(100);

	size = sprintf(data, "length: %d\n", MEASUREMENT_getBusy());
		HAL_UART_Transmit_IT(&huart1, data, size);
		HAL_Delay(100);


}








