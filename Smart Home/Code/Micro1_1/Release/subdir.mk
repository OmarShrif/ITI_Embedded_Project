################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../DIO_Program.c \
../KeyPad_Program.c \
../LCD_Program.c \
../SevenSegment_Program.c \
../UART_Program.c \
../main.c 

OBJS += \
./DIO_Program.o \
./KeyPad_Program.o \
./LCD_Program.o \
./SevenSegment_Program.o \
./UART_Program.o \
./main.o 

C_DEPS += \
./DIO_Program.d \
./KeyPad_Program.d \
./LCD_Program.d \
./SevenSegment_Program.d \
./UART_Program.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

