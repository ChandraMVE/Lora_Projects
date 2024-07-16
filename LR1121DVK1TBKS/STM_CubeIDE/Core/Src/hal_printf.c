//-----------------------------------------------------------------
///
///     \file hal_printf.c
///
///     \brief print the data on uart
///
///
///     \author       CHandrashekhar Venaktesh
///
///     Location:     India
///
///     Project Name: LORA MVE Stack
///
///     \date Created 01May2024
///
///
/// Copyright © 2024 Microvision embedded pvt ltd
///
/// Confidential Property of Microvision
///
//-----------------------------------------------------------------

//==============================================================================
//          __             __   ___  __
//  | |\ | /  ` |    |  | |  \ |__  /__`
//  | | \| \__, |___ \__/ |__/ |___ .__/
//
//==============================================================================
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "main.h"
#include "cmsis_os.h"

//==============================================================================
//   __   ___  ___         ___  __
//  |  \ |__  |__  | |\ | |__  /__`
//  |__/ |___ |    | | \| |___ .__/
//
//==============================================================================
#define PRINT_BUFFER_SIZE 100
extern UART_HandleTypeDef huart2;
//==============================================================================
//   __        __   __                          __   __
//  / _` |    /  \ |__)  /\  |       \  /  /\  |__) /__`
//  \__> |___ \__/ |__) /~~\ |___     \/  /~~\ |  \ .__/
//
//==============================================================================

//==============================================================================
//   __  ___      ___    __                __   __
//  /__`  |   /\   |  | /  `    \  /  /\  |__) /__`
//  .__/  |  /~~\  |  | \__,     \/  /~~\ |  \ .__/
//
//==============================================================================

/*******************************************************************************
 * Function name  : HAL_printf_valist
 *
 * Description    : Custom printf function in order to use HAL_UART_Transmit()
 * Parameters     : *fmt String to print
 * 					argp Parameters list
 * Returns        : None
 *
 * Known Issues   :
 * Note           :
 * author         : Chandrashekhar Venkatesh
 * date           : 15JULY2024
 ******************************************************************************/

void HAL_printf_valist(const char *fmt, va_list argp) {
  char string[PRINT_BUFFER_SIZE];

  if (vsprintf(string, fmt, argp) > 0) {
    HAL_UART_Transmit(&huart2, (uint8_t*)string, strlen(string), HAL_MAX_DELAY); // send message via UART
  } else {
	HAL_UART_Transmit(&huart2, (uint8_t*)"E - Print\n", 14, HAL_MAX_DELAY);
  }
}

/*******************************************************************************
 * Function name  : HAL_printf_valist
 *
 * Description    : Custom printf function, only translate to va_list arg HAL_UART.
 * Parameters     : *fmt String to print
 * 					Data
 * Returns        : None
 *
 * Known Issues   :
 * Note           :
 * author         : Chandrashekhar Venkatesh
 * date           : 15JULY2024
 ******************************************************************************/
void HAL_printf(const char *fmt, ...) {
  va_list argp;

  va_start(argp, fmt);
  HAL_printf_valist(fmt, argp);
  va_end(argp);
}
