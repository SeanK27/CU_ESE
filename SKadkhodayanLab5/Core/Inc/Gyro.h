/*
 * Gyro.h
 *
 *  Created on: Nov 10, 2024
 *      Author: seank
 */

#ifndef INC_GYRO_H_
#define INC_GYRO_H_

#include "stm32f4xx_hal.h"
#include "ErrorHandling.h"
#include <stdio.h>
#include <stdint.h>

// Macros
#define WHO_AM_I 0x0F
#define CTRL_REG1 0x20
#define CTRL_REG2 0x21
#define CTRL_REG3 0x22
#define CTRL_REG4 0x23
#define CTRL_REG5 0x24
#define REFERENCE_DATACAPTURE 0x25
#define OUT_TEMP 0x26
#define STATUS_REG 0x27
#define OUT_X_L 0x28
#define OUT_X_H 0x29
#define OUT_Y_L 0x2A
#define OUT_Y_H 0x2B
#define OUT_Z_L 0x2C
#define OUT_Z_H 0x2D
#define FIFO_CTRL_REG 0x2E
#define FIFO_SRC_REG 0x2F
#define INT1_CFG 0x30
#define INT1_SRC 0x31
#define INT1_THS_XH 0x32
#define INT1_THS_XL 0x33
#define INT1_THS_YH 0x34
#define INT1_THS_YL 0x35
#define INT1_THS_ZH 0x36
#define INT1_THS_ZL 0x37
#define INT1_DURATION 0x38

// SPI Send Structure for Gyro |(READ/WRITE)|(MS)|(ADDRESS)|(DATA)|
//                             |     0      |  1 |   2-7   | 8-15 |
#define WRITE 0
#define READ  1

#define TIMEOUT 5000

#define SPI5_SCK_PIN GPIO_PIN_7         // PF7
#define SPI5_MISO_PIN GPIO_PIN_8        // PF8
#define SPI5_MOSI_PIN GPIO_PIN_9        // PF9
#define NCS_MEMS_SPI_PIN GPIO_PIN_1     // PC1      SPIMode(0) I2CMode(1)
#define MEMS_INT2_PIN GPIO_PIN_2        // PA2
#define MEMS_INT1_PIN GPIO_PIN_1        // PA1

// Prototypes
void Gyro_Init();
void Gyro_GetID();
void Gyro_PowerON();
void Gyro_GetTemperature();
void Gyro_Config();
void Gyro_ReadConfig();
void Gyro_CheckHALStatus();
void Gyro_EnableSlaveComms();
void Gyro_DisableSlaveComms();

#endif /* INC_GYRO_H_ */
