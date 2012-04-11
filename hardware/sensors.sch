EESchema Schematic File Version 2  date Wed 11 Apr 2012 02:03:40 PM ART
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
Sheet 4 6
Title "Distance Sensors"
Date "11 apr 2012"
Rev "0.3"
Comp "Departamento de Ingeniería Eléctrica y Computadoras, Universidad Nacional del Sur"
Comment1 "Directors: Ricardo Cayssials, Edgardo Ferro"
Comment2 "Authors: Pablo Odorico, Juan Bajo, Marcos Chaparro"
Comment3 ""
Comment4 ""
$EndDescr
Text HLabel 2750 4200 0    60   BiDi ~ 0
SENS_SDA
Text HLabel 2750 4450 0    60   BiDi ~ 0
SENS_SCL
$Comp
L CONN_4 P3
U 1 1 4F85593C
P 5600 4250
F 0 "P3" V 5550 4250 50  0000 C CNN
F 1 "CONN_4" V 5650 4250 50  0000 C CNN
	1    5600 4250
	1    0    0    -1  
$EndComp
Text GLabel 2750 3500 0    60   Input ~ 0
5V
$Comp
L GND #PWR022
U 1 1 4F85598B
P 5000 4600
F 0 "#PWR022" H 5000 4600 30  0001 C CNN
F 1 "GND" H 5000 4530 30  0001 C CNN
	1    5000 4600
	1    0    0    -1  
$EndComp
$Comp
L R R4
U 1 1 4F8559AE
P 3300 3850
F 0 "R4" V 3380 3850 50  0000 C CNN
F 1 "4.7k" V 3300 3850 50  0000 C CNN
	1    3300 3850
	1    0    0    -1  
$EndComp
$Comp
L R R5
U 1 1 4F8559CC
P 3600 3850
F 0 "R5" V 3680 3850 50  0000 C CNN
F 1 "4.7k" V 3600 3850 50  0000 C CNN
	1    3600 3850
	1    0    0    -1  
$EndComp
$Comp
L CONN_4 P99
U 1 1 4F855C9B
P 6300 3300
F 0 "P99" V 6250 3300 50  0000 C CNN
F 1 "CONN_4" V 6350 3300 50  0000 C CNN
	1    6300 3300
	-1   0    0    -1  
$EndComp
$Comp
L SRF02 Sens0
U 1 1 4F855CB4
P 8600 3350
F 0 "Sens0" H 8600 3250 50  0000 C CNN
F 1 "SRF02" H 8600 3450 50  0000 C CNN
F 2 "MODULE" H 8600 3350 50  0001 C CNN
F 3 "DOCUMENTATION" H 8600 3350 50  0001 C CNN
	1    8600 3350
	1    0    0    -1  
$EndComp
$Comp
L SRF02 Sens1
U 1 1 4F855CCD
P 8600 4300
F 0 "Sens1" H 8600 4200 50  0000 C CNN
F 1 "SRF02" H 8600 4400 50  0000 C CNN
F 2 "MODULE" H 8600 4300 50  0001 C CNN
F 3 "DOCUMENTATION" H 8600 4300 50  0001 C CNN
	1    8600 4300
	1    0    0    -1  
$EndComp
$Comp
L SRF02 Sens2
U 1 1 4F855CD3
P 8600 5250
F 0 "Sens2" H 8600 5150 50  0000 C CNN
F 1 "SRF02" H 8600 5350 50  0000 C CNN
F 2 "MODULE" H 8600 5250 50  0001 C CNN
F 3 "DOCUMENTATION" H 8600 5250 50  0001 C CNN
	1    8600 5250
	1    0    0    -1  
$EndComp
NoConn ~ 7850 3450
NoConn ~ 7850 4400
NoConn ~ 7850 5350
Text Notes 3850 3850 0    60   ~ 0
I2C pull-up\nresistors
Text Notes 6200 2650 0    60   ~ 0
This is how the sensors would be connected to the\nI2C bus.
Text Label 5250 4100 2    60   ~ 0
VCC
Text Label 5250 4200 2    60   ~ 0
SDA
Text Label 5250 4300 2    60   ~ 0
SCL
Text Label 5250 4400 2    60   ~ 0
GND
Text Label 6650 3150 0    60   ~ 0
VCC
Text Label 6650 3250 0    60   ~ 0
SDA
Text Label 6650 3350 0    60   ~ 0
SCL
Text Label 6650 3450 0    60   ~ 0
GND
Text Notes 2000 4750 0    60   ~ 0
STM32 pins tolerate\n5V logic levels.
Wire Wire Line
	5000 4100 5250 4100
Wire Wire Line
	5000 3500 5000 4100
Wire Wire Line
	5000 3500 2750 3500
Wire Wire Line
	2750 4200 5250 4200
Wire Wire Line
	4900 4300 5250 4300
Wire Wire Line
	4900 4300 4900 4450
Wire Wire Line
	4900 4450 2750 4450
Wire Wire Line
	5000 4400 5250 4400
Wire Wire Line
	5000 4400 5000 4600
Wire Wire Line
	3300 3600 3300 3500
Connection ~ 3300 3500
Wire Wire Line
	3300 4100 3300 4200
Connection ~ 3300 4200
Wire Wire Line
	7750 3450 7750 3550
Wire Wire Line
	7750 3550 7850 3550
Wire Wire Line
	7550 3150 7550 5050
Wire Wire Line
	7550 4100 7850 4100
Wire Wire Line
	7450 3250 7450 5150
Wire Wire Line
	7450 4200 7850 4200
Wire Wire Line
	7350 3350 7350 5250
Wire Wire Line
	7350 4300 7850 4300
Wire Wire Line
	7250 3450 7250 5350
Wire Wire Line
	7250 4400 7750 4400
Wire Wire Line
	7750 4400 7750 4500
Wire Wire Line
	7750 4500 7850 4500
Wire Wire Line
	7550 5050 7850 5050
Connection ~ 7550 4100
Wire Wire Line
	7450 5150 7850 5150
Connection ~ 7450 4200
Wire Wire Line
	7350 5250 7850 5250
Connection ~ 7350 4300
Wire Wire Line
	7250 5350 7750 5350
Wire Wire Line
	7750 5350 7750 5450
Wire Wire Line
	7750 5450 7850 5450
Connection ~ 7250 4400
Wire Notes Line
	6000 2400 6000 5850
Wire Notes Line
	6000 5850 9250 5850
Wire Notes Line
	9250 5850 9250 2400
Wire Notes Line
	9250 2400 6000 2400
Connection ~ 7550 3150
Connection ~ 7450 3250
Connection ~ 7350 3350
Connection ~ 7250 3450
Wire Wire Line
	7750 3450 6650 3450
Wire Wire Line
	6650 3350 7850 3350
Wire Wire Line
	7850 3250 6650 3250
Wire Wire Line
	6650 3150 7850 3150
Wire Wire Line
	3600 4100 3600 4450
Connection ~ 3600 4450
Wire Wire Line
	3600 3600 3600 3500
Connection ~ 3600 3500
$EndSCHEMATC
