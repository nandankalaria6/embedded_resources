/*
 * ssd1306_driver.h
 *
 *  Created on: Jun 19, 2026
 *      Author: NANDAN
 */

#ifndef INC_SSD1306_DRIVER_H_
#define INC_SSD1306_DRIVER_H_

#include "stm32f1xx_hal.h"
extern I2C_HandleTypeDef hi2c1;
void display_command(uint8_t cmd);
void display_init();
void display_setCursor(uint8_t page,uint8_t column);
void display_data(uint8_t data);
void display_fill(uint8_t pattern);
void display_update();

#endif /* INC_SSD1306_DRIVER_H_ */
