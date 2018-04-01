/*
 * max30102.c
 *
 *  Created on: Mar 21, 2018
 *      Author: Kajetan Spionek
 */

#include "max30102.h"

void MAX30102_init(void) {

	// Set data ready interrupt (B6)
	MAX30102_setRegValue(MAX30102_INT_ENABLE1, 0x40); // 0100 0000
	// Clear fifo wr ptr
	MAX30102_setRegValue(MAX30102_FIFO_WR_PTR, 0x00);
	// Clear fifo rd prt
	MAX30102_setRegValue(MAX30102_FIFO_RD_PTR, 0x00);
	// Clear overflow count
	MAX30102_setRegValue(MAX30102_OVF_CNT, 0x00);
	// Set HR mode 02 // spo2
	MAX30102_setRegValue(MAX30102_MODE_CONFIG, 0x03);
	// SPO2 config - 100 SPS and ADC res 18bits
    MAX30102_setRegValue(MAX30102_SPO2_CONFIG, 0x67);
	// Diodes current
  	MAX30102_setRegValue(MAX30102_LED1_AMP , 0x4F);
  	MAX30102_setRegValue(MAX30102_LED2_AMP, 0x40);
	// No averageing
	MAX30102_setRegValue(MAX30102_FIFO_CONFIG, 0x00);
}

uint8_t MAX30102_getRegValue(uint8_t address) {

	uint8_t buf;
	HAL_I2C_Mem_Read(&hi2c1, MAX30102_ADDRESS, address, 1, &buf, 1, 100);
	return buf;
}

void MAX30102_setRegValue(uint8_t address,uint8_t value) {

	HAL_I2C_Mem_Write(&hi2c1, MAX30102_ADDRESS, address, 1, &value	, 1, 1000);
}

void MAX30102_getRegMultipleValues(uint8_t address, uint8_t* buf, uint8_t len) {

	HAL_I2C_Mem_Read(&hi2c1, MAX30102_ADDRESS, address, 1, buf, len, 100);
}

void MAX30102_read(uint32_t* red, uint32_t* ir) {
	// Buffer for IR and RED diode data
	uint8_t buf[6];
	// Read data
	MAX30102_getRegMultipleValues(MAX30102_FIFO_DATA, buf, 6);
	// Store data as 32bit variables
	*red = ((buf[0]&0x03)<<16) | buf[1]<<8 | buf[2];
	*ir = ((buf[3]&0x03)<<16) | buf[4]<<8 | buf[5];
}










