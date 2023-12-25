################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ADC_program.c \
../DIO_Program.c \
../LCD_Program.c \
../Lm35_Program.c \
../Servo_Program.c \
../Timer1_Program.c \
../UART_Program.c \
../main.c 

OBJS += \
./ADC_program.o \
./DIO_Program.o \
./LCD_Program.o \
./Lm35_Program.o \
./Servo_Program.o \
./Timer1_Program.o \
./UART_Program.o \
./main.o 

C_DEPS += \
./ADC_program.d \
./DIO_Program.d \
./LCD_Program.d \
./Lm35_Program.d \
./Servo_Program.d \
./Timer1_Program.d \
./UART_Program.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


