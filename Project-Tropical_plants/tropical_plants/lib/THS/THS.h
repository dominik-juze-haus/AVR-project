#ifndef THS_H
#define THS_H

#include <avr/io.h>
#include "I2C.h"

#ifndef F_CPU
#define F_CPU 16000000
#endif

void I2C_init();
void THS_dataread();

#endif
