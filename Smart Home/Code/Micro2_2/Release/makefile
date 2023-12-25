################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
Micro2_2.lss \

FLASH_IMAGE += \
Micro2_2.hex \

EEPROM_IMAGE += \
Micro2_2.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: Micro2_2.elf secondary-outputs

# Tool invocations
Micro2_2.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,Micro2_2.map -mmcu=atmega32 -o "Micro2_2.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Micro2_2.lss: Micro2_2.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S Micro2_2.elf  >"Micro2_2.lss"
	@echo 'Finished building: $@'
	@echo ' '

Micro2_2.hex: Micro2_2.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex Micro2_2.elf  "Micro2_2.hex"
	@echo 'Finished building: $@'
	@echo ' '

Micro2_2.eep: Micro2_2.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex Micro2_2.elf  "Micro2_2.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Micro2_2.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 Micro2_2.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) Micro2_2.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
