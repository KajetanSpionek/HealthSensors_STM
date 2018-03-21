/*
 * max30102.h
 *
 *  Created on: Mar 21, 2018
 *      Author: Kajetan Spionek
 */

#ifndef MAX30102_H_
#define MAX30102_H_

#include "stm32l1xx_hal.h"

/* I2C handle */
extern I2C_HandleTypeDef hi2c1;

/* I2C address */
#define MAX30102_ADDRESS			(uint8_t)(0x57 << 1)
/* STATUS registers */
#define MAX30102_INT_STATUS1		0x00
#define MAX30102_INT_STATUS2		0x01
#define MAX30102_INT_ENABLE1		0x02
#define MAX30102_INT_ENABLE2		0x03
/* FIFO */
#define MAX30102_FIFO_WR_PTR		0x04
#define MAX30102_OVF_CNT			0x05
#define MAX30102_FIFO_RD_PTR		0x06
#define MAX30102_FIFO_DATA			0x07
/* CONFIG registers */
#define MAX30102_FIFO_CONFIG		0x08
#define MAX30102_MODE_CONFIG		0x09
#define MAX30102_SPO2_CONFIG		0x0A
#define MAX30102_LED1_AMP			0x0C
#define MAX30102_LED2_AMP			0x0D
#define MAX30102_PILOT				0x10
#define MAX30102_MLED_CTRL1			0x11
#define MAX30102_MLED_CTRL2			0x12
/* DIE TEMP registers */
#define MAX30102_TEMP_INT			0x1F
#define MAX30102_TEMP_FRAC			0x20
#define MAX30102_TEMP_EN			0x21
/* PROXIMITY register */
#define MAX30102_PROX_THRESH		0x30
/* PART ID registers */
#define MAX30102_REV_ID				0xFE
#define MAX30102_PART_ID			0xFF


void MAX30102_init(void);
uint8_t MAX30102_getRegValue(uint8_t address);
void MAX30102_setRegValue(uint8_t address,uint8_t value);
void MAX30102_getRegMultipleValues(uint8_t address, uint8_t* buf, uint8_t len);





#endif /* MAX30102_H_ */
