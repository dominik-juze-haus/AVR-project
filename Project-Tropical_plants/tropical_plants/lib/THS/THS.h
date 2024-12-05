#ifndef THS_H
#define THS_H

#include <avr/io.h>
#include <gpio.h>

//Ports and pins for DHT11 sensor
#ifndef F_CPU
#define F_CPU 16000000
#endif

//DHT11 Temperature humidity sensor
#define DHT11_PORT  PORTB  // Define the data pin connected to DHT11
#define DHT11_PIN   1  // Define the data pin connected to DHT11

void THS_init();
uint8_t THS_dataread(float *temperature, float *humidity);

#endif
