/*************************************************************************
*  Title:    Library for interfacing with the photoresistor on ADC 
*  Author:   Dominik Chalupka
*  File:     photor.c
*  Software: PlatformIO
*  Hardware: Arduino Uno
*  License:  MIT
**************************************************************************/

#include <avr/io.h>         // AVR device-specific IO definitions
#include <util/delay.h>     // Functions for busy-wait delay loops
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC
#include <stdlib.h>




void ADC_init() {
    // Set the ADC prescaler to 128 for 16 MHz clock (16 MHz / 128 = 125 kHz ADC clock)
    ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

    // Set reference voltage to AVcc (5V) with external capacitor at AREF pin
    ADMUX |= (1 << REFS0);

    // Enable ADC
    ADCSRA |= (1 << ADEN) | (1 << ADIE);
}

uint16_t PHOTOR_read() {
    // Mask to ensure channel number is within 0-7
    ADMUX = (ADMUX & 0xF8) | (0 & 0x07);  // Clear the channel bits and set the new channel

    // Start the conversion
    ADCSRA |= (1 << ADSC);

    while (ADCSRA & (1 << ADSC)) {
        // Wait for the conversion to complete
    }

    return ADC;

}

