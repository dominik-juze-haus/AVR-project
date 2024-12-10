#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <uart.h>
#include <THS.h>




// Čtení analogové hodnoty z ADC

uint16_t ADC_read() {

    // Mask to ensure channel number is within 0-7
    ADMUX = (ADMUX & 0xF8) | (1 & 0x07);  // Clear the channel bits and set the new channel

    // Start the conversion
    ADCSRA |= (1 << ADSC);

    while (ADCSRA & (1 << ADSC)) {
        // Wait for the conversion to complete
    }

    return ADC;  
}

 

// Přemapování hodnot

uint16_t map(int x, int in_min, int in_max, int out_min, int out_max) {

    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;

}


uint16_t SHS_read(void) {
    int soil_hum_adc_values = ADC_read(); // Read the ADC result

    int soil_humidity = map(soil_hum_adc_values, 0, 1024, 0, 100); // Map the value to the range 0-100

    return soil_humidity; // Return the soil humidity value
}


 
