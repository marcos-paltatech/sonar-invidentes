EESchema Schematic File Version 2  date Thu 12 Apr 2012 08:38:20 PM ART
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
LIBS:LD1117xx
EELAYER 25  0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 5 6
Title "Flash Memory"
Date "12 apr 2012"
Rev "0.3"
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
F 4 "W25Q80BVSSIG" H 5900 4050 60  0001 C CNN "mfg#"
	1    5900 4050
	1    0    0    -1  
$EndComp
Text GLabel 4950 4100 0    60   Input ~ 0
3.3V
Text GLabel 7850 3900 2    60   Input ~ 0
3.3V
Text HLabel 6850 4100 2    60   Input ~ 0
MEM_CLK
Text HLabel 6850 4200 2    60   Input ~ 0
MEM_MOSI
Text HLabel 4950 3900 0    60   Input ~ 0
MEM_NCS
Text HLabel 4950 4000 0    60   Output ~ 0
MEM_MISO
$Comp
L GND #PWR023
U 1 1 4F85D530
P 4950 4300
F 0 "#PWR023" H 4950 4300 30  0001 C CNN
F 1 "GND" H 4950 4230 30  0001 C CNN
	1    4950 4300
	1    0    0    -1  
$EndComp
$Comp
L C C22
U 1 1 4F85DDDE
P 7550 4100
F 0 "C22" H 7600 4200 50  0000 L CNN
F 1 "100nF" H 7600 4000 50  0000 L CNN
F 4 "C0603C104K4RACTU" H 7550 4100 60  0001 C CNN "mfg#"
	1    7550 4100
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR024
U 1 1 4F85DE08
P 7550 4300
F 0 "#PWR024" H 7550 4300 30  0001 C CNN
F 1 "GND" H 7550 4230 30  0001 C CNN
	1    7550 4300
	1    0    0    -1  
$EndComp
Wire Wire Line
	5050 4100 4950 4100
Wire Wire Line
	6850 4000 6750 4000
Wire Wire Line
	6750 4100 6850 4100
Wire Wire Line
	6750 4200 6850 4200
Wire Wire Line
	5050 3900 4950 3900
Wire Wire Line
	5050 4000 4950 4000
Wire Wire Line
	5050 4200 4950 4200
Wire Wire Line
	4950 4200 4950 4300
Wire Wire Line
	6750 3900 7850 3900
Wire Wire Line
	6850 4000 6850 3900
Connection ~ 6850 3900
Wire Wire Line
	7550 3900 7550 3900
Connection ~ 7550 3900
Connection ~ 7550 3900
Text Notes 650  800  0    118  ~ 24
Flash Memory
$EndSCHEMATC
