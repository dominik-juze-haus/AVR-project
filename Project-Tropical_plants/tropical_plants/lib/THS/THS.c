/*************************************************************************
*  Title:    Library for interfacing with the DHT11 sensor 
*  Author:   Dominik Chalupka
*  File:     THS.c
*  Software: PlatformIO
*  Hardware: Arduino Uno
*  License:  MIT
**************************************************************************/

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <gpio.h>
#include <uart.h>
#include "THS.h"

volatile long int timeout = 100000;  // Timeout variable  

void THS_init() {
    // Set DHT11 pin as output to send start signal to the sensor
    GPIO_mode_output(&DHT11_PORT,DHT11_PIN);
    GPIO_write_high(&DHT11_PORT,DHT11_PIN);
    //DDRB |= (1 << DHT11_PIN);
}

uint8_t THS_dataread(float *temperature, float *humidity) {
    uint8_t data[5] = {0};  // Array to hold the 40 bits (5 bytes)
    char debug_string[40];  // String for debugging

    GPIO_mode_output(&DHT11_PORT,DHT11_PIN);
    sprintf(debug_string, "PIN: Output set");
    uart_puts(debug_string);
    uart_puts("\r\n");


    // Send start signal
    GPIO_write_low(&DHT11_PORT,DHT11_PIN);  // Pull pin low
    _delay_ms(20);               // Wait for 18-20 ms
    sprintf(debug_string, "Start signal sent 18 ms");
    uart_puts(debug_string);
    uart_puts("\r\n");

    GPIO_write_high(&DHT11_PORT,DHT11_PIN);   // Pull pin high
    _delay_us(40);               // Wait for 20-40 us
    sprintf(debug_string, "Pull up 40 us");

    // Set pin to input to read data
    GPIO_mode_input_nopull(&DHT11_PORT,DHT11_PIN);
    sprintf(debug_string, "PIN: Input set");
    uart_puts(debug_string);
    uart_puts("\r\n");
    
    if (GPIO_read(&DHT11_PORT, DHT11_PIN) == 0) {
        sprintf(debug_string, "Sensor response received");
        uart_puts(debug_string);
        uart_puts("\r\n");
    }
    
    // DDRB &= ~(1 << DHT11_PIN);
    // Wait DHT11 response
    //_delay_us(80);
    timeout = 100000;
    while (GPIO_read(&DHT11_PORT, DHT11_PIN) == 0 && --timeout);  // Wait for the sensor to pull the pin high
    if (timeout == 0) sprintf(debug_string, "Timemout");     // Return an error code if the sensor does not pull the pin high
    uart_puts(debug_string);
    uart_puts("\r\n");

    if (GPIO_read(&DHT11_PORT, DHT11_PIN) == 1) {   // Check if the pin is high
        sprintf(debug_string, "Sensor response received");
        _delay_us(80);
    }
        // Read data 
    
    for (int byte = 0; byte < 5; byte++) { 
            for (int bit = 0; bit < 8; bit++) {

                timeout = 100000;                 
                while (GPIO_read(&DHT11_PORT, DHT11_PIN) && --timeout);  // Wait for the sensor to pull the pin high
                if (timeout == 0) sprintf(debug_string, "Timemout");     // Return an error code if the sensor does not pull the pin high
                uart_puts(debug_string);
                uart_puts("\r\n");
                //_delay_us(50);
                if (GPIO_read(&DHT11_PORT, DHT11_PIN) == 0) 
                {   sprintf(debug_string, "Error, expected 1");
                    uart_puts(debug_string);
                    uart_puts("\r\n");  
                } 
                else
                {   sprintf(debug_string, "Bit receiving");
                    uart_puts(debug_string);
                    uart_puts("\r\n");
                }


                _delay_us(30);
                if (GPIO_read(&DHT11_PORT, DHT11_PIN)) {  // If the sensor pin is still high 
                    data[byte] |= (1 << (7 - bit));  // Write bit to data array if high
                    while (GPIO_read(&DHT11_PORT, DHT11_PIN) == 1);  // Wait for the sensor to pull the pin low
                }
        }
    }
    
    // Verify checksum
    if (data[4] == (data[0] + data[1] + data[2] + data[3])) {
        *humidity = data[0] + data[1] * 0.1;  // Convert to float 
        *temperature = data[2] + data[3] * 0.1;  // Convert to float

        return 2;  // Successful read
    }    
return 0;  // Return an error code if checksum verification fails
}




