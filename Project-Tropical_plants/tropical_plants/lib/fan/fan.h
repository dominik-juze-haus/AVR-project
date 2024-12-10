#ifndef fan_h
#define fan_h

#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <uart.h>
#include <gpio.h>

#ifndef F_CPU
#define F_CPU 16000000  // CPU frequency in Hz required for UART_BAUD_SELECT
#endif

void PWM_init(void);

void set_fan_speed(uint8_t speed);

void tachometer_init(void);

uint16_t get_rpm(void);




#endif