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
![DE2_Schematic](https://github.com/user-attachments/assets/a7cdf0ae-7362-4a58-9beb-534daae5c42d)

List of components in the project:
- 12VDC voltage source
- NPN transistor
- Fan
- Arduino uno
- Resistor 200 Ohm
- Photoresistor
- SH1106 OLED Display
- Air temperature and humidity sensor DHT12
- Capacitive soil moisture sensor v1.2
- Non-soldering field
- Wires

Photoresistor controls the LEDs using a PWM signal, which is regulated by the Arduino's ADC depending on the light intensity. The NPN transistor is used here to switch the fan on and off for temperature regulation. It needs a 12V power supply to function properly.

## Instructions and photos
![1000027171](https://github.com/user-attachments/assets/921009fc-6c6f-46ac-ba79-856d180d2c00)

https://github.com/user-attachments/assets/09fd01c2-3a24-49cf-b40c-fbae61326e49

## References and tools

1. Visio.com
2. 
