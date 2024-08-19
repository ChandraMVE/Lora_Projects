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



void lis2de12_filter_hp_rst_on_int(void);

#ifdef __cplusplus
}
#endif

#endif /* LIS2DE12_DRV_H */
