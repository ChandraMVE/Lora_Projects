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
#include "main.h"

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
float acceleration_mg[3];
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
static void MX_GPIO_Init(void);

/* Main Example --------------------------------------------------------------*/
void lis2de12_filter_hp_rst_on_int(void)
{
  lis2de12_reg_t reg;
  lis2de12_ctrl_reg3_t reg3;
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
  /*set interrupt on INT1 I1_ZYXDA*/
  reg3.i1_overrun = PROPERTY_ENABLE;
  reg3.i1_wtm = PROPERTY_ENABLE;
  reg3.i1_zyxda = PROPERTY_ENABLE;
  reg3.i1_ia2 = PROPERTY_ENABLE;
  reg3.i1_ia1 = PROPERTY_ENABLE;
  reg3.i1_click = PROPERTY_ENABLE;
  lis2de12_pin_int1_config_set(&dev_ctx,&reg3);
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
  while (1) {
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
      if ((GPIOA->IDR & LL_GPIO_PIN_9) != 0x00u)
      {
    	  HAL_DBG_TRACE_INFO( "AccX: %08.4f AccY: %08.4f AccZ: %08.4f\n\r", acceleration_mg[0], acceleration_mg[1], acceleration_mg[2]);
    	  break;
      }
    }
  }
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
	MX_GPIO_Init();
}


/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  LL_EXTI_InitTypeDef EXTI_InitStruct = {0};
  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOC);
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOH);
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOA);
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOB);

  /**/
  LL_GPIO_ResetOutputPin(GPIOC, LL_GPIO_PIN_0|LL_GPIO_PIN_1);

  /**/
  LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_0|LL_GPIO_PIN_8);

  /**/
  LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_0|LL_GPIO_PIN_4);

  /**/
  LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTC, LL_SYSCFG_EXTI_LINE13);

  /**/
  EXTI_InitStruct.Line_0_31 = LL_EXTI_LINE_13;
  EXTI_InitStruct.Line_32_63 = LL_EXTI_LINE_NONE;
  EXTI_InitStruct.LineCommand = ENABLE;
  EXTI_InitStruct.Mode = LL_EXTI_MODE_IT;
  EXTI_InitStruct.Trigger = LL_EXTI_TRIGGER_FALLING;
  LL_EXTI_Init(&EXTI_InitStruct);

  /**/
  LL_GPIO_SetPinPull(B1_GPIO_Port, B1_Pin, LL_GPIO_PULL_NO);

  /**/
  LL_GPIO_SetPinMode(B1_GPIO_Port, B1_Pin, LL_GPIO_MODE_INPUT);

  /**/
  GPIO_InitStruct.Pin = LL_GPIO_PIN_0|LL_GPIO_PIN_1;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = LL_GPIO_PIN_0|LL_GPIO_PIN_8;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = LL_GPIO_PIN_1|LL_GPIO_PIN_4|LL_GPIO_PIN_9;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = LL_GPIO_PIN_0|LL_GPIO_PIN_4;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = LL_GPIO_PIN_3;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}
