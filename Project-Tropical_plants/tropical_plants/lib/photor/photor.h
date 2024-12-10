#ifndef PHOTOR_H
#define PHOTOR_H

#ifndef F_CPU
#define F_CPU 16000000
#endif


#include <avr/io.h>



void ADC_init();
uint16_t PHOTOR_read();





#endif
