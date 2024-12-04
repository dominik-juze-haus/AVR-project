#include <avr/io.h>         // AVR device-specific IO definitions
#include <util/delay.h>     // Functions for busy-wait delay loops
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC           // I2C/TWI library for AVR-GCC         // Peter Fleury's UART library
#include <stdlib.h>        // C library. Needed for number conversions
#include <uart.h>         // C library. Needed for number conversions
#include <gpio.h>           // AVR device-specific IO definitions
#include <photor.h>         // photoresistor library for reading analog values
#include "timer.h"          // Timer library for AVR-GCC

// extrenal LED_GREEN connection
#define LED_GREEN_PORT PORTB 
#define LED_GREEN_PIN 0

//DHT12 Temperature humidity sensor
#define DHT12_ADR 0x5c
#define DHT12_HUM_mem 0
#define DHT12_TEMP_mem 2


// Photoresitor variables
const uint16_t photor_voltage_threshold = 500; // Threshold for turning on the LED
uint16_t photor_voltage_value; // ADC value of the photoresistor

// DHT12 variables
volatile uint8_t DHT12_data[5]; // Array for storing data from DHT12 sensor



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
    static uint8_t DHT12_countdown = 0;
    DHT12_countdown++;

    if (DHT12_countdown >= 50) // 50 * 33ms = 1.65s countdown
    {
        DHT12_countdown = 0;
        THS_dataread(DHT12_ADR, DHT12_HUM_mem, DHT12_data, 5); // Read data from DHT12 sensor
        
    }
    

    char photor_val_string[1];  // String for photoresiiostor value
    char DHT12_hum_string[1];  // String for DHT12 humidity value
    char DHT12_temp_string[1];  // String for DHT12 temperature value
    char DHT12_checksum_string[1];  // String for DHT12 checksum value


    sprintf(photor_val_string, "Light intensity: %d", photor_voltage_value);
    sprintf(DHT12_hum_string, "Humidity: %u.%u \t\t", DHT12_data[0], DHT12_data[1]);
    sprintf(DHT12_temp_string, "Temperature: %u.%u °C\t\t", DHT12_data[2], DHT12_data[3]);
    sprintf(DHT12_checksum_string, "Checksum: %u\t\t", DHT12_data[4]);




    uart_puts(photor_val_string);
    uart_puts(DHT12_hum_string);
    uart_puts(DHT12_temp_string);
    uart_puts(DHT12_checksum_string);
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

    




