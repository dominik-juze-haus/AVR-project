#include <avr/io.h>         // AVR device-specific IO definitions
#include <stdio.h>         // C library for standard I/O functions
#include <util/delay.h>     // Functions for busy-wait delay loops
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC           // I2C/TWI library for AVR-GCC         // Peter Fleury's UART library
#include <stdlib.h>        // C library. Needed for number conversions
#include <uart.h>         // C library. Needed for number conversions
#include <gpio.h>    
#include <fan.h>        // AVR device-specific IO definitions

volatile uint16_t rpm_count = 0;

void PWM_init(void)
{
    DDRD |= (1 << PD3);  // Set the PD3 pin (Digital 3) as output

    // Set Timer2: Fast PWM, non-inverting mode, prescaler 64
    TCCR2A = (1 << COM2B1) | (1 << WGM21) | (1 << WGM20);
    TCCR2B = (1 << CS22);  // Prescaler 64
}

// Function to set the fan speed (value 0-255)
void set_fan_speed(uint8_t speed)
{
    OCR2B = speed;
}
//

// Tachometer initialization on pin D2 (INT0)
void tachometer_init(void)
{
    DDRD &= ~(1 << PD2); // Set PD2 as input
    PORTD |= (1 << PD2); // Enable pull-up resistor on PD2
    EICRA |= (1 << ISC01); // Falling edge will trigger interrupt
    EICRA &= ~(1 << ISC00); // Logical change won't trigger interrupt

    EIMSK |= (1 << INT0); // Enable external interrupt 0
}

ISR(INT0_vect)
{
    rpm_count++;
}

uint16_t get_rpm(void)
{
    uint16_t rpm = (rpm_count * 60) / 2;
    rpm_count = 0;
    return rpm;
}