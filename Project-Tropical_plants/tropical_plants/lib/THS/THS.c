#include <avr/io.h>
#include <avr/interrupt.h>
#include <uart.h>
#include "THS.h"

void THS_dataread(uint8_t adress, uint8_t mem_adress, uint8_t *data, uint8_t nbytes) {
    I2C_start();
    if (I2C_write(adress << 1 | I2C_WRITE) == 0) {
    
        I2C_write(mem_adress);

        I2C_stop();
        I2C_start();

        I2C_write(adress << 1 | I2C_READ);
        for (uint8_t i = 0; i < nbytes; i++) {
            if (i == nbytes - 1) {
                data[i] = I2C_read_nack();
            } else {
                data[i] = I2C_read_ack();
            }
        }
    *data = I2C_read_nack();
        I2C_stop();
    }
    else 
    {
        I2C_stop();        
    }
    

}

