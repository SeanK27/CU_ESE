/*
 * Gyro.c
 *
 *  Created on: Nov 10, 2024
 *      Author: seank
 */

#include "Gyro.h"

static GPIO_InitTypeDef GPIOFstruct;
static GPIO_InitTypeDef GPIOCstruct;
static SPI_HandleTypeDef SPI;
static HAL_StatusTypeDef HALStatus;

// MSB First Bit Structure in uint16_t
// SPI Send Structure for Gyro |(DATA)|(READ/WRITE)|(MS)|(ADDRESS)|
//                  Bit Number | 16-9 |      8     |  7 |   6-0   |

void Gyro_Init(){

	// Enable GPIOF Clock
	__HAL_RCC_GPIOF_CLK_ENABLE();

	// GPIOF Configuration
	GPIOFstruct.Pin = SPI5_SCK_PIN | SPI5_MISO_PIN | SPI5_MOSI_PIN;
	GPIOFstruct.Mode = GPIO_MODE_AF_PP;
	GPIOFstruct.Alternate = GPIO_AF5_SPI5;
	GPIOFstruct.Pull = GPIO_NOPULL;
	GPIOFstruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOF, &GPIOFstruct);

	// Enable GPIOC Clock
	__HAL_RCC_GPIOC_CLK_ENABLE();

	// GPIOC Configuration
	GPIOCstruct.Pin = NCS_MEMS_SPI_PIN;
	GPIOCstruct.Mode = GPIO_MODE_OUTPUT_OD;
	GPIOCstruct.Alternate = GPIO_AF5_SPI5;
	GPIOCstruct.Pull = GPIO_PULLUP;
	GPIOCstruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOC, &GPIOCstruct);
	Gyro_DisableSlaveComms();

	// SPI5 Configuration
	SPI.Instance = SPI5;
	SPI.Init.Mode = SPI_MODE_MASTER;
	SPI.Init.Direction = SPI_DIRECTION_2LINES;
	SPI.Init.DataSize = SPI_DATASIZE_8BIT;					// 2 x 8bit package send
	SPI.Init.CLKPolarity = SPI_POLARITY_HIGH;
	SPI.Init.CLKPhase = SPI_PHASE_2EDGE;
	SPI.Init.NSS = SPI_NSS_SOFT;
	SPI.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_64;
	SPI.Init.FirstBit = SPI_FIRSTBIT_MSB;					// MSB First bit reads from left to right
	SPI.Init.TIMode = SPI_TIMODE_DISABLE;
	SPI.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	SPI.Init.CRCPolynomial = 0;
	HAL_SPI_Init(&SPI);
}

void Gyro_GetID() {

	// Create Send Data to read the WHO_AM_I register
	uint16_t dataSend = (0 << 8) | (READ << 7) | (0 << 6) | (WHO_AM_I);		// Send |00000000|1|0|001111| to WHO_AM_I
	uint16_t dataReceive = 0;
	uint8_t parsedReceive;

	// Send data once the communication line is low
	Gyro_EnableSlaveComms();
	while (HAL_GPIO_ReadPin(GPIOC,NCS_MEMS_SPI_PIN) != GPIO_PIN_RESET);
	HALStatus = HAL_SPI_TransmitReceive(&SPI, (uint8_t*) &dataSend, (uint8_t*) &dataReceive, 2, TIMEOUT);
	Gyro_DisableSlaveComms();

	// Parse the Incoming Data by taking the second byte(data)
	parsedReceive = ((uint8_t*)&dataReceive)[1];

	// Print ID in hex format
	printf("\nDevice ID: %x \n", parsedReceive);
}

void Gyro_PowerON() {

	// Create Send Data to enable Power Down Mode (1000)
	uint16_t dataSend = (0x8 << 8) | (WRITE << 7) | (0 << 6) | (CTRL_REG1);		// Send |00001000|0|0|100000| to CTRL_REG1

	Gyro_EnableSlaveComms();
	HAL_SPI_Transmit(&SPI, (uint8_t*)&dataSend, 2, TIMEOUT);
	Gyro_DisableSlaveComms();
}

void Gyro_GetTemperature() {
	// Create Send Data to read the OUT_TEMP register
	uint16_t dataSend = (0 << 8) | (READ << 7) | (0 << 6) | (OUT_TEMP);		// Send |00000000|1|0|001111| to OUT_TEMP
	uint16_t dataReceive = 0;
	uint8_t parsedReceive;

	// Send data once the communication line is low
	Gyro_EnableSlaveComms();
	while (HAL_GPIO_ReadPin(GPIOC,NCS_MEMS_SPI_PIN) != GPIO_PIN_RESET);
	HALStatus = HAL_SPI_TransmitReceive(&SPI, (uint8_t*) &dataSend, (uint8_t*) &dataReceive, 2, TIMEOUT);
	Gyro_DisableSlaveComms();

	// Parse the Incoming Data by taking the second byte(data)
	parsedReceive = ((uint8_t*)&dataReceive)[1];

	// Print ID in hex format
	printf("Temperature: %d \n", parsedReceive);

}

void Gyro_Config() {

	// Create Send Data to put module in normal mode
	uint16_t dataSend = (0x8 << 8) | (WRITE << 7) | (0 << 6) | (CTRL_REG1);		// Send |00001000|0|0|100000| to CTRL_REG1

	Gyro_EnableSlaveComms();
	HAL_SPI_Transmit(&SPI, (uint8_t*) &dataSend, 2, TIMEOUT);
	Gyro_DisableSlaveComms();


	// Create Send Data to reboot memory content
	dataSend = (0x80 << 8) | (WRITE << 7) | (0 << 6) | (CTRL_REG5);				// Send |10000000|0|0|100100| to CTRL_REG5

	Gyro_EnableSlaveComms();
	HAL_SPI_Transmit(&SPI, (uint8_t*) &dataSend, 2, TIMEOUT);
	Gyro_DisableSlaveComms();

}

void Gyro_ReadConfig() {
	// Create Send Data to read the CTRL_REG1 register
	uint16_t dataSend = (0) | (READ << 7) | (0 << 6) | (CTRL_REG1);		// Send |00000000|1|0|100000| to CTRL_REG1
	uint16_t dataReceive = 0;
	uint8_t parsedReceive;

	// Send data once the communication line is low
	Gyro_EnableSlaveComms();
	while (HAL_GPIO_ReadPin(GPIOC,NCS_MEMS_SPI_PIN) != GPIO_PIN_RESET);
	HALStatus = HAL_SPI_TransmitReceive(&SPI, (uint8_t*) &dataSend, (uint8_t*) &dataReceive, 2, TIMEOUT);
	Gyro_DisableSlaveComms();

	// Parse the Incoming Data by taking the second byte(data)
	parsedReceive = ((uint8_t*)&dataReceive)[1];

	// Print ID in hex format
	printf("CTRL_REG1: %x \n", parsedReceive);


	// Create Send Data to read the CTRL_REG5 register
	dataSend = (0) | (READ << 7) | (0 << 6) | (CTRL_REG5);		// Send |00000000|1|0|100100| to CTRL_REG5
	dataReceive = 0;

	// Send data once the communication line is low
	Gyro_EnableSlaveComms();
	while (HAL_GPIO_ReadPin(GPIOC,NCS_MEMS_SPI_PIN) != GPIO_PIN_RESET);
	HALStatus = HAL_SPI_TransmitReceive(&SPI, (uint8_t*) &dataSend, (uint8_t*) &dataReceive, 2, TIMEOUT);
	Gyro_DisableSlaveComms();

	// Parse the Incoming Data by taking the second byte(data)
	parsedReceive = ((uint8_t*)&dataReceive)[1];

	// Print ID in hex format
	printf("CTRL_REG5: %x \n", parsedReceive);
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
