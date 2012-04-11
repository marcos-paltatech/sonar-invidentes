EESchema Schematic File Version 2  date Wed 11 Apr 2012 03:48:29 AM ART
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:special
LIBS:analog_switches
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:opto
LIBS:BTM511
LIBS:SRF02
LIBS:W25Q80BV
LIBS:STM32F100RBT6B
LIBS:sonar_board-cache
EELAYER 25  0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 5 6
Title "Flash Memory"
Date "11 apr 2012"
Rev "0.1"
Comp "Departamento de Ingeniería Eléctrica y Computadoras, Universidad Nacional del Sur"
Comment1 "Directors: Ricardo Cayssials, Edgardo Ferro"
Comment2 "Authors: Pablo Odorico, Juan Bajo, Marcos Chaparro"
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L W25Q80BV U3
U 1 1 4F84D20F
P 5900 4050
F 0 "U3" H 5900 3950 50  0000 C CNN
F 1 "W25Q80BV" H 5900 4150 50  0000 C CNN
F 2 "MODULE" H 5900 4050 50  0001 C CNN
F 3 "DOCUMENTATION" H 5900 4050 50  0001 C CNN
	1    5900 4050
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR023
U 1 1 4F84D228
P 4950 4350
F 0 "#PWR023" H 4950 4350 30  0001 C CNN
F 1 "GND" H 4950 4280 30  0001 C CNN
	1    4950 4350
	1    0    0    -1  
$EndComp
Text GLabel 4950 4100 0    60   Input ~ 0
3.3V
Text GLabel 6950 3900 2    60   Input ~ 0
3.3V
Wire Wire Line
	5050 4200 4950 4200
Wire Wire Line
	4950 4200 4950 4350
Wire Wire Line
	5050 4100 4950 4100
Wire Wire Line
	6850 4000 6750 4000
Wire Wire Line
	6750 3900 6950 3900
Wire Wire Line
	6850 4000 6850 3900
Connection ~ 6850 3900
Connection ~ 6850 3900
Wire Wire Line
	6750 4100 6850 4100
Wire Wire Line
	6750 4200 6850 4200
Wire Wire Line
	5050 3900 4950 3900
Wire Wire Line
	5050 4000 4950 4000
Text HLabel 6850 4100 2    60   Input ~ 0
MEM_CLK
Text HLabel 6850 4200 2    60   Input ~ 0
MEM_MOSI
Text HLabel 4950 3900 0    60   Input ~ 0
MEM_NCS
Text HLabel 4950 4000 0    60   Output ~ 0
MEM_MISO
$EndSCHEMATC
