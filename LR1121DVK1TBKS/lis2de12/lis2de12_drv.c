/*
 ******************************************************************************
 * @file    filter_hp_rst_on_int.c
 * @author  Sensors Software Solution Team
 * @brief   This file show how to configure the high-pass filter in
 *          "autoreset on inteerupt" mode.
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

/* Includes ------------------------------------------------------------------*/
#include <string.h>
#include <stdio.h>
#include "lis2de12_reg.h"

#include "stm32l4xx_hal.h"
#include "stm32l4xx_ll_gpio.h"
#include "stm32l4xx_ll_utils.h"
#include "smtc_hal_dbg_trace.h"

/* Private macro -------------------------------------------------------------*/
#define    BOOT_TIME            5 //ms

I2C_HandleTypeDef hi2c1;

#define SENSOR_BUS hi2c1
#define LIS2DE12_I2C_ADD LIS2DE12_I2C_ADD_H

/* Private variables ---------------------------------------------------------*/
static int16_t data_raw_acceleration[3];
static float acceleration_mg[3];
static uint8_t whoamI;

/* Extern variables ----------------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/
/*
 *   WARNING:
 *   Functions declare in this section are defined at the end of this file
 *   and are strictly related to the hardware platform used.
 *
 */
static int32_t platform_write(void *handle, uint8_t reg, const uint8_t *bufp,
                              uint16_t len);
static int32_t platform_read(void *handle, uint8_t reg, uint8_t *bufp,
                             uint16_t len);
static void platform_delay(uint32_t ms);
static void platform_init(void);
static void MX_I2C1_Init(void);

/* Main Example --------------------------------------------------------------*/
void lis2de12_filter_hp_rst_on_int(void)
{
  lis2de12_reg_t reg;
  stmdev_ctx_t dev_ctx;
  /* Initialize mems driver interface */
  dev_ctx.write_reg = platform_write;
  dev_ctx.read_reg = platform_read;
  dev_ctx.mdelay = platform_delay;
  dev_ctx.handle = &SENSOR_BUS;
  /* Initialize platform specific hardware */
  platform_init();
  /* Wait sensor boot time */
  platform_delay(BOOT_TIME);
  /* Check device ID */
  lis2de12_device_id_get(&dev_ctx, &whoamI);

  if (whoamI != LIS2DE12_ID) {
    while (1) {
      /* manage here device not found */
    }
  }

  /* Set full scale to 2g */
  lis2de12_full_scale_set(&dev_ctx, LIS2DE12_2g);
  /* route HP filter output on outputs registers */
  lis2de12_high_pass_on_outputs_set(&dev_ctx, PROPERTY_ENABLE);
  /* route HP filter output on interrupt generator 1 */
  lis2de12_high_pass_int_conf_set(&dev_ctx, LIS2DE12_ON_INT1_GEN);
  /* HP filter mode is "autoreset on inteerupt event" */
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
//  while (1) {
    /* Read output only if new value available */
    lis2de12_xl_data_ready_get(&dev_ctx, &reg.byte);

    if (reg.byte) {
      lis2de12_int1_gen_source_get(&dev_ctx, &reg.int1_src);
      /* Read accelerometer data */
      memset(data_raw_acceleration, 0x00, 3 * sizeof(int16_t));
      lis2de12_acceleration_raw_get(&dev_ctx, data_raw_acceleration);
      acceleration_mg[0] =
        lis2de12_from_fs2_to_mg(data_raw_acceleration[0]);
      acceleration_mg[1] =
        lis2de12_from_fs2_to_mg(data_raw_acceleration[1]);
      acceleration_mg[2] =
        lis2de12_from_fs2_to_mg(data_raw_acceleration[2]);
//      sprintf((char *)tx_buffer,
//              "Acceleration [mg]:\t%4.2f\t%4.2f\t%4.2f\t%02X\r\n",
//              acceleration_mg[0], acceleration_mg[1], acceleration_mg[2], reg.byte);
//      tx_com(tx_buffer, strlen((char const *)tx_buffer));
      HAL_DBG_TRACE_INFO( "AccX: %08.4f AccY: %08.4f AccZ: %08.4f\n\r", acceleration_mg[0], acceleration_mg[1], acceleration_mg[2]);
    }
//  }
}

/*
 * @brief  Write generic device register (platform dependent)
 *
 * @param  handle    customizable argument. In this examples is used in
 *                   order to select the correct sensor bus handler.
 * @param  reg       register to write
 * @param  bufp      pointer to data to write in register reg
 * @param  len       number of consecutive register to write
 *
 */
static int32_t platform_write(void *handle, uint8_t reg, const uint8_t *bufp,
                              uint16_t len)
{
  /* Write multiple command */
  reg |= 0x80;
  HAL_I2C_Mem_Write(handle, LIS2DE12_I2C_ADD, reg,
                    I2C_MEMADD_SIZE_8BIT, (uint8_t*) bufp, len, 1000);
  return 0;
}

/*
 * @brief  Read generic device register (platform dependent)
 *
 * @param  handle    customizable argument. In this examples is used in
 *                   order to select the correct sensor bus handler.
 * @param  reg       register to read
 * @param  bufp      pointer to buffer that store the data read
 * @param  len       number of consecutive register to read
 *
 */
static int32_t platform_read(void *handle, uint8_t reg, uint8_t *bufp,
                             uint16_t len)
{
  /* Read multiple command */
  reg |= 0x80;
  HAL_I2C_Mem_Read(handle, LIS2DE12_I2C_ADD, reg,
                   I2C_MEMADD_SIZE_8BIT, bufp, len, 1000);
  return 0;
}

/*
 * @brief  platform specific delay (platform dependent)
 *
 * @param  ms        delay in ms
 *
 */
static void platform_delay(uint32_t ms)
{
	LL_mDelay(ms);
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.Timing = 0x10D19CE4;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}
/*
 * @brief  platform specific initialization (platform dependent)
 */
static void platform_init(void)
{
	MX_I2C1_Init();
}

