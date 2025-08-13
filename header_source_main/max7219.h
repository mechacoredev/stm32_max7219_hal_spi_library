/*
 * max7219.h
 *
 *  Created on: Aug 13, 2025
 *      Author: Enes
 */

#ifndef INC_MAX7219_H_
#define INC_MAX7219_H_

#include "stm32f4xx_hal.h"

typedef enum {
	MAX7219_OK = 0, MAX7219_SEND_DATA_FAIL,
} MAX7219_Return_Stat;

typedef enum {
	MAX7219_NOOP_ADDR = 0,
	MAX7219_DIGIT0_ADDR,
	MAX7219_DIGIT1_ADDR,
	MAX7219_DIGIT2_ADDR,
	MAX7219_DIGIT3_ADDR,
	MAX7219_DIGIT4_ADDR,
	MAX7219_DIGIT5_ADDR,
	MAX7219_DIGIT6_ADDR,
	MAX7219_DIGIT7_ADDR,
	MAX7219_DECODEMODE_ADDR,
	MAX7219_INTENSITY_ADDR,
	MAX7219_SCANLIMIT_ADDR,
	MAX7219_SHUTDOWN_ADDR,
	MAX7219_DISPLAYTEST_ADDR = 15,
} MAX7219_Reg_Addr;

typedef struct {
	uint16_t MAX7219_TimeoutForSpi;
	SPI_HandleTypeDef *MAX7219_spi_handler;
	GPIO_TypeDef *MAX7219_CS_Port;
	uint16_t MAX7219_CS_pin;
	uint8_t MAX7219_Digits[8];
	uint8_t MAX7219_DecodeMode;
	uint8_t MAX7219_Intensity;
	uint8_t MAX7219_ScanLimit;
	uint8_t MAX7219_DisplayTest;
	MAX7219_Reg_Addr MAX7219_Reg_Address;
	uint8_t MAX7219_Buffer[2];
} MAX7219_t;

MAX7219_Return_Stat MAX7219_Init(MAX7219_t *dev, SPI_HandleTypeDef *hspi, uint16_t TimeOutForSpi, GPIO_TypeDef *CS_GPIO_PORT, uint16_t CS_PIN);

MAX7219_Return_Stat MAX7219_Clear(MAX7219_t *dev);

MAX7219_Return_Stat MAX7219_DisplayMatrix(MAX7219_t *dev);

MAX7219_Return_Stat MAX7219_ShutDown(MAX7219_t *dev);

#endif /* INC_MAX7219_H_ */
