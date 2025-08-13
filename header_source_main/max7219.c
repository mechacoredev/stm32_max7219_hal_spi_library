/*
 * max7219.c
 *
 *  Created on: Aug 13, 2025
 *      Author: Enes
 */

#include "max7219.h"

static inline MAX7219_Return_Stat _MAX7219SendData(MAX7219_t *dev) {
	HAL_GPIO_WritePin(dev->MAX7219_CS_Port, dev->MAX7219_CS_pin,
			GPIO_PIN_RESET);
	if (HAL_SPI_Transmit(dev->MAX7219_spi_handler, dev->MAX7219_Buffer, 2,
			dev->MAX7219_TimeoutForSpi) != HAL_OK) {
		return MAX7219_SEND_DATA_FAIL;
	}
	HAL_GPIO_WritePin(dev->MAX7219_CS_Port, dev->MAX7219_CS_pin, GPIO_PIN_SET);
	return MAX7219_OK;
}

MAX7219_Return_Stat inline MAX7219_Clear(MAX7219_t *dev) {
	for (uint8_t i = 1; i < 9; i++) {
		dev->MAX7219_Buffer[0] = i;
		dev->MAX7219_Buffer[1] = 0x00;
		if (_MAX7219SendData(dev) != MAX7219_OK) {
			return MAX7219_SEND_DATA_FAIL;
		}
	}
	return MAX7219_OK;
}

MAX7219_Return_Stat MAX7219_Init(MAX7219_t *dev, SPI_HandleTypeDef *hspi, uint16_t TimeOutForSpi, GPIO_TypeDef *CS_GPIO_PORT, uint16_t CS_PIN) {
	dev->MAX7219_spi_handler = hspi;
	dev->MAX7219_TimeoutForSpi=TimeOutForSpi;
	dev->MAX7219_CS_Port=CS_GPIO_PORT;
	dev->MAX7219_CS_pin=CS_PIN;
	dev->MAX7219_Buffer[0] = MAX7219_SHUTDOWN_ADDR;
	dev->MAX7219_Buffer[1] = 0x01;
	if (_MAX7219SendData(dev) != MAX7219_OK) {
		return MAX7219_SEND_DATA_FAIL;
	}
	dev->MAX7219_Buffer[0] = MAX7219_DECODEMODE_ADDR;
	dev->MAX7219_Buffer[1] = 0x00;
	if (_MAX7219SendData(dev) != MAX7219_OK) {
		return MAX7219_SEND_DATA_FAIL;
	}
	dev->MAX7219_Buffer[0] = MAX7219_INTENSITY_ADDR;
	dev->MAX7219_Buffer[1] = 0x0F;
	if (_MAX7219SendData(dev) != MAX7219_OK) {
		return MAX7219_SEND_DATA_FAIL;
	}
	dev->MAX7219_Buffer[0] = MAX7219_SCANLIMIT_ADDR;
	dev->MAX7219_Buffer[1] = 0x07;
	if (_MAX7219SendData(dev) != MAX7219_OK) {
		return MAX7219_SEND_DATA_FAIL;
	}
	MAX7219_Clear(dev);
	return MAX7219_OK;
}

MAX7219_Return_Stat inline MAX7219_DisplayMatrix(MAX7219_t *dev) {
	for (uint8_t i = 1; i < 9; i++) {
		dev->MAX7219_Buffer[0] = i;
		dev->MAX7219_Buffer[1] = dev->MAX7219_Digits[i - 1];
		if (_MAX7219SendData(dev) != MAX7219_OK) {
			return MAX7219_SEND_DATA_FAIL;
		}
	}
	return MAX7219_OK;
}
