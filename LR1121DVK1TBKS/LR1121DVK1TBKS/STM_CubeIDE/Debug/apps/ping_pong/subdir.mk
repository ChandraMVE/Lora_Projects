################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
E:/LoRaSensor/LR1121DVK1TBKS/LR1121DVK1TBKS/apps/ping_pong/main_transmit.c 

OBJS += \
./apps/ping_pong/main_transmit.o 

C_DEPS += \
./apps/ping_pong/main_transmit.d 


# Each subdirectory must supply rules for building sources it contributes
apps/ping_pong/main_transmit.o: E:/LoRaSensor/LR1121DVK1TBKS/LR1121DVK1TBKS/apps/ping_pong/main_transmit.c apps/ping_pong/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -DLR1121MB1DIS=1 -DUSE_FULL_LL_DRIVER -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../../common/inc -I../../libs/smtc-hal-mcu/inc -I../../libs/smtc-hal-mcu-stm32l4/inc -I../../libs/smtc-shields/common/inc -I../../lr11xx/common -I../../lr11xx/common/printers -I../../lr11xx/lr11xx_driver/src -I../../libs/smtc-shields/lr11xx/inc -I../../libs/smtc_dbpsk_driver/src -I../../lis2de12 -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-apps-2f-ping_pong

clean-apps-2f-ping_pong:
	-$(RM) ./apps/ping_pong/main_transmit.cyclo ./apps/ping_pong/main_transmit.d ./apps/ping_pong/main_transmit.o ./apps/ping_pong/main_transmit.su

.PHONY: clean-apps-2f-ping_pong

