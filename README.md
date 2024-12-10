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

## Modules
# Main
Main module includes all the header files, defines connection for simple parts (LED) and initializes all services and routines. It contains a main loop which utilizes declared functions from the library to obtain measurments from sensors and communicate with I2C peripherals, prepare data into pretty strings and put them on the OLED display and into the serial monitor UART.
#photor


## Instructions and photos
![1000027171](https://github.com/user-attachments/assets/8986efcb-698f-4686-a587-29c6455c2acc)

https://github.com/user-attachments/assets/09fd01c2-3a24-49cf-b40c-fbae61326e49

## References and tools

1. Visio.com
2. Simul.ide
3. Autodesk Fusion
