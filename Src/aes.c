/*
 * aes.c
 *
 *  Created on: Apr 11, 2018
 *      Author: Kajetan Spionek
 */

#include "aes.h"

void AES_encryptPpgData(uint32_t* data_out, uint32_t* ppg) {

	HAL_CRYP_AESECB_Encrypt(&hcryp, ppg, 16, data_out, 10);
}


