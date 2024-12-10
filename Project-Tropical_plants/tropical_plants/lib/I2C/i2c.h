#ifndef I2C_h
#define I2C_h

#include <avr/io.h>

#ifndef F_CPU
#define F_CPU 16000000
#endif
#define twi_scl_clock 100000 //100kHz clock
#define TWI_BAUDRATE ((F_CPU/twi_scl_clock)-16)/(2) //baudrate calculation

#define twi_port PORTC
#define twi_pin_sda 4 // PC4 - data pin
#define twi_pin_scl 5 // PC5 - clock pin

#define TWI_WRITE 0 //write mode value
#define TWI_READ 1 //read mode value
#define TWI_ACK 1   //acknowledge value
#define TWI_NACK 0  //no acknowledge value

void twi_init();
void twi_start();
void twi_stop();

uint8_t twi_read(uint8_t ack);
uint8_t twi_write(uint8_t data);
uint8_t twi_read_ack();
uint8_t twi_read_nack();

#endif
