## AVR-project
# Plant climate control system 

## Introduction
Our project deals with the recording of values such as air temperature and humidity, soil moisture and sunlight. The assumption is that tropical temperatures live in temperatures of 20-22 degrees Celsius. In the event of high temperature, the fan will blow air from the terrarium and reduce the temperature. All sensors, such as the soil moisture sensor, the temperature and humidity sensor and the sunlight sensor, will project the values on the OLED display and will show basic instructions for the user to provide the plant with proper care.

## Team members and their responsibilities
- Dominik Chalupka: responsible for coding
- Lukáš Poláček: responsible for creating schematic, GitHub
- Lukáš Horák: responsible for coding
- Samuel Gubi: responsible for coding and creating schematic

## Schematic
![DE2_Schematic](https://github.com/user-attachments/assets/19ef0f04-6bf9-4653-a368-9838793214af)

List of components in the project:
- 12VDC voltage source
- NPN transistor
- Fan
- Arduino Uno board
- Resistor 200 Ohm
- Photoresistor
- SH1106 OLED Display
- Air temperature and humidity sensor DHT11
- Capacitive soil moisture sensor v1.2
- Non-soldering field
- Wires

The LED indicates insufficient lighting and i controlled via a digital pin, which is regulated by the Arduino's ADC depending on the amount of light falling on the photoresistor. The fan is operated by a PWM signal from the board and changes it's speed depending on the humidity readings. The NPN transistor is used here to switch the fan on and off for temperature and humidity regulation. It needs a 12V power supply to function properly. The OLED display communicates via I2C bus with arduino and displays all sensor readings. It is the principle of one master and several slaves.

# Modules
## Main

**the source file**

Main module includes all the header files, defines connection for simple parts (LED) and initializes all services and routines. It contains a main loop which utilizes declared functions from the library to obtain measurments from sensors and communicate with I2C peripherals, prepare data into pretty strings and put them on the OLED display and into the serial monitor UART.

## SHS

**Reading values from the soil humidity sensor**

*SHS.h, SHS.c*

Header file again carrying function prototypes. C file utilizes the ADC_init from the photor library and reads from the sensor using the ADC channel 1. The map function then normalizes the data with a formula. The SHS_read function then utilizes the previous declared functions and returns the normalized soil humidity value.

## THS

**Reading values from the DHT11 sensor through it's proprietary protocol**

*THS.h, THS.c*

Even though we used a DHT12 in labs, we've chosen DHT11 for simulation reasons (in simulide by default). The DHT11 doesn't work on I2C, excepts it relies on single wire communication. It first needs a 18 ms low and 30 us high input stimulation, to which it replies with 80 us low and 80 us high ready signal followed by 40 bits of data. Each bit starts with 50 us low and is then followed by either 27 us high, which is 0, or 70 us high, which is 1. It communicates temperature decimal and integral, humidity decimal and integral and a checksum just like the DHT12. 
In the header file, we defined the connections and function prototypes. In the C file, we initialize the pin and establish a debugged communication with the sensor as described. After obtaining data, we verify the checksum and if succesful, return the data for further operations.

## Photor

**Reading value on the photoresistor**

*photor.h, photor.c*

The header file declares the function prototypes, it's pretty simple. The c file has the initialization function and therefore serves double pourpose for initializing the AD converter and reading the values from the particular channel the photoresistor is connected to. The ADC readings come from channel 0.

## Fan

**Controling the fan speed and reading it's RPM**

*fan.h, fan.c*

The header file is, again, simple for function prototypes. The c file has a function that initializes the PWM signal generation at PD3 pin at an non-inverting mode. The tachometer function works on interupt that reads falling edges. It was important then to ensure that no any logical change would trigger interupt. The get_rpm function then calculates the RPM from the value of the counter that runs in the ISR through a simple formula. We are then displaying the RPM on the screen.

## GPIO *Atmel default*

**General purpose input output**

*gpio.h, gpio.c*

For setting pins as inputs, outputs or setting them high or low. 

## I2C *From labs*

**Two wire I2C protocol**

*I2C.h, I2C.c*

Library for communication with I2C parts, in our case, for communication with the OLED display. 

## OLED *from labs*

**Code for operating the SH1106 OLED

*OLED.h, OLED.c, font.h*

The library for communicating with the OLED screen through I2C with a header file containing information about a font used for displayed text.

##UART *by Peter Fleury*

**Code for using the UART serial monitor**

*UART.h, UART.c*

This module enables the UART serial monitor functionality primarily used for debugging, developmnent and simulations.

# Enclosure design
We chose and enclosure design that would make the unit an all-in-one solution directly stabbed to the soil. The fan would connect to pins on the chasis and would be the only external part. The design is plug-and-play.

![Enclosure 1](https://github.com/dominik-juze-haus/AVR-project/blob/main/Render1.png)

![Enclosure 2](https://github.com/dominik-juze-haus/AVR-project/blob/main/render2.png)

![Enclosure 3](https://github.com/dominik-juze-haus/AVR-project/blob/main/render3.png)

![Enclosure 4](https://github.com/dominik-juze-haus/AVR-project/blob/main/render4.png)


## Instructions and photos
Plug-and-play. Device turns on and starts functioning.

![1000027171](https://github.com/user-attachments/assets/8986efcb-698f-4686-a587-29c6455c2acc)

https://github.com/user-attachments/assets/09fd01c2-3a24-49cf-b40c-fbae61326e49

## References and tools

1. Visio.com
2. Simul.ide
3. Autodesk Fusion
