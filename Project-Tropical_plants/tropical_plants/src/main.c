#include <avr/io.h>         // AVR device-specific IO definitions
#include <stdio.h>         // C library for standard I/O functions
#include <util/delay.h>     // Functions for busy-wait delay loops
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC           // I2C/TWI library for AVR-GCC         // Peter Fleury's UART library
#include <stdlib.h>        // C library. Needed for number conversions
#include <uart.h>         // C library. Needed for number conversions
#include <gpio.h>           // AVR device-specific IO definitions
#include <photor.h>         // photoresistor library for reading analog values
#include <THS.h>            // library for reading data from DHT12 sensor
#include <I2C.h>            // I2C library 
#include "timer.h"          // Timer library for AVR-GCC

// extrenal LED_GREEN connection (PROTOTYPE purposes)
#define LED_GREEN_PORT PORTB 
#define LED_GREEN_PIN 0 



// Photoresitor variables
const uint16_t photor_voltage_threshold = 500; // Threshold for turning on the LED
uint16_t photor_voltage_value; // ADC value of the photoresistor

// Soil humidity variables
//int SoilmaxVal = 0;
//int SoilminVal = 1024;

//THS DHT11 variables
float DHT11_temperature; // String for DHT11 temperature value
float DHT11_humidity;  // String for DHT11 humidity value


int main(void)
{ //Initialize LED
    DDRB |= (1 << LED_GREEN_PIN);
    
    ADC_init();  // Initialize ADC
    THS_init();  // Initialize DHT11 sensor
    I2C_init();  // Initialize I2C
    uart_init(UART_BAUD_SELECT(9600, F_CPU)); // Initialize UART
    


    TIM1_ovf_1sec();
    TIM1_ovf_enable();
    // Interrupts must be enabled, bacause of `uart_puts()`
    sei();

    char DHT12_hum_string[40];  // String for DHT11 humidity value
    char DHT12_temp_string[40];  // String for DHT11 temperature value
    //char DHT12_checksum_string[10];  // String for DHT11 checksum value
    char photor_val_string[40];  // String for photoresiiostor value

    //int DHT11_gpio_test; // String for DHT11 GPIO test
    //char DHT11_gpio_test_string[10]; // String for DHT11 SPI test
    while (1)
    {   
        
        PHOTOR_read();
        
        if(THS_dataread(&DHT11_temperature, &DHT11_humidity) == 2) // Read data from DHT11 sensor
        {
        sprintf(DHT12_hum_string, "Humidity: %.2f \t\t", DHT11_humidity); // Format the DHT12 humidity value
        sprintf(DHT12_temp_string, "Temperature: %.2f °C\t\t", DHT11_temperature); // Format the DHT12 temperature value
        }


        //DHT11_gpio_test = GPIO_read(&DHT11_PORT, DHT11_PIN);
        
        //itoa(DHT11_gpio_test, DHT11_gpio_test_string, 10);

        
        //uart_puts(DHT11_gpio_test_string); // Print the DHT11 GPIO test
        //uart_puts("\r\n"); // New line
        

            // Turn on the LED if the photor voltage is above the threshold (PROTOTYPE purposes)
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

        //sprintf(DHT12_checksum_string, "Checksum: %u\t\t", DHT12_data[4]); // Format the DHT12 checksum value
        sprintf(photor_val_string, "Light intensity: %u", photor_voltage_value); // Format the photoresistor value
        
        uart_puts(photor_val_string); // Print the photoresistor value
        uart_puts("\r\n"); // New line
        uart_puts(DHT12_hum_string); // Print the DHT12 humidity value
        uart_puts(" ");  // Space
        uart_puts(DHT12_temp_string); // Print the DHT12 temperature value
        uart_puts("\r\n"); // New line

        //uart_puts(DHT12_checksum_string); // Print the DHT12 checksum value
        //uart_puts("\r\n"); // New line


    }
    return 0;

}



ISR(TIMER1_OVF_vect)
{   
  
} 
    
ISR(ADC_vect)
{    // Read the ADC result
    photor_voltage_value = ADC;

    /*
    int soil_hum_adc_values = ADC; // 

    int soil_humidity = map(soil_hum_adcvalues, SoilminVal, SoilmaxVal, 0, 100); // Přemapování do rozsahu 0–100
    */
}

    




