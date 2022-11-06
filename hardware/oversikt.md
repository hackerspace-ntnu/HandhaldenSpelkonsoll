## Hardware (endringer kan forekomme)
* MCU: ESP32 
* Skjerm: ILI9488 controller 480*320 4.5"
* Knapper: buttons 
* Batteri: 18650 Li-ion (3.6 V, 2600 mAh)



## Koblinger mellom ILI9488 og ESP32
|ILI9488    | ESP32 | Notes:             |
|-----------|-------|--------------------|
| SDO(MISO) |  19   | Master In Slave Out|
| SDO(MOSI) |  23   | Master out Slave In|
| SCK       |  18   | Clock Signal       | 
| CS        |   5   | Chip Select        |
| DC/RS     |   2   | Data Command       | 
| RST       |   4   | Reset              |
| VCC       |  5V   | Or 3.3V            |
| LED       |  5V   | Or 3.3V            |
| GND       |  GND  | Ground             |

## Koblinger mellom knapper og ESP32
| Knapp        | ESP32 |
|--------------|-------|
| BTN_A        |  21   | 
| BTN_B        |  32   |
| BTN_X        |  33   |
| BTN_Y        |  25   |
| BTN_DP_LEFT  |  14   | 
| BTN_DP_RIGHT |  13   | 
| BTN_DP_UP    |  26   | 
| BTN_DP_DOWN  |  27   |