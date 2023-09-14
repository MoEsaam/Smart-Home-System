################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ADC_program.c \
../Dio_program.c \
../EXTI_program.c \
../GIE_program.c \
../KEYPAD_program.c \
../LCD_program.c \
../RTC_program.c \
../TIMER0_program.c \
../TIMER1.program.c \
../TWI_program.c \
../main.c 

OBJS += \
./ADC_program.o \
./Dio_program.o \
./EXTI_program.o \
./GIE_program.o \
./KEYPAD_program.o \
./LCD_program.o \
./RTC_program.o \
./TIMER0_program.o \
./TIMER1.program.o \
./TWI_program.o \
./main.o 

C_DEPS += \
./ADC_program.d \
./Dio_program.d \
./EXTI_program.d \
./GIE_program.d \
./KEYPAD_program.d \
./LCD_program.d \
./RTC_program.d \
./TIMER0_program.d \
./TIMER1.program.d \
./TWI_program.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


