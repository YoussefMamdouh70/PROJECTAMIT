################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ADC_program.c \
../DIO_program.c \
../Delay_program.c \
../I2C_program.c \
../ICU_program.c \
../INT_program.c \
../Keypad_program.c \
../LCD_program.c \
../LED_program.c \
../PWM_software_program.c \
../SPI_program.c \
../S_SEGMENT.c \
../TIMER_program.c \
../UART_program.c \
../assingment.c 

OBJS += \
./ADC_program.o \
./DIO_program.o \
./Delay_program.o \
./I2C_program.o \
./ICU_program.o \
./INT_program.o \
./Keypad_program.o \
./LCD_program.o \
./LED_program.o \
./PWM_software_program.o \
./SPI_program.o \
./S_SEGMENT.o \
./TIMER_program.o \
./UART_program.o \
./assingment.o 

C_DEPS += \
./ADC_program.d \
./DIO_program.d \
./Delay_program.d \
./I2C_program.d \
./ICU_program.d \
./INT_program.d \
./Keypad_program.d \
./LCD_program.d \
./LED_program.d \
./PWM_software_program.d \
./SPI_program.d \
./S_SEGMENT.d \
./TIMER_program.d \
./UART_program.d \
./assingment.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


