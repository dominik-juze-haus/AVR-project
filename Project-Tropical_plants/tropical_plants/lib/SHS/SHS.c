#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "timer.h"
#include <uart.h>
#include <THS.h>


// Kalibrační hodnoty vlhkosti


 





/* 

int main(void) {

    // Inicializace periferií

    ADC_init(); // Inicializace ADC

    uart_init(UART_BAUD_SELECT(9600, F_CPU)); // Inicializace UARTu

    TIM1_ovf_4sec(); // Nastavení časovače na 4 sekundy

    TIM1_ovf_enable(); // Povolení přerušení časovače

    sei(); // Povolení globálních přerušení

 

    char string[10];

 

    while (1) {

        int vlhkost = nactiVlhkost(); // Načtení hodnoty vlhkosti

 

        // Vypisování hodnot do UART

        uart_puts("Vlhkost: ");

        itoa(vlhkost, string, 10);

        uart_puts(string);

        uart_puts(" %\n");

 

        _delay_ms(1000); // Zpoždění 1 sekundy

    }

 

    return 0;

}

 



 

// Čtení analogové hodnoty z ADC

int SHS_read() {

    // Mask to ensure channel number is within 0-7
    ADMUX = (ADMUX & 0xF8) | (1 & 0x07);  // Clear the channel bits and set the new channel

    // Start the conversion
    ADCSRA |= (1 << ADSC);



}

 

// Přemapování hodnot

int map(int x, int in_min, int in_max, int out_min, int out_max) {

    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;

}
*/
 
