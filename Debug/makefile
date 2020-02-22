################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/STM32F7xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
Transmisor.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
Transmisor.list \

OBJCOPY_BIN += \
Transmisor.bin \


# All Target
all: Transmisor.elf secondary-outputs

# Tool invocations
Transmisor.elf: $(OBJS) $(USER_OBJS) /Users/administrador/STM32CubeIDE/STM32F4/Transmisor/STM32F767ZITX_FLASH.ld
	arm-none-eabi-gcc -o "Transmisor.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m7 -T"/Users/administrador/STM32CubeIDE/STM32F4/Transmisor/STM32F767ZITX_FLASH.ld" --specs=nosys.specs -Wl,-Map="Transmisor.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -u _printf_float -u _scanf_float -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

Transmisor.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "Transmisor.list"
	@echo 'Finished building: $@'
	@echo ' '

Transmisor.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "Transmisor.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
