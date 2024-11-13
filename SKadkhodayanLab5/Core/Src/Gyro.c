/*
 * Gyro.c
 *
 *  Created on: Nov 10, 2024
 *      Author: seank
 */

#include "Gyro.h"

static GPIO_InitTypeDef gyro;
static GPIO_InitTypeDef GPIOFstruct;
static GPIO_InitTypeDef GPIOCstruct;
static SPI_HandleTypeDef SPI;
static HAL_StatusTypeDef HALStatus;

// SPI Send Structure for Gyro |(DATA)|(ADDRESS)|(MS)|(READ/WRITE)|
//                  Bit Number | 15-8 |   7-2   |  1 |     0      |

void Gyro_Init(){
	// Enable the SPI5 peripheral
	__HAL_RCC_SPI5_CLK_ENABLE();

	// Enable the GPIOF peripheral
	__HAL_RCC_GPIOF_CLK_ENABLE();

	// Enable the GPIOC peripheral
	__HAL_RCC_GPIOC_CLK_ENABLE();

	// Set up the GPIO for SPI5
	GPIOFstruct.Pin = SPI5_SCK_PIN | SPI5_MISO_PIN | SPI5_MOSI_PIN;
	GPIOFstruct.Mode = GPIO_MODE_AF_PP;
	GPIOFstruct.Pull = GPIO_NOPULL;
	GPIOFstruct.Speed = GPIO_SPEED_FREQ_LOW;
	GPIOFstruct.Alternate = GPIO_AF5_SPI5;
	HAL_GPIO_Init(GPIOF, &GPIOFstruct);

	// Set up the GPIO for NCS_MEMS_SPI_PIN
	GPIOCstruct.Pin = NCS_MEMS_SPI_PIN;
	GPIOCstruct.Mode = GPIO_MODE_OUTPUT_OD;
	GPIOCstruct.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIOCstruct.Alternate = GPIO_AF5_SPI5;
	HAL_GPIO_Init(GPIOC, &GPIOCstruct);

	// Set up the SPI for Gyro
	SPI.Instance = SPI5;
	SPI.Init.Mode = SPI_MODE_MASTER;
	SPI.Init.Direction = SPI_DIRECTION_2LINES;
	SPI.Init.DataSize = SPI_DATASIZE_8BIT;
	SPI.Init.CLKPolarity = SPI_POLARITY_HIGH;
	SPI.Init.CLKPhase = SPI_PHASE_2EDGE;
	SPI.Init.NSS = SPI_NSS_SOFT;
	SPI.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_64;
	SPI.Init.FirstBit = SPI_FIRSTBIT_LSB;
	SPI.Init.TIMode = SPI_TIMODE_DISABLE;
	SPI.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	SPI.Init.CRCPolynomial = 0;
	HAL_SPI_Init(&SPI);
}

void Gyro_GetID() {
	uint16_t targetRegister = WHO_AM_I;
	uint16_t dataSend = (READ) | (0 << 1) | (targetRegister << 2) | (0);		// Send |00000000|001111|0|1| to WHO_AM_I
	uint8_t dataReceive = 0;

	Gyro_EnableSlaveComms();
	HALStatus = HAL_SPI_TransmitReceive(&SPI, (uint8_t*) &dataSend, &dataReceive, 2, TIMEOUT);
	Gyro_DisableSlaveComms();

	printf("WHO_AM_I: %x\n", dataReceive);
}

void Gyro_PowerON() {
	uint16_t targetRegister = CTRL_REG1;
	uint16_t dataSend = (WRITE) | (0 << 1) | (targetRegister << 2) | (0x0F << 8);		// Send |00001111|001000|0|0| to CTRL_REG1

	Gyro_EnableSlaveComms();
	HALStatus = HAL_SPI_Transmit(&SPI, (uint8_t*) &dataSend, 2, TIMEOUT);
	Gyro_DisableSlaveComms();
}

void Gyro_GetTemperature() {
	uint16_t targetRegister = OUT_TEMP;
	uint16_t dataSend = (READ) | (0 << 1) | (targetRegister << 2) | (0);		// Send |00000000|100110|0|1| to CTRL_REG1
	uint8_t dataReceive;

	Gyro_EnableSlaveComms();
	HALStatus = HAL_SPI_TransmitReceive(&SPI, (uint8_t*) &dataSend, &dataReceive, 2, TIMEOUT);
	Gyro_DisableSlaveComms();

	printf("CTRL_REG1: %d\n", dataReceive);

}

void Gyro_Config() {

	// Set up the SPI for 100Hz, 25 Cutoff, Normal Mode, All axis enabled
	uint16_t targetRegister = CTRL_REG1;
	uint16_t dataSend = (WRITE) | (0 << 1) | (targetRegister << 2) | (0x2F << 8);		// Send |00101111|100000|0|0| to CTRL_REG1

	Gyro_EnableSlaveComms();
	HALStatus = HAL_SPI_Transmit(&SPI, (uint8_t*) &dataSend, 2, TIMEOUT);
	Gyro_DisableSlaveComms();

	// Set up the SPI for REBOOT enabled, FIFO disabled, High Pass Filter enabled
	targetRegister = CTRL_REG5;
	dataSend = (WRITE) | (0 << 1) | (targetRegister << 2) | (0x80 << 8);		// Send |1000 0000|100100|0|0| to CTRL_REG5
	Gyro_EnableSlaveComms();
	HALStatus = HAL_SPI_Transmit(&SPI, (uint8_t*) &dataSend, 2, TIMEOUT);
	Gyro_DisableSlaveComms();
}

void Gyro_ReadConfig() {
	uint16_t targetRegister = CTRL_REG1;
	uint16_t dataSend = (READ) | (0 << 1) | (targetRegister << 2) | (0);		// Send |00000000|100000|0|1| to CTRL_REG1
	uint16_t dataReceive;

	Gyro_EnableSlaveComms();
	HALStatus = HAL_SPI_TransmitReceive(&SPI, (uint8_t*) &dataSend, (uint8_t*) &dataReceive, 2, TIMEOUT);
	Gyro_DisableSlaveComms();

	printf("CTRL_REG1: %x\n", dataReceive);

	targetRegister = CTRL_REG5;
	dataSend = (READ) | (0 << 1) | (targetRegister << 2) | (0);		// Send |00000000|100001|0|1| to CTRL_REG5

	Gyro_EnableSlaveComms();
	HALStatus = HAL_SPI_TransmitReceive(&SPI, (uint8_t*) &dataSend, (uint8_t*) &dataReceive, 2, TIMEOUT);
	Gyro_DisableSlaveComms();

	printf("CTRL_REG5: %x\n", dataReceive);
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
