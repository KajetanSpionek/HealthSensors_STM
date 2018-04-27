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

void UTIL_convertAsciiToHex(uint8_t* input, uint8_t* output) {

	for(uint8_t _i = 0; _i < 16; _i++) {

		if (input[2 * _i] > 57)
			input[2 * _i]-= 39;

		if (input[(2 * _i) + 1] > 57)
			input[(2 * _i) + 1]-= 39;

		input[2 * _i]-= 48;
		input[(2 * _i) + 1]-= 48;

		output[_i] = input[2 * _i] << 4 | input[(2 * _i) + 1];
	}
}
