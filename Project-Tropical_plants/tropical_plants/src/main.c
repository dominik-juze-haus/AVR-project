#include <avr/io.h>         // AVR device-specific IO definitions
#include <stdio.h>         // C library for standard I/O functions
#include <util/delay.h>     // Functions for busy-wait delay loops
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC          
#include <stdlib.h>        // C library. Needed for number conversions
#include <uart.h>         // Uart library for the serial communication
#include <gpio.h>           // AVR device-specific IO definitions
#include <photor.h>         // photoresistor library for reading analog values
#include <THS.h>            // library for reading data from DHT12 sensor
#include <I2C.h>            // I2C library 
#include <fan.h>            // Fan library        
#include <oled.h>           // OLED library
#include <fan.h>            // Fan library
#include <SHS.h>            // Soil humidity sensor library
#include "timer.h"          // Timer library for AVR-GCC

// extrenal LED_GREEN connection (PROTOTYPE purposes)
#define LED_GREEN_PORT PORTB 
#define LED_GREEN_PIN 0 



// Photoresitor variables
const uint16_t photor_voltage_threshold = 500; // Threshold for turning on the LED
uint16_t photor_voltage_value; // ADC value of the photoresistor

// Soil humidity variables
const uint16_t soil_humidity_threshold = 25; // Threshold for turning on the LED
uint16_t Soil_humidity_value; // Value of the soil humidity

//THS DHT11 variables
float DHT11_temperature; // String for DHT11 temperature value
float DHT11_humidity;  // String for DHT11 humidity value

// Fan variables
const uint16_t humidity_threshold_1 = 70; // Threshold for setting the fan speed to 1
const uint16_t humidity_threshold_2 = 80; // Threshold for setting the fan speed to 2
const uint16_t humidity_threshold_3 = 90; // Threshold for setting the fan speed to 3
uint16_t fan_speed_reading; //Fan speed value


int main(void)
{ //Initialize LED
    DDRB |= (1 << LED_GREEN_PIN);
    
    ADC_init();  // Initialize ADC
    THS_init();  // Initialize DHT11 sensor
    twi_init();  // Initialize I2C
    uart_init(UART_BAUD_SELECT(9600, F_CPU)); // Initialize UART
    PWM_init();  // Initialize PWM for the fan
    oled_init(OLED_DISP_ON); // Initialize OLED display
    tachometer_init(); // Initialize tachometer for the fan
    


    oled_clrscr(); // Clear the OLED display
    oled_charMode(DOUBLESIZE);
    oled_gotoxy(0, 0); // Set the cursor to the first line
    oled_puts("Tropical plants"); // Print the text on the OLED display
    oled_display(); // Display the OLED display



    TIM1_ovf_1sec();
    TIM1_ovf_enable();

    // Interrupts must be enabled, bacause of `uart_puts()`
    sei();

    char DHT11_hum_string[40];  // String for DHT11 humidity value
    char DHT11_temp_string[40];  // String for DHT11 temperature value
    //char DHT11_checksum_string[10];  // String for DHT11 checksum value
    char photor_val_string[40];  // String for photoresiiostor value
    char Soil_humidity_string[40]; // String for soil humidity value
    char fan_speed_string[40]; // String for fan speed value

    //int DHT11_gpio_test; // String for DHT11 GPIO test
    //char DHT11_gpio_test_string[10]; // String for DHT11 SPI test
    while (1)
    {   
        
        

        
        if(THS_dataread(&DHT11_temperature, &DHT11_humidity) == 2) // Read data from DHT11 sensor
        {
        sprintf(DHT11_hum_string, "Humidity: %.2f \t\t", DHT11_humidity); // Format the DHT12 humidity value
        sprintf(DHT11_temp_string, "Temperature: %.2f °C\t\t", DHT11_temperature); // Format the DHT12 temperature value
        if (DHT11_humidity > humidity_threshold_3)
        {
            set_fan_speed(255);
        }
        else if (DHT11_humidity > humidity_threshold_2)
        {
            set_fan_speed(170);
        }
        else if (DHT11_humidity > humidity_threshold_1)
        {
            set_fan_speed(85);
        }
        else
        {
            set_fan_speed(0);
        }
        }
        else
        {
            DHT11_humidity = 0;
            DHT11_temperature = 0;
        }
        {}
        


        photor_voltage_value = PHOTOR_read(); // Read the photoresistor value
        
            // Turn on the LED if the photor voltage is above the threshold (PROTOTYPE purposes)
        if (photor_voltage_value > photor_voltage_threshold)
        {
            //LED_GREEN_PORT |= (1 << LED_GREEN_PIN); kdyby to nefachalo
            GPIO_write_high(&LED_GREEN_PORT, LED_GREEN_PIN);
        }
        else
        {
            //LED_GREEN_PORT &= ~(1 << LED_GREEN_PIN);
            GPIO_write_low(&LED_GREEN_PORT, LED_GREEN_PIN);
        }
        
        
        Soil_humidity_value = SHS_read(); // Read the soil humidity value
        if (Soil_humidity_value < soil_humidity_threshold)
        {
        
            sprintf(Soil_humidity_string, "Soil humidity: %u Water the plants!", Soil_humidity_value); // Format the soil humidity value
        }
        else
        {
            
            sprintf(Soil_humidity_string, "Soil humidity: %u Soil moisture FINE", Soil_humidity_value); // Format the soil humidity value
        }

        //sprintf(DHT12_checksum_string, "Checksum: %u\t\t", DHT12_data[4]); // Format the DHT12 checksum value
        sprintf(photor_val_string, "Light intensity: %u", photor_voltage_value); // Format the photoresistor value
        
        fan_speed_reading = get_rpm(); // Read the fan speed
        sprintf(fan_speed_string, "Fan speed: %u RPM", fan_speed_reading); // Format the fan speed value

        uart_puts(photor_val_string); // Print the photoresistor value
        uart_puts("\r\n"); // New line
        uart_puts(DHT11_hum_string); // Print the DHT12 humidity value
        uart_puts(" ");  // Space
        uart_puts(DHT11_temp_string); // Print the DHT12 temperature value
        uart_puts("\r\n"); // New line
        uart_puts(Soil_humidity_string); // Print the soil humidity value
        uart_puts("\r\n"); // New line
        uart_puts(fan_speed_string); // Print the fan speed value
        uart_puts("\r\n"); // New line

        //uart_puts(DHT12_checksum_string); // Print the DHT12 checksum value
        //uart_puts("\r\n"); // New line
        oled_clrscr(); // Clear the OLED display
        oled_charMode(NORMALSIZE);

        oled_gotoxy(0, 0); // Set the cursor to the first line
        oled_puts(photor_val_string); // Print the text on the OLED display
        oled_gotoxy(20, 0); // Set the cursor to the fifth line
        oled_puts(fan_speed_string); // Print the text on the OLED display
        oled_gotoxy(0, 1); // Set the cursor to the second line
        oled_puts(DHT11_hum_string); // Print the text on the OLED display
        oled_gotoxy(0, 2); // Set the cursor to the third line
        oled_puts(DHT11_temp_string); // Print the text on the OLED display
        oled_gotoxy(0, 3); // Set the cursor to the fourth line
        oled_puts(Soil_humidity_string); // Print the text on the OLED display
        
        oled_display(); // Display the OLED display


    }
    return 0;
}



/*ISR(TIMER1_OVF_vect)
{   
  
} 
*/

/*
ISR(ADC_vect)
{    // Read the ADC result
    photor_voltage_value = ADC;


    int soil_hum_adc_values = ADC; // 

    int soil_humidity = map(soil_hum_adcvalues, SoilminVal, SoilmaxVal, 0, 100); // Přemapování do rozsahu 0–100
    
}  
*/


    




