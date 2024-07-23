/*
 * mve_LoRa.c
 *
 *  Created on: Jul 19, 2024
 *      Author: Keerthi Mallesh
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "apps_common.h"
#include "apps_utilities.h"
#include "lr11xx_radio.h"
#include "lr11xx_system.h"
#include "lr11xx_system_types.h"
#include "lr11xx_regmem.h"
#include "mve_LoRa.h"
#include "smtc_hal_dbg_trace.h"
#include "uart_init.h"
#include "smtc_hal_mcu_gpio_stm32l4.h"
#include "stm32l4xx_ll_gpio.h"
#include "stm32l4xx_ll_bus.h"


smtc_hal_mcu_status_t switch_init()
{

	LL_AHB2_GRP1_EnableClock( LL_AHB2_GRP1_PERIPH_GPIOC );

	LL_GPIO_InitTypeDef GPIO_InitStruct = {

			.Pin = LL_GPIO_PIN_13,
			.Mode = LL_GPIO_MODE_INPUT,
			.Pull = LL_GPIO_PULL_NO,
	};

		LL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	    return SMTC_HAL_MCU_STATUS_OK;
}

GPIO_PinState Switch_ReadPin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
 GPIO_PinState bitstatus;

 /* Check the parameters */
 assert_param(IS_GPIO_PIN(GPIO_Pin));

 if ((GPIOx->IDR & GPIO_Pin) != 0x00u)
 {
   bitstatus = GPIO_PIN_SET;
 }
 else
 {
   bitstatus = GPIO_PIN_RESET;
 }
 return bitstatus;
}

void switch_pressed()
{
	uint8_t buffer = 0;
	switch_init();

	HAL_DBG_TRACE_INFO( "===== Waiting for the switch to be pressed =====\n" );

	while(1)
	{
		if( Switch_ReadPin(GPIOC, LL_GPIO_PIN_13) == GPIO_PIN_RESET )
			{
				buffer++;
			}

		if( buffer == 1 )
		{
			buffer = 0;
			break;
		}
	}

 }

