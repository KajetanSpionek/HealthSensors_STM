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

void UTIL_powerShutdown(uint8_t mode, uint8_t time);
void UTIL_convertAsciiToHex(uint8_t* input, uint8_t* output);

#endif /* UTIL_H_ */
