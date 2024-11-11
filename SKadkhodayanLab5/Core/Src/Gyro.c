/*
 * Gyro.c
 *
 *  Created on: Nov 10, 2024
 *      Author: seank
 */

#include "Gyro.h"

static GPIO_InitTypeDef gyro;
static SPI_HandleTypeDef SPI;
static HAL_StatusTypeDef HALStatus;

// SPI Send Structure for Gyro |(DATA)|(ADDRESS)|(MS)|(READ/WRITE)|
//                  Bit Number | 15-8 |   7-2   |  1 |     0      |


void Gyro_GetTemperature() {

}

void Gyro_Config() {

	// Set up the SPI for 100Hz, 25 Cutoff, Normal Mode, All axis enabled
	uint16_t targetRegister = CTRL_REG1;
	uint16_t dataSend = (WRITE) | (0) | (targetRegister << 2) | (0x2F << 8);		// Send |00101111|001000|0|0| to CTRL_REG1

	Gyro_EnableSlaveComms();
	HALStatus = HAL_SPI_Transmit(&SPI, &dataSend, 2, TIMEOUT);
	Gyro_DisableSlaveComms();

	// Set up the SPI for REBOOT enabled, FIFO disabled, High Pass Filter enabled
	targetRegister = CTRL_REG5;
	dataSend = (WRITE) | (0) | (targetRegister << 2) | (0x80 << 8);		// Send |1000 0000|100001|0|0| to CTRL_REG5
	Gyro_EnableSlaveComms();
	HALStatus = HAL_SPI_Transmit(&SPI, &dataSend, 2, TIMEOUT);
	Gyro_DisableSlaveComms();
}

void Gyro_ReadConfig() {
	uint16_t targetRegister = CTRL_REG1;
	uint16_t dataSend = (READ) | (0) | (targetRegister << 2) | (0);		// Send |00000000|001000|0|1| to CTRL_REG1
	uint16_t dataReceive;

	Gyro_EnableSlaveComms();
	HALStatus = HAL_SPI_TransmitReceive(&SPI, &dataSend, &dataReceive, 2, TIMEOUT);
	Gyro_DisableSlaveComms();

	// Check if the data received is correct
	if(dataReceive != 0x2F) {
		APPLICATION_ASSERT(false);
	}

	targetRegister = CTRL_REG5;
	dataSend = (READ) | (0) | (targetRegister << 2) | (0);		// Send |00000000|100001|0|1| to CTRL_REG5
}

void Gyro_CheckHALStatus() {
	if(HALStatus != HAL_OK){
		APPLICATION_ASSERT(false);
	}
}

void Gyro_EnableSlaveComms() {
	HAL_GPIO_WritePin(GPIOC, NCS_MEMS_SPI_PIN, GPIO_PIN_RESET); // Set to LOW to enable SPI mode Pin PC1
}

void Gyro_DisableSlaveComms() {
	HAL_GPIO_WritePin(GPIOC, NCS_MEMS_SPI_PIN, GPIO_PIN_SET); 	// Set to HIGH to disable SPI mode Pin PC1
}