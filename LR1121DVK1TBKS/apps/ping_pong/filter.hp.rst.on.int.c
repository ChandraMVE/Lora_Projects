/*
 ******************************************************************************
 * @file    filter_hp_rst_on_int.c
 * @author  Sensors Software Solution Team
 * @brief   This file shows how to configure the high-pass filter in
 *          "autoreset on interrupt" mode.
 *          The filter is reset when the interrupt threshold is reached
 *
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

/* STMicroelectronics evaluation boards definition */
#define STM32L4XX      /* STM32L4 series board */

/* ATTENTION: By default the driver is little endian. If you need to switch
 *            to big endian please see "Endianness definitions" in the
 *            header file of the driver (_reg.h).
 */

#if defined(STM32L4XX)
/* STM32L4XX: Define communication interface */
//#define SENSOR_BUS hi2c1

#endif

/* Includes ------------------------------------------------------------------*/
#include <string.h>
#include <stdio.h>
#include "main.h"
#include "lis2de12_reg.h"
#include "stm32l4xx_hal.h"
#include "stm32l4xx_hal_i2c.h"
#include "stm32l4xx_hal_gpio.h"
#include "filter.hp.rst.on.int.h"


// Declare your I2C handle
I2C_HandleTypeDef hi2c1;


/* Private macro -------------------------------------------------------------*/
#define    BOOT_TIME            5 //ms

/* Private variables ---------------------------------------------------------*/
static int16_t data_raw_acceleration[3];
static float acceleration_mg[3];
static uint8_t whoamI;
static uint8_t tx_buffer[1000];

/* Private functions ---------------------------------------------------------*/
/*
 *   WARNING:
 *   Functions declared in this section are defined at the end of this file
 *   and are strictly related to the hardware platform used.
 *
 */


/* Main Example --------------------------------------------------------------*/
void lis2de12_filter_hp_rst_on_int(void)
{
  lis2de12_reg_t reg;
  stmdev_ctx_t dev_ctx; //Structure rename

  /* Initialize mems driver interface */
  dev_ctx.write_reg = platform_write;
  dev_ctx.read_reg = platform_read;
  dev_ctx.mdelay = platform_delay;
  dev_ctx.handle = &hi2c1;

  /* Initialize platform specific hardware */
  platform_init();
  uint8_t regAddr = 0x0F;
  HAL_StatusTypeDef status_tx;
  HAL_StatusTypeDef status_rx;


  status_tx = HAL_I2C_Master_Transmit(&hi2c1, 0x19 << 1, regAddr, sizeof(regAddr), 1000);

  uint8_t who_am_i;
  status_rx = HAL_I2C_Master_Receive(&hi2c1, 0x19 << 1, who_am_i, sizeof(who_am_i), 1000);

  HAL_Delay(50);

  /* Wait sensor boot time */
//  platform_delay(BOOT_TIME);

  /* Check device ID */
// uint8_t dev_id = lis2de12_device_id_get(&dev_ctx, &whoamI);
//
//  if (whoamI != LIS2DE12_ID) {
//    while (1) {
//      /* manage here device not found */
//    }
//  }



  /* Set full scale to 2g */
  lis2de12_full_scale_set(&dev_ctx, LIS2DE12_2g);

  /* Route HP filter output on output registers */
  lis2de12_high_pass_on_outputs_set(&dev_ctx, PROPERTY_ENABLE);

  /* Route HP filter output on interrupt generator 1 */
  lis2de12_high_pass_int_conf_set(&dev_ctx, LIS2DE12_ON_INT1_GEN);

  /* HP filter mode is "autoreset on interrupt event" */
  lis2de12_high_pass_mode_set(&dev_ctx, LIS2DE12_AUTORST_ON_INT);

  /* Set HP filter on mode */
  lis2de12_high_pass_bandwidth_set(&dev_ctx, LIS2DE12_AGGRESSIVE);

  /* Configure interrupt on threshold on z axis low / high events */
  reg.byte = PROPERTY_DISABLE;
  reg.int1_cfg.xhie = PROPERTY_ENABLE;
  reg.int1_cfg.yhie = PROPERTY_ENABLE;
  lis2de12_int1_gen_conf_set(&dev_ctx, &reg.int1_cfg);

  /* Set interrupt threshold at ~800 mg -> 1bit = 16mg@2g */
  lis2de12_int1_gen_threshold_set(&dev_ctx, 0x30);

  /* Set duration to zero - 1 bit = 1/ODR */
  lis2de12_int1_gen_duration_set(&dev_ctx, 0);

  /* Set Output Data Rate to 25Hz */
  lis2de12_data_rate_set(&dev_ctx, LIS2DE12_ODR_25Hz);

  /* Read samples in polling mode (no int) */
  while (1) {
    /* Read output only if new value available */
    lis2de12_xl_data_ready_get(&dev_ctx, &reg.byte);

    if (reg.byte) {
      lis2de12_int1_gen_source_get(&dev_ctx, &reg.int1_src);

      /* Read accelerometer data */
      memset(data_raw_acceleration, 0x00, 3 * sizeof(int16_t));
      lis2de12_acceleration_raw_get(&dev_ctx, data_raw_acceleration); //Read Accelero meter Raw Data
      acceleration_mg[0] =
        lis2de12_from_fs2_to_mg(data_raw_acceleration[0]);
      acceleration_mg[1] =
        lis2de12_from_fs2_to_mg(data_raw_acceleration[1]);
      acceleration_mg[2] =
        lis2de12_from_fs2_to_mg(data_raw_acceleration[2]);

      sprintf((char *)tx_buffer,
              "Acceleration [mg]:\t%4.2f\t%4.2f\t%4.2f\t%02X\r\n",
              acceleration_mg[0], acceleration_mg[1], acceleration_mg[2], reg.byte);
      tx_com(tx_buffer, strlen((char const *)tx_buffer));
    }
  }
}

/*
 * @brief  Write generic device register (platform dependent)
 *
 * @param  handle    customizable argument. In this example, it is used in
 *                   order to select the correct sensor bus handler.
 * @param  reg       register to write
 * @param  bufp      pointer to data to write in register reg
 * @param  len       number of consecutive registers to write
 *
 */
int32_t platform_write(void *handle, uint8_t reg, const uint8_t *bufp,
                              uint16_t len)
{
  /* Write multiple command */
  reg |= 0x80;
  HAL_I2C_Mem_Write(handle, LIS2DE12_I2C_ADD_L, reg,
                    I2C_MEMADD_SIZE_8BIT, (uint8_t*) bufp, len, 1000);
  return 0;
}

/*
 * @brief  Read generic device register (platform dependent)
 *
 * @param  handle    customizable argument. In this example, it is used in
 *                   order to select the correct sensor bus handler.
 * @param  reg       register to read
 * @param  bufp      pointer to buffer that stores the data read
 * @param  len       number of consecutive registers to read
 *
 */
int32_t platform_read(void *handle, uint8_t reg, uint8_t *bufp,
                             uint16_t len)
{
  /* Read multiple command */
  reg |= 0x80;
  HAL_I2C_Mem_Read(handle, LIS2DE12_I2C_ADD_L, reg,
                   I2C_MEMADD_SIZE_8BIT, bufp, len, 1000);
  return 0;
}

/*
 * @brief  Write data to transmission buffer
 *
 * @param  tx_buffer     buffer to transmit
 * @param  len           number of bytes to send
 *
 */
void tx_com(uint8_t *tx_buffer, uint16_t len)
{

}

/*
 * @brief  Platform specific delay
 *
 * @param  ms        delay in milliseconds
 *
 */
void platform_delay(uint32_t ms)
{
  HAL_Delay(ms);
}

/*
 * @brief  Platform specific initialization
 */
void platform_init(void)
{
  /* Initialize peripherals as needed (e.g., I2C, UART, GPIO) */
	MX_I2C1_Init(&hi2c1);

}

