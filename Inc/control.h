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

void CONTROL_initHandler(void);
void CONTROL_idleHandler(void);



#endif /* CONTROL_H_ */
