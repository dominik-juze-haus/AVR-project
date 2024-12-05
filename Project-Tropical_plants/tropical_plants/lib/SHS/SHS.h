#ifndef SHS_H
#define SHS_H

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

/*
void ADC_init(void);
int analogRead(uint8_t channel);
int nactiVlhkost(void);
int map(int x, int in_min, int in_max, int out_min, int out_max);
*/

#endif