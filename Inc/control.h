/*
 * control.h
 *
 *  Created on: Mar 26, 2018
 *      Author: Kajetan Spionek
 */

#ifndef CONTROL_H_
#define CONTROL_H_

#include "stm32l1xx_hal.h"
#include "max30102.h"
#include "sd.h"
#include "measurement.h"
#include "device.h"
#include "aes.h"
#include "esp.h"

extern UART_HandleTypeDef huart1;

void CONTROL_initHandler(void);
void CONTROL_idleHandler(void);
void CONTROL_ppgDataHandler(uint32_t* red, uint32_t* ir);

#endif /* CONTROL_H_ */
