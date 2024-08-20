################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
E:/LoRaSensor/LR1121DVK1TBKS/LR1121DVK1TBKS/common/src/common_version.c \
E:/LoRaSensor/LR1121DVK1TBKS/LR1121DVK1TBKS/common/src/smtc_hal_arduino_mapping.c \
E:/LoRaSensor/LR1121DVK1TBKS/LR1121DVK1TBKS/common/src/smtc_hal_dbg_trace.c \
E:/LoRaSensor/LR1121DVK1TBKS/LR1121DVK1TBKS/common/src/smtc_shield_pinout_mapping.c \
E:/LoRaSensor/LR1121DVK1TBKS/LR1121DVK1TBKS/common/src/uart_init.c 

OBJS += \
./common/src/common_version.o \
./common/src/smtc_hal_arduino_mapping.o \
./common/src/smtc_hal_dbg_trace.o \
./common/src/smtc_shield_pinout_mapping.o \
./common/src/uart_init.o 

C_DEPS += \
./common/src/common_version.d \
./common/src/smtc_hal_arduino_mapping.d \
./common/src/smtc_hal_dbg_trace.d \
./common/src/smtc_shield_pinout_mapping.d \
./common/src/uart_init.d 


# Each subdirectory must supply rules for building sources it contributes
common/src/common_version.o: E:/LoRaSensor/LR1121DVK1TBKS/LR1121DVK1TBKS/common/src/common_version.c common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -DLR1121MB1DIS=1 -DUSE_FULL_LL_DRIVER -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../../common/inc -I../../libs/smtc-hal-mcu/inc -I../../libs/smtc-hal-mcu-stm32l4/inc -I../../libs/smtc-shields/common/inc -I../../lr11xx/common -I../../lr11xx/common/printers -I../../lr11xx/lr11xx_driver/src -I../../libs/smtc-shields/lr11xx/inc -I../../libs/smtc_dbpsk_driver/src -I../../lis2de12 -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
common/src/smtc_hal_arduino_mapping.o: E:/LoRaSensor/LR1121DVK1TBKS/LR1121DVK1TBKS/common/src/smtc_hal_arduino_mapping.c common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -DLR1121MB1DIS=1 -DUSE_FULL_LL_DRIVER -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../../common/inc -I../../libs/smtc-hal-mcu/inc -I../../libs/smtc-hal-mcu-stm32l4/inc -I../../libs/smtc-shields/common/inc -I../../lr11xx/common -I../../lr11xx/common/printers -I../../lr11xx/lr11xx_driver/src -I../../libs/smtc-shields/lr11xx/inc -I../../libs/smtc_dbpsk_driver/src -I../../lis2de12 -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
common/src/smtc_hal_dbg_trace.o: E:/LoRaSensor/LR1121DVK1TBKS/LR1121DVK1TBKS/common/src/smtc_hal_dbg_trace.c common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -DLR1121MB1DIS=1 -DUSE_FULL_LL_DRIVER -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../../common/inc -I../../libs/smtc-hal-mcu/inc -I../../libs/smtc-hal-mcu-stm32l4/inc -I../../libs/smtc-shields/common/inc -I../../lr11xx/common -I../../lr11xx/common/printers -I../../lr11xx/lr11xx_driver/src -I../../libs/smtc-shields/lr11xx/inc -I../../libs/smtc_dbpsk_driver/src -I../../lis2de12 -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
common/src/smtc_shield_pinout_mapping.o: E:/LoRaSensor/LR1121DVK1TBKS/LR1121DVK1TBKS/common/src/smtc_shield_pinout_mapping.c common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -DLR1121MB1DIS=1 -DUSE_FULL_LL_DRIVER -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../../common/inc -I../../libs/smtc-hal-mcu/inc -I../../libs/smtc-hal-mcu-stm32l4/inc -I../../libs/smtc-shields/common/inc -I../../lr11xx/common -I../../lr11xx/common/printers -I../../lr11xx/lr11xx_driver/src -I../../libs/smtc-shields/lr11xx/inc -I../../libs/smtc_dbpsk_driver/src -I../../lis2de12 -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
common/src/uart_init.o: E:/LoRaSensor/LR1121DVK1TBKS/LR1121DVK1TBKS/common/src/uart_init.c common/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -DLR1121MB1DIS=1 -DUSE_FULL_LL_DRIVER -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../../common/inc -I../../libs/smtc-hal-mcu/inc -I../../libs/smtc-hal-mcu-stm32l4/inc -I../../libs/smtc-shields/common/inc -I../../lr11xx/common -I../../lr11xx/common/printers -I../../lr11xx/lr11xx_driver/src -I../../libs/smtc-shields/lr11xx/inc -I../../libs/smtc_dbpsk_driver/src -I../../lis2de12 -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-common-2f-src

clean-common-2f-src:
	-$(RM) ./common/src/common_version.cyclo ./common/src/common_version.d ./common/src/common_version.o ./common/src/common_version.su ./common/src/smtc_hal_arduino_mapping.cyclo ./common/src/smtc_hal_arduino_mapping.d ./common/src/smtc_hal_arduino_mapping.o ./common/src/smtc_hal_arduino_mapping.su ./common/src/smtc_hal_dbg_trace.cyclo ./common/src/smtc_hal_dbg_trace.d ./common/src/smtc_hal_dbg_trace.o ./common/src/smtc_hal_dbg_trace.su ./common/src/smtc_shield_pinout_mapping.cyclo ./common/src/smtc_shield_pinout_mapping.d ./common/src/smtc_shield_pinout_mapping.o ./common/src/smtc_shield_pinout_mapping.su ./common/src/uart_init.cyclo ./common/src/uart_init.d ./common/src/uart_init.o ./common/src/uart_init.su

.PHONY: clean-common-2f-src

