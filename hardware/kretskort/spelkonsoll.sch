EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Spelkonsoll"
Date "2022-01-28"
Rev "V1.0"
Comp "Hackerspace, Prosjekt: Håndholdt Spillkonsoll"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L spelkonsoll-rescue:ILI9488-ILI9488 U2
U 1 1 61F441BE
P 3050 5000
F 0 "U2" H 3050 5915 50  0000 C CNN
F 1 "ILI9488" H 3050 5824 50  0000 C CNN
F 2 "ESP32-DEVKITC-32D:ILI9488" H 2550 5950 50  0001 C CNN
F 3 "" H 2550 5950 50  0001 C CNN
	1    3050 5000
	1    0    0    -1  
$EndComp
$Comp
L spelkonsoll-rescue:ESP32-DEVKITC-32D-ESP32-DEVKITC-32D U1
U 1 1 61F1CC6B
P 3050 2200
F 0 "U1" H 3050 3367 50  0000 C CNN
F 1 "ESP32-DEVKITC-32D" H 3050 3276 50  0000 C CNN
F 2 "ESP32-DEVKITC-32D:MODULE_ESP32-DEVKITC-32D" H 3050 2200 50  0001 L BNN
F 3 "" H 3050 2200 50  0001 L BNN
F 4 "4" H 3050 2200 50  0001 L BNN "PARTREV"
F 5 "Espressif Systems" H 3050 2200 50  0001 L BNN "MANUFACTURER"
	1    3050 2200
	1    0    0    -1  
$EndComp
$Comp
L spelkonsoll-rescue:+5V-power #PWR05
U 1 1 61F50C10
P 2150 3100
F 0 "#PWR05" H 2150 2950 50  0001 C CNN
F 1 "+5V" V 2165 3228 50  0000 L CNN
F 2 "" H 2150 3100 50  0001 C CNN
F 3 "" H 2150 3100 50  0001 C CNN
	1    2150 3100
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2250 3100 2150 3100
$Comp
L spelkonsoll-rescue:GND-power #PWR06
U 1 1 61F5615F
P 3950 1300
F 0 "#PWR06" H 3950 1050 50  0001 C CNN
F 1 "GND" V 3955 1172 50  0000 R CNN
F 2 "" H 3950 1300 50  0001 C CNN
F 3 "" H 3950 1300 50  0001 C CNN
	1    3950 1300
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3950 1300 3850 1300
Text GLabel 3850 2000 2    50   Input ~ 0
MISO
Text GLabel 3850 1400 2    50   Input ~ 0
MOSI
Text GLabel 1750 5250 0    50   Input ~ 0
DC\RS
Text GLabel 3850 2300 2    50   Input ~ 0
DC\RS
Text GLabel 3850 2500 2    50   Input ~ 0
RESET
Text GLabel 3850 2100 2    50   Input ~ 0
SCK
Text GLabel 3850 2400 2    50   Input ~ 0
CS
NoConn ~ 1750 4350
NoConn ~ 1750 4450
NoConn ~ 1750 4550
NoConn ~ 1750 4650
NoConn ~ 1750 4750
NoConn ~ 4350 4850
NoConn ~ 4350 4950
NoConn ~ 4350 5050
NoConn ~ 4350 5150
Text GLabel 1750 4850 0    50   Input ~ 0
MISO
Text GLabel 1750 5050 0    50   Input ~ 0
SCK
Text GLabel 1750 5150 0    50   Input ~ 0
MOSI
Text GLabel 1750 5350 0    50   Input ~ 0
RESET
Text GLabel 1750 5450 0    50   Input ~ 0
CS
$Comp
L spelkonsoll-rescue:SW_Push-Switch SW5
U 1 1 62030F73
P 8750 2300
F 0 "SW5" H 8750 2585 50  0000 C CNN
F 1 "SW_Push" H 8750 2494 50  0000 C CNN
F 2 "footprints:B3F1052" H 8750 2500 50  0001 C CNN
F 3 "~" H 8750 2500 50  0001 C CNN
	1    8750 2300
	1    0    0    -1  
$EndComp
$Comp
L spelkonsoll-rescue:SW_Push-Switch SW6
U 1 1 620331E8
P 8750 2900
F 0 "SW6" H 8750 3185 50  0000 C CNN
F 1 "SW_Push" H 8750 3094 50  0000 C CNN
F 2 "footprints:B3F1052" H 8750 3100 50  0001 C CNN
F 3 "~" H 8750 3100 50  0001 C CNN
	1    8750 2900
	1    0    0    -1  
$EndComp
Text GLabel 8550 2300 0    50   Input ~ 0
BTN_A
Text GLabel 3850 1800 2    50   Input ~ 0
BTN_A
Text GLabel 8550 2900 0    50   Input ~ 0
BTN_B
Text GLabel 2250 1900 0    50   Input ~ 0
BTN_B
$Comp
L spelkonsoll-rescue:SW_Push-Switch SW7
U 1 1 62044CE9
P 8750 3500
F 0 "SW7" H 8750 3785 50  0000 C CNN
F 1 "SW_Push" H 8750 3694 50  0000 C CNN
F 2 "footprints:B3F1052" H 8750 3700 50  0001 C CNN
F 3 "~" H 8750 3700 50  0001 C CNN
	1    8750 3500
	1    0    0    -1  
$EndComp
$Comp
L spelkonsoll-rescue:SW_Push-Switch SW8
U 1 1 62045913
P 8750 4100
F 0 "SW8" H 8750 4385 50  0000 C CNN
F 1 "SW_Push" H 8750 4294 50  0000 C CNN
F 2 "footprints:B3F1052" H 8750 4300 50  0001 C CNN
F 3 "~" H 8750 4300 50  0001 C CNN
	1    8750 4100
	1    0    0    -1  
$EndComp
Text GLabel 8550 3500 0    50   Input ~ 0
BTN_X
Text GLabel 8550 4100 0    50   Input ~ 0
BTN_Y
Text GLabel 2250 2000 0    50   Input ~ 0
BTN_X
Text GLabel 2250 2100 0    50   Input ~ 0
BTN_Y
$Comp
L spelkonsoll-rescue:SW_Push-Switch SW1
U 1 1 6208388F
P 7550 2300
F 0 "SW1" H 7550 2585 50  0000 C CNN
F 1 "SW_Push" H 7550 2494 50  0000 C CNN
F 2 "footprints:B3F1052" H 7550 2500 50  0001 C CNN
F 3 "~" H 7550 2500 50  0001 C CNN
	1    7550 2300
	1    0    0    -1  
$EndComp
$Comp
L spelkonsoll-rescue:SW_Push-Switch SW2
U 1 1 62083D6E
P 7550 2900
F 0 "SW2" H 7550 3185 50  0000 C CNN
F 1 "SW_Push" H 7550 3094 50  0000 C CNN
F 2 "footprints:B3F1052" H 7550 3100 50  0001 C CNN
F 3 "~" H 7550 3100 50  0001 C CNN
	1    7550 2900
	1    0    0    -1  
$EndComp
$Comp
L spelkonsoll-rescue:SW_Push-Switch SW3
U 1 1 620840F6
P 7550 3500
F 0 "SW3" H 7550 3785 50  0000 C CNN
F 1 "SW_Push" H 7550 3694 50  0000 C CNN
F 2 "footprints:B3F1052" H 7550 3700 50  0001 C CNN
F 3 "~" H 7550 3700 50  0001 C CNN
	1    7550 3500
	1    0    0    -1  
$EndComp
$Comp
L spelkonsoll-rescue:SW_Push-Switch SW4
U 1 1 620844B6
P 7550 4100
F 0 "SW4" H 7550 4385 50  0000 C CNN
F 1 "SW_Push" H 7550 4294 50  0000 C CNN
F 2 "footprints:B3F1052" H 7550 4300 50  0001 C CNN
F 3 "~" H 7550 4300 50  0001 C CNN
	1    7550 4100
	1    0    0    -1  
$EndComp
Text GLabel 7350 2300 0    50   Input ~ 0
BTN_DP_UP
Text GLabel 7350 2900 0    50   Input ~ 0
BTN_DP_DOWN
Text GLabel 7350 3500 0    50   Input ~ 0
BTN_DP_LEFT
Text GLabel 7350 4100 0    50   Input ~ 0
BTN_DP_RIGHT
Text GLabel 2250 2200 0    50   Input ~ 0
BTN_DP_UP
Text GLabel 2250 2300 0    50   Input ~ 0
BTN_DP_DOWN
Text GLabel 2250 2400 0    50   Input ~ 0
BTN_DP_LEFT
Text GLabel 2250 2700 0    50   Input ~ 0
BTN_DP_RIGHT
Text Notes 7900 1850 0    50   ~ 0
BUTTONS ’N
NoConn ~ 2250 1300
NoConn ~ 2250 1400
NoConn ~ 2250 1500
NoConn ~ 2250 1600
NoConn ~ 3850 1500
NoConn ~ 3850 1600
NoConn ~ 3850 1700
NoConn ~ 3850 2200
NoConn ~ 3850 2600
NoConn ~ 2250 2800
NoConn ~ 2250 2900
NoConn ~ 2250 3000
NoConn ~ 3850 2900
NoConn ~ 3850 3000
NoConn ~ 3850 3100
$Comp
L spelkonsoll-rescue:GND-power #PWR07
U 1 1 61FCBFD5
P 3950 1900
F 0 "#PWR07" H 3950 1650 50  0001 C CNN
F 1 "GND" V 3955 1772 50  0000 R CNN
F 2 "" H 3950 1900 50  0001 C CNN
F 3 "" H 3950 1900 50  0001 C CNN
	1    3950 1900
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3950 1900 3850 1900
$Comp
L spelkonsoll-rescue:+5V-power #PWR01
U 1 1 620FF538
P 1650 4950
F 0 "#PWR01" H 1650 4800 50  0001 C CNN
F 1 "+5V" V 1665 5078 50  0000 L CNN
F 2 "" H 1650 4950 50  0001 C CNN
F 3 "" H 1650 4950 50  0001 C CNN
	1    1650 4950
	0    -1   -1   0   
$EndComp
$Comp
L spelkonsoll-rescue:+5V-power #PWR03
U 1 1 61F52AEC
P 1650 5650
F 0 "#PWR03" H 1650 5500 50  0001 C CNN
F 1 "+5V" V 1665 5778 50  0000 L CNN
F 2 "" H 1650 5650 50  0001 C CNN
F 3 "" H 1650 5650 50  0001 C CNN
	1    1650 5650
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1750 5650 1650 5650
$Comp
L spelkonsoll-rescue:GND-power #PWR02
U 1 1 61F5AB18
P 1650 5550
F 0 "#PWR02" H 1650 5300 50  0001 C CNN
F 1 "GND" V 1655 5422 50  0000 R CNN
F 2 "" H 1650 5550 50  0001 C CNN
F 3 "" H 1650 5550 50  0001 C CNN
	1    1650 5550
	0    1    1    0   
$EndComp
Wire Wire Line
	1650 5550 1750 5550
$Comp
L spelkonsoll-rescue:GND-power #PWR04
U 1 1 61F59FD0
P 2150 2600
F 0 "#PWR04" H 2150 2350 50  0001 C CNN
F 1 "GND" V 2155 2472 50  0000 R CNN
F 2 "" H 2150 2600 50  0001 C CNN
F 3 "" H 2150 2600 50  0001 C CNN
	1    2150 2600
	0    1    1    0   
$EndComp
Wire Wire Line
	2150 2600 2250 2600
Wire Wire Line
	9050 4100 8950 4100
Wire Wire Line
	8950 3500 9050 3500
Wire Wire Line
	9050 2300 8950 2300
Wire Wire Line
	7750 3500 7850 3500
Wire Wire Line
	7850 2900 7750 2900
Wire Wire Line
	7750 2300 7850 2300
Wire Wire Line
	8950 2900 9050 2900
Wire Wire Line
	7850 4100 7750 4100
Wire Wire Line
	1650 4950 1750 4950
$Comp
L spelkonsoll-rescue:+5V-power #PWR013
U 1 1 6233968B
P 7850 2300
F 0 "#PWR013" H 7850 2150 50  0001 C CNN
F 1 "+5V" V 7865 2428 50  0000 L CNN
F 2 "" H 7850 2300 50  0001 C CNN
F 3 "" H 7850 2300 50  0001 C CNN
	1    7850 2300
	0    1    1    0   
$EndComp
$Comp
L spelkonsoll-rescue:+5V-power #PWR014
U 1 1 6233E20C
P 7850 2900
F 0 "#PWR014" H 7850 2750 50  0001 C CNN
F 1 "+5V" V 7865 3028 50  0000 L CNN
F 2 "" H 7850 2900 50  0001 C CNN
F 3 "" H 7850 2900 50  0001 C CNN
	1    7850 2900
	0    1    1    0   
$EndComp
$Comp
L spelkonsoll-rescue:+5V-power #PWR015
U 1 1 6233E43F
P 7850 3500
F 0 "#PWR015" H 7850 3350 50  0001 C CNN
F 1 "+5V" V 7865 3628 50  0000 L CNN
F 2 "" H 7850 3500 50  0001 C CNN
F 3 "" H 7850 3500 50  0001 C CNN
	1    7850 3500
	0    1    1    0   
$EndComp
$Comp
L spelkonsoll-rescue:+5V-power #PWR016
U 1 1 6233E66E
P 7850 4100
F 0 "#PWR016" H 7850 3950 50  0001 C CNN
F 1 "+5V" V 7865 4228 50  0000 L CNN
F 2 "" H 7850 4100 50  0001 C CNN
F 3 "" H 7850 4100 50  0001 C CNN
	1    7850 4100
	0    1    1    0   
$EndComp
$Comp
L spelkonsoll-rescue:+5V-power #PWR024
U 1 1 6233E91E
P 9050 4100
F 0 "#PWR024" H 9050 3950 50  0001 C CNN
F 1 "+5V" V 9065 4228 50  0000 L CNN
F 2 "" H 9050 4100 50  0001 C CNN
F 3 "" H 9050 4100 50  0001 C CNN
	1    9050 4100
	0    1    1    0   
$EndComp
$Comp
L spelkonsoll-rescue:+5V-power #PWR023
U 1 1 6233ECD0
P 9050 3500
F 0 "#PWR023" H 9050 3350 50  0001 C CNN
F 1 "+5V" V 9065 3628 50  0000 L CNN
F 2 "" H 9050 3500 50  0001 C CNN
F 3 "" H 9050 3500 50  0001 C CNN
	1    9050 3500
	0    1    1    0   
$EndComp
$Comp
L spelkonsoll-rescue:+5V-power #PWR022
U 1 1 6233EF03
P 9050 2900
F 0 "#PWR022" H 9050 2750 50  0001 C CNN
F 1 "+5V" V 9065 3028 50  0000 L CNN
F 2 "" H 9050 2900 50  0001 C CNN
F 3 "" H 9050 2900 50  0001 C CNN
	1    9050 2900
	0    1    1    0   
$EndComp
$Comp
L spelkonsoll-rescue:+5V-power #PWR021
U 1 1 6233F162
P 9050 2300
F 0 "#PWR021" H 9050 2150 50  0001 C CNN
F 1 "+5V" V 9065 2428 50  0000 L CNN
F 2 "" H 9050 2300 50  0001 C CNN
F 3 "" H 9050 2300 50  0001 C CNN
	1    9050 2300
	0    1    1    0   
$EndComp
$Comp
L spelkonsoll-rescue:GND-power #PWR012
U 1 1 623A8B1C
P 7350 4250
F 0 "#PWR012" H 7350 4000 50  0001 C CNN
F 1 "GND" V 7355 4122 50  0000 R CNN
F 2 "" H 7350 4250 50  0001 C CNN
F 3 "" H 7350 4250 50  0001 C CNN
	1    7350 4250
	0    1    1    0   
$EndComp
Wire Wire Line
	7750 4100 7750 4250
Connection ~ 7750 4100
Wire Wire Line
	7450 4250 7350 4250
Wire Wire Line
	8950 3650 8950 3500
Connection ~ 8950 3500
$Comp
L spelkonsoll-rescue:GND-power #PWR019
U 1 1 623F3731
P 8550 3650
F 0 "#PWR019" H 8550 3400 50  0001 C CNN
F 1 "GND" V 8555 3522 50  0000 R CNN
F 2 "" H 8550 3650 50  0001 C CNN
F 3 "" H 8550 3650 50  0001 C CNN
	1    8550 3650
	0    1    1    0   
$EndComp
Wire Wire Line
	8550 3650 8650 3650
Wire Wire Line
	7750 3650 7750 3500
Connection ~ 7750 3500
$Comp
L spelkonsoll-rescue:GND-power #PWR011
U 1 1 623FAAD8
P 7350 3650
F 0 "#PWR011" H 7350 3400 50  0001 C CNN
F 1 "GND" V 7355 3522 50  0000 R CNN
F 2 "" H 7350 3650 50  0001 C CNN
F 3 "" H 7350 3650 50  0001 C CNN
	1    7350 3650
	0    1    1    0   
$EndComp
Wire Wire Line
	7350 3650 7450 3650
$Comp
L spelkonsoll-rescue:R-Device R4
U 1 1 623FF6EB
P 7600 4250
F 0 "R4" V 7500 4250 50  0000 C CNN
F 1 "10K" V 7600 4250 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 7530 4250 50  0001 C CNN
F 3 "~" H 7600 4250 50  0001 C CNN
	1    7600 4250
	0    1    1    0   
$EndComp
$Comp
L spelkonsoll-rescue:R-Device R3
U 1 1 6240010B
P 7600 3650
F 0 "R3" V 7500 3650 50  0000 C CNN
F 1 "10K" V 7600 3650 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 7530 3650 50  0001 C CNN
F 3 "~" H 7600 3650 50  0001 C CNN
	1    7600 3650
	0    1    1    0   
$EndComp
$Comp
L spelkonsoll-rescue:R-Device R7
U 1 1 62400357
P 8800 3650
F 0 "R7" V 8700 3650 50  0000 C CNN
F 1 "10K" V 8800 3650 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 8730 3650 50  0001 C CNN
F 3 "~" H 8800 3650 50  0001 C CNN
	1    8800 3650
	0    1    1    0   
$EndComp
$Comp
L spelkonsoll-rescue:R-Device R8
U 1 1 624006AD
P 8800 4250
F 0 "R8" V 8700 4250 50  0000 C CNN
F 1 "10K" V 8800 4250 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 8730 4250 50  0001 C CNN
F 3 "~" H 8800 4250 50  0001 C CNN
	1    8800 4250
	0    1    1    0   
$EndComp
Wire Wire Line
	8950 4250 8950 4100
Connection ~ 8950 4100
$Comp
L spelkonsoll-rescue:GND-power #PWR020
U 1 1 62401C76
P 8550 4250
F 0 "#PWR020" H 8550 4000 50  0001 C CNN
F 1 "GND" V 8555 4122 50  0000 R CNN
F 2 "" H 8550 4250 50  0001 C CNN
F 3 "" H 8550 4250 50  0001 C CNN
	1    8550 4250
	0    1    1    0   
$EndComp
Wire Wire Line
	8550 4250 8650 4250
$Comp
L spelkonsoll-rescue:R-Device R2
U 1 1 6247A9BD
P 7600 3050
F 0 "R2" V 7500 3050 50  0000 C CNN
F 1 "10K" V 7600 3050 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 7530 3050 50  0001 C CNN
F 3 "~" H 7600 3050 50  0001 C CNN
	1    7600 3050
	0    1    1    0   
$EndComp
$Comp
L spelkonsoll-rescue:R-Device R1
U 1 1 6247AD48
P 7600 2450
F 0 "R1" V 7500 2450 50  0000 C CNN
F 1 "10K" V 7600 2450 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 7530 2450 50  0001 C CNN
F 3 "~" H 7600 2450 50  0001 C CNN
	1    7600 2450
	0    1    1    0   
$EndComp
$Comp
L spelkonsoll-rescue:R-Device R5
U 1 1 6247B07B
P 8800 2450
F 0 "R5" V 8700 2450 50  0000 C CNN
F 1 "10K" V 8800 2450 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 8730 2450 50  0001 C CNN
F 3 "~" H 8800 2450 50  0001 C CNN
	1    8800 2450
	0    1    1    0   
$EndComp
$Comp
L spelkonsoll-rescue:R-Device R6
U 1 1 6247B486
P 8800 3050
F 0 "R6" V 8700 3050 50  0000 C CNN
F 1 "10K" V 8800 3050 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 8730 3050 50  0001 C CNN
F 3 "~" H 8800 3050 50  0001 C CNN
	1    8800 3050
	0    1    1    0   
$EndComp
Wire Wire Line
	8950 3050 8950 2900
Connection ~ 8950 2900
Wire Wire Line
	8950 2450 8950 2300
Connection ~ 8950 2300
Wire Wire Line
	7750 2300 7750 2450
Connection ~ 7750 2300
Wire Wire Line
	7750 2900 7750 3050
Connection ~ 7750 2900
$Comp
L spelkonsoll-rescue:GND-power #PWR010
U 1 1 624800B4
P 7350 3050
F 0 "#PWR010" H 7350 2800 50  0001 C CNN
F 1 "GND" V 7355 2922 50  0000 R CNN
F 2 "" H 7350 3050 50  0001 C CNN
F 3 "" H 7350 3050 50  0001 C CNN
	1    7350 3050
	0    1    1    0   
$EndComp
$Comp
L spelkonsoll-rescue:GND-power #PWR09
U 1 1 624803D7
P 7350 2450
F 0 "#PWR09" H 7350 2200 50  0001 C CNN
F 1 "GND" V 7355 2322 50  0000 R CNN
F 2 "" H 7350 2450 50  0001 C CNN
F 3 "" H 7350 2450 50  0001 C CNN
	1    7350 2450
	0    1    1    0   
$EndComp
$Comp
L spelkonsoll-rescue:GND-power #PWR017
U 1 1 624806FE
P 8550 2450
F 0 "#PWR017" H 8550 2200 50  0001 C CNN
F 1 "GND" V 8555 2322 50  0000 R CNN
F 2 "" H 8550 2450 50  0001 C CNN
F 3 "" H 8550 2450 50  0001 C CNN
	1    8550 2450
	0    1    1    0   
$EndComp
$Comp
L spelkonsoll-rescue:GND-power #PWR018
U 1 1 62480AF9
P 8550 3050
F 0 "#PWR018" H 8550 2800 50  0001 C CNN
F 1 "GND" V 8555 2922 50  0000 R CNN
F 2 "" H 8550 3050 50  0001 C CNN
F 3 "" H 8550 3050 50  0001 C CNN
	1    8550 3050
	0    1    1    0   
$EndComp
Wire Wire Line
	8550 3050 8650 3050
Wire Wire Line
	8650 2450 8550 2450
Wire Wire Line
	7450 2450 7350 2450
Wire Wire Line
	7350 3050 7450 3050
NoConn ~ 2250 1700
NoConn ~ 2250 1800
NoConn ~ 2250 2500
NoConn ~ 3850 2700
NoConn ~ 3850 2800
$EndSCHEMATC