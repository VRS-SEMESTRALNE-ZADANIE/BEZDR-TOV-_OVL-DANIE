################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../rfm22/rfm22.c 

OBJS += \
./rfm22/rfm22.o 

C_DEPS += \
./rfm22/rfm22.d 


# Each subdirectory must supply rules for building sources it contributes
rfm22/%.o rfm22/%.su rfm22/%.cyclo: ../rfm22/%.c rfm22/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F303x8 -c -I../Core/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/mihal/STM32CubeIDE/workspace_1.16.1/old/wirelesska/rfm22" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-rfm22

clean-rfm22:
	-$(RM) ./rfm22/rfm22.cyclo ./rfm22/rfm22.d ./rfm22/rfm22.o ./rfm22/rfm22.su

.PHONY: clean-rfm22

