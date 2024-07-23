/*
 * mve_LoRa.h
 *
 *  Created on: Jul 19, 2024
 *      Author: User
 */

#ifndef APPS_MVE_LORA_MVE_LORA_H_
#define APPS_MVE_LORA_MVE_LORA_H_


smtc_hal_mcu_status_t switch_init();
GPIO_PinState Switch_ReadPin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void switch_pressed();


#endif /* APPS_MVE_LORA_MVE_LORA_H_ */
