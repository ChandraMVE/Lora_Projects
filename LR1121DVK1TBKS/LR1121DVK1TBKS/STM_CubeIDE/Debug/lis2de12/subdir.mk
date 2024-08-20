################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
E:/LoRaSensor/LR1121DVK1TBKS/LR1121DVK1TBKS/lis2de12/lis2de12_drv.c \
E:/LoRaSensor/LR1121DVK1TBKS/LR1121DVK1TBKS/lis2de12/lis2de12_reg.c 

OBJS += \
./lis2de12/lis2de12_drv.o \
./lis2de12/lis2de12_reg.o 

C_DEPS += \
./lis2de12/lis2de12_drv.d \
./lis2de12/lis2de12_reg.d 


# Each subdirectory must supply rules for building sources it contributes
lis2de12/lis2de12_drv.o: E:/LoRaSensor/LR1121DVK1TBKS/LR1121DVK1TBKS/lis2de12/lis2de12_drv.c lis2de12/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -DLR1121MB1DIS=1 -DUSE_FULL_LL_DRIVER -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../../common/inc -I../../libs/smtc-hal-mcu/inc -I../../libs/smtc-hal-mcu-stm32l4/inc -I../../libs/smtc-shields/common/inc -I../../lr11xx/common -I../../lr11xx/common/printers -I../../lr11xx/lr11xx_driver/src -I../../libs/smtc-shields/lr11xx/inc -I../../libs/smtc_dbpsk_driver/src -I../../lis2de12 -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
lis2de12/lis2de12_reg.o: E:/LoRaSensor/LR1121DVK1TBKS/LR1121DVK1TBKS/lis2de12/lis2de12_reg.c lis2de12/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -DLR1121MB1DIS=1 -DUSE_FULL_LL_DRIVER -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../../common/inc -I../../libs/smtc-hal-mcu/inc -I../../libs/smtc-hal-mcu-stm32l4/inc -I../../libs/smtc-shields/common/inc -I../../lr11xx/common -I../../lr11xx/common/printers -I../../lr11xx/lr11xx_driver/src -I../../libs/smtc-shields/lr11xx/inc -I../../libs/smtc_dbpsk_driver/src -I../../lis2de12 -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-lis2de12

clean-lis2de12:
	-$(RM) ./lis2de12/lis2de12_drv.cyclo ./lis2de12/lis2de12_drv.d ./lis2de12/lis2de12_drv.o ./lis2de12/lis2de12_drv.su ./lis2de12/lis2de12_reg.cyclo ./lis2de12/lis2de12_reg.d ./lis2de12/lis2de12_reg.o ./lis2de12/lis2de12_reg.su

.PHONY: clean-lis2de12

