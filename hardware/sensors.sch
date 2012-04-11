EESchema Schematic File Version 2  date Tue 10 Apr 2012 10:24:32 PM ART
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
Rev "0.1"
Comp "Departamento de Ingeniería Eléctrica y Computadoras, Universidad Nacional del Sur"
Comment1 "Directors: Ricardo Cayssials, Edgardo Ferro"
Comment2 "Authors: Pablo Odorico, Juan Bajo, Marcos Chaparro"
Comment3 ""
Comment4 ""
$EndDescr
Text HLabel 2750 3550 0    60   BiDi ~ 0
SENS_SDA
Text HLabel 2750 3800 0    60   BiDi ~ 0
SENS_SCL
$Comp
L CONN_4 P3
U 1 1 4F85593C
P 5450 3600
F 0 "P3" V 5400 3600 50  0000 C CNN
F 1 "SENS_SPI" V 5500 3600 50  0000 C CNN
	1    5450 3600
	1    0    0    -1  
$EndComp
Text GLabel 2750 2850 0    60   Input ~ 0
5V
$Comp
L GND #PWR?
U 1 1 4F85598B
P 5000 3950
F 0 "#PWR?" H 5000 3950 30  0001 C CNN
F 1 "GND" H 5000 3880 30  0001 C CNN
	1    5000 3950
	1    0    0    -1  
$EndComp
$Comp
L R R4
U 1 1 4F8559AE
P 3300 3200
F 0 "R4" V 3380 3200 50  0000 C CNN
F 1 "4.7k" V 3300 3200 50  0000 C CNN
	1    3300 3200
	1    0    0    -1  
$EndComp
$Comp
L R R5
U 1 1 4F8559CC
P 3800 3200
F 0 "R5" V 3880 3200 50  0000 C CNN
F 1 "4.7k" V 3800 3200 50  0000 C CNN
	1    3800 3200
	1    0    0    -1  
$EndComp
$Comp
L CONN_4 P99
U 1 1 4F855C9B
P 6300 3600
F 0 "P99" V 6250 3600 50  0000 C CNN
F 1 "CONN_4" V 6350 3600 50  0000 C CNN
	1    6300 3600
	-1   0    0    -1  
$EndComp
$Comp
L SRF02 Sens0
U 1 1 4F855CB4
P 8600 3650
F 0 "Sens0" H 8600 3550 50  0000 C CNN
F 1 "SRF02" H 8600 3750 50  0000 C CNN
F 2 "MODULE" H 8600 3650 50  0001 C CNN
F 3 "DOCUMENTATION" H 8600 3650 50  0001 C CNN
	1    8600 3650
	1    0    0    -1  
$EndComp
$Comp
L SRF02 Sens1
U 1 1 4F855CCD
P 8600 4600
F 0 "Sens1" H 8600 4500 50  0000 C CNN
F 1 "SRF02" H 8600 4700 50  0000 C CNN
F 2 "MODULE" H 8600 4600 50  0001 C CNN
F 3 "DOCUMENTATION" H 8600 4600 50  0001 C CNN
	1    8600 4600
	1    0    0    -1  
$EndComp
$Comp
L SRF02 Sens2
U 1 1 4F855CD3
P 8600 5550
F 0 "Sens2" H 8600 5450 50  0000 C CNN
F 1 "SRF02" H 8600 5650 50  0000 C CNN
F 2 "MODULE" H 8600 5550 50  0001 C CNN
F 3 "DOCUMENTATION" H 8600 5550 50  0001 C CNN
	1    8600 5550
	1    0    0    -1  
$EndComp
NoConn ~ 7850 3750
NoConn ~ 7850 4700
NoConn ~ 7850 5650
Text Notes 4050 3150 0    60   ~ 0
I2C Pull-up\nresistors.
Text Notes 6200 2950 0    60   ~ 0
This is how the sensors would be connected to the\nI2C bus.
Wire Wire Line
	5000 3450 5100 3450
Wire Wire Line
	5000 2850 5000 3450
Wire Wire Line
	5000 2850 2750 2850
Wire Wire Line
	2750 3550 5100 3550
Wire Wire Line
	4900 3650 5100 3650
Wire Wire Line
	4900 3650 4900 3800
Wire Wire Line
	4900 3800 2750 3800
Wire Wire Line
	5100 3750 5000 3750
Wire Wire Line
	5000 3750 5000 3950
Wire Wire Line
	3300 2950 3300 2850
Connection ~ 3300 2850
Wire Wire Line
	3300 3450 3300 3550
Connection ~ 3300 3550
Wire Wire Line
	3800 2950 3800 2850
Connection ~ 3800 2850
Wire Wire Line
	3800 3450 3800 3800
Connection ~ 3800 3800
Wire Wire Line
	7750 3750 7750 3850
Wire Wire Line
	7750 3850 7850 3850
Wire Wire Line
	7550 3450 7550 5350
Wire Wire Line
	7550 4400 7850 4400
Wire Wire Line
	7450 3550 7450 5450
Wire Wire Line
	7450 4500 7850 4500
Wire Wire Line
	7350 3650 7350 5550
Wire Wire Line
	7350 4600 7850 4600
Wire Wire Line
	7250 3750 7250 5650
Wire Wire Line
	7250 4700 7750 4700
Wire Wire Line
	7750 4700 7750 4800
Wire Wire Line
	7750 4800 7850 4800
Wire Wire Line
	7550 5350 7850 5350
Connection ~ 7550 4400
Wire Wire Line
	7450 5450 7850 5450
Connection ~ 7450 4500
Wire Wire Line
	7350 5550 7850 5550
Connection ~ 7350 4600
Wire Wire Line
	7250 5650 7750 5650
Wire Wire Line
	7750 5650 7750 5750
Wire Wire Line
	7750 5750 7850 5750
Connection ~ 7250 4700
Wire Notes Line
	6000 2700 6000 6150
Wire Notes Line
	6000 6150 9250 6150
Wire Notes Line
	9250 6150 9250 2700
Wire Notes Line
	9250 2700 6000 2700
Connection ~ 7550 3450
Connection ~ 7450 3550
Connection ~ 7350 3650
Connection ~ 7250 3750
Wire Wire Line
	7750 3750 6650 3750
Wire Wire Line
	6650 3650 7850 3650
Wire Wire Line
	7850 3550 6650 3550
Wire Wire Line
	6650 3450 7850 3450
$EndSCHEMATC
