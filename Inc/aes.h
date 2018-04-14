/*
 * aes.h
 *
 *  Created on: Apr 11, 2018
 *      Author: Kajetan Spionek
 */

#ifndef AES_H_
#define AES_H_

#include "stm32l1xx_hal.h"

extern CRYP_HandleTypeDef hcryp;

void AES_encryptPpgData(uint32_t* data_out, uint32_t* ppg);

#endif /* AES_H_ */
