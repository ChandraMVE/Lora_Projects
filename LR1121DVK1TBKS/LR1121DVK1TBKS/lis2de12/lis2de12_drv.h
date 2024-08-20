/**
  ******************************************************************************
  * @file    lis2de12_drv.h
  * @author  Sensors Software Solution Team
  * @brief   This file contains all the functions prototypes for the
  *          lis2de12_drv.c driver.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef LIS2DE12_DRV_H
#define LIS2DE12_DRV_H

#ifdef __cplusplus
extern "C" {
#endif  

extern float acceleration_mg[3];

extern I2C_HandleTypeDef hi2c1;

#define SENSOR_BUS hi2c1
#define LIS2DE12_I2C_ADD LIS2DE12_I2C_ADD_H


void lis2de12_filter_hp_rst_on_int(void);
void lis2de12_init_and_configure(void);
int32_t platform_write(void *handle, uint8_t reg, const uint8_t *bufp,
                              uint16_t len);
int32_t platform_read(void *handle, uint8_t reg, uint8_t *bufp,
                             uint16_t len);
void platform_delay(uint32_t ms);
void platform_init(void);
void MX_I2C1_Init(void);
void MX_GPIO_Init(void);
#ifdef __cplusplus
}
#endif

#endif /* LIS2DE12_DRV_H */
