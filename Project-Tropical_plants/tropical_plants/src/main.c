#include <avr/io.h>         // AVR device-specific IO definitions
#include <util/delay.h>     // Functions for busy-wait delay loops
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC           // I2C/TWI library for AVR-GCC         // Peter Fleury's UART library
#include <stdlib.h>        // C library. Needed for number conversions
#include <uart.h>         // C library. Needed for number conversions
#include <gpio.h>           // AVR device-specific IO definitions
#include <photor.h>         // photoresistor library for reading analog values
#include "timer.h"          // Timer library for AVR-GCC


#define LED_GREEN_PORT PORTB
#define LED_GREEN_PIN 0

const uint16_t photor_voltage_threshold = 500;
uint16_t photor_voltage_value;


int main(void)
{ //Initialize LED
    DDRB |= (1 << LED_GREEN_PIN);
    
    ADC_init();  // Initialize ADC
    uart_init(UART_BAUD_SELECT(9600, F_CPU));


    TIM1_ovf_33ms();
    TIM1_ovf_enable();
    // Interrupts must be enabled, bacause of `uart_puts()`
    sei();

    PHOTOR_read();

    while (1)
    {   
    }
    return 0;

}

ISR(TIMER1_OVF_vect)
{

    char string[1];  // String for converted numbers by itoa()
    itoa(photor_voltage_value, string, 10);
    uart_puts(string);
    uart_puts("\r\n");
    
    // Turn on the LED if the photor voltage is above the threshold
    if (photor_voltage_value > photor_voltage_threshold)
    {
        //LED_GREEN_PORT |= (1 << LED_GREEN_PIN); kdyby ta mrdka nefungovala
        GPIO_write_high(&LED_GREEN_PORT, LED_GREEN_PIN);
    }
    else
    {
        //LED_GREEN_PORT &= ~(1 << LED_GREEN_PIN); kdyby ta mrdka nefungovala
        GPIO_write_low(&LED_GREEN_PORT, LED_GREEN_PIN);
    }
    PHOTOR_read();
}



ISR(ADC_vect)
{    // Read the ADC result
    photor_voltage_value = ADC;
}

    




