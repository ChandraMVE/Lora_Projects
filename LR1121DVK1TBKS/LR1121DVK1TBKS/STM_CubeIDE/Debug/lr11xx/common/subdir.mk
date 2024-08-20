################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
E:/LoRaSensor/LR1121DVK1TBKS/LR1121DVK1TBKS/lr11xx/common/apps_common.c \
E:/LoRaSensor/LR1121DVK1TBKS/LR1121DVK1TBKS/lr11xx/common/apps_version.c \
E:/LoRaSensor/LR1121DVK1TBKS/LR1121DVK1TBKS/lr11xx/common/lr11xx_hal.c 

OBJS += \
./lr11xx/common/apps_common.o \
./lr11xx/common/apps_version.o \
./lr11xx/common/lr11xx_hal.o 

C_DEPS += \
./lr11xx/common/apps_common.d \
./lr11xx/common/apps_version.d \
./lr11xx/common/lr11xx_hal.d 


# Each subdirectory must supply rules for building sources it contributes
lr11xx/common/apps_common.o: E:/LoRaSensor/LR1121DVK1TBKS/LR1121DVK1TBKS/lr11xx/common/apps_common.c lr11xx/common/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -DLR1121MB1DIS=1 -DUSE_FULL_LL_DRIVER -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../../common/inc -I../../libs/smtc-hal-mcu/inc -I../../libs/smtc-hal-mcu-stm32l4/inc -I../../libs/smtc-shields/common/inc -I../../lr11xx/common -I../../lr11xx/common/printers -I../../lr11xx/lr11xx_driver/src -I../../libs/smtc-shields/lr11xx/inc -I../../libs/smtc_dbpsk_driver/src -I../../lis2de12 -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
lr11xx/common/apps_version.o: E:/LoRaSensor/LR1121DVK1TBKS/LR1121DVK1TBKS/lr11xx/common/apps_version.c lr11xx/common/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -DLR1121MB1DIS=1 -DUSE_FULL_LL_DRIVER -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../../common/inc -I../../libs/smtc-hal-mcu/inc -I../../libs/smtc-hal-mcu-stm32l4/inc -I../../libs/smtc-shields/common/inc -I../../lr11xx/common -I../../lr11xx/common/printers -I../../lr11xx/lr11xx_driver/src -I../../libs/smtc-shields/lr11xx/inc -I../../libs/smtc_dbpsk_driver/src -I../../lis2de12 -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
lr11xx/common/lr11xx_hal.o: E:/LoRaSensor/LR1121DVK1TBKS/LR1121DVK1TBKS/lr11xx/common/lr11xx_hal.c lr11xx/common/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -DLR1121MB1DIS=1 -DUSE_FULL_LL_DRIVER -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../../common/inc -I../../libs/smtc-hal-mcu/inc -I../../libs/smtc-hal-mcu-stm32l4/inc -I../../libs/smtc-shields/common/inc -I../../lr11xx/common -I../../lr11xx/common/printers -I../../lr11xx/lr11xx_driver/src -I../../libs/smtc-shields/lr11xx/inc -I../../libs/smtc_dbpsk_driver/src -I../../lis2de12 -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-lr11xx-2f-common

clean-lr11xx-2f-common:
	-$(RM) ./lr11xx/common/apps_common.cyclo ./lr11xx/common/apps_common.d ./lr11xx/common/apps_common.o ./lr11xx/common/apps_common.su ./lr11xx/common/apps_version.cyclo ./lr11xx/common/apps_version.d ./lr11xx/common/apps_version.o ./lr11xx/common/apps_version.su ./lr11xx/common/lr11xx_hal.cyclo ./lr11xx/common/lr11xx_hal.d ./lr11xx/common/lr11xx_hal.o ./lr11xx/common/lr11xx_hal.su

.PHONY: clean-lr11xx-2f-common

