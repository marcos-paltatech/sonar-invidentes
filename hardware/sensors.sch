EESchema Schematic File Version 2  date Sun 15 Apr 2012 04:55:50 PM ART
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
LIBS:sonar_board-cache
EELAYER 25  0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 4 6
Title "Distance Sensors"
Date "15 apr 2012"
Rev "0.4"
Comp "Departamento de Ingeniería Eléctrica y Computadoras, Universidad Nacional del Sur"
Comment1 "Directors: Ricardo Cayssials, Edgardo Ferro"
Comment2 "Authors: Pablo Odorico, Juan Bajo, Marcos Chaparro"
Comment3 ""
Comment4 ""
$EndDescr
Text HLabel 2550 3300 0    60   BiDi ~ 0
SENS_SDA
Text HLabel 2550 3550 0    60   BiDi ~ 0
SENS_SCL
Text GLabel 2550 2600 0    60   Input ~ 0
5V
$Comp
L GND #PWR022
U 1 1 4F85598B
P 5350 3700
F 0 "#PWR022" H 5350 3700 30  0001 C CNN
F 1 "GND" H 5350 3630 30  0001 C CNN
	1    5350 3700
	1    0    0    -1  
$EndComp
$Comp
L R R4
U 1 1 4F8559AE
P 3100 2950
F 0 "R4" V 3180 2950 50  0000 C CNN
F 1 "4.7k" V 3100 2950 50  0000 C CNN
F 4 "ERJ-3EKF4701V" H 3100 2950 60  0001 C CNN "mfg#"
	1    3100 2950
	1    0    0    -1  
$EndComp
$Comp
L R R5
U 1 1 4F8559CC
P 3400 2950
F 0 "R5" V 3480 2950 50  0000 C CNN
F 1 "4.7k" V 3400 2950 50  0000 C CNN
F 4 "ERJ-3EKF4701V" H 3400 2950 60  0001 C CNN "mfg#"
	1    3400 2950
	1    0    0    -1  
$EndComp
Text Notes 3650 2950 0    60   ~ 0
I2C pull-up\nresistors
Text Label 5900 3200 2    60   ~ 0
5V
Text Label 5900 3300 2    60   ~ 0
SDA
Text Label 5900 3400 2    60   ~ 0
SCL
Text Label 5900 3500 2    60   ~ 0
GND
Text Notes 1800 3850 0    60   ~ 0
STM32 pins tolerate\n5V logic levels.
Text Notes 700  850  0    118  ~ 24
Sensors
$Comp
L SRF02 S1
U 1 1 4F8A2BAD
P 7950 3400
F 0 "S1" H 7950 3300 50  0000 C CNN
F 1 "SRF02" H 7950 3500 50  0000 C CNN
F 2 "MODULE" H 7950 3400 50  0001 C CNN
F 3 "DOCUMENTATION" H 7950 3400 50  0001 C CNN
F 4 "77315-113-04LF" H 7950 3400 60  0001 C CNN "mfg#"
	1    7950 3400
	1    0    0    -1  
$EndComp
$Comp
L SRF02 S2
U 1 1 4F8A2BBC
P 7950 4300
F 0 "S2" H 7950 4200 50  0000 C CNN
F 1 "SRF02" H 7950 4400 50  0000 C CNN
F 2 "MODULE" H 7950 4300 50  0001 C CNN
F 3 "DOCUMENTATION" H 7950 4300 50  0001 C CNN
F 4 "77315-113-04LF" H 7950 4300 60  0001 C CNN "mfg#"
	1    7950 4300
	1    0    0    -1  
$EndComp
$Comp
L SRF02 S3
U 1 1 4F8A2BCB
P 7950 5250
F 0 "S3" H 7950 5150 50  0000 C CNN
F 1 "SRF02" H 7950 5350 50  0000 C CNN
F 2 "MODULE" H 7950 5250 50  0001 C CNN
F 3 "DOCUMENTATION" H 7950 5250 50  0001 C CNN
F 4 "77315-113-04LF" H 7950 5250 60  0001 C CNN "mfg#"
	1    7950 5250
	1    0    0    -1  
$EndComp
NoConn ~ 7200 3500
NoConn ~ 7200 4400
NoConn ~ 7200 5350
Text Notes 5850 2650 0    60   ~ 0
Sensors connected to the I2C bus.
Text GLabel 8750 900  0    60   Input ~ 0
5V
$Comp
L C C12
U 1 1 4F8A3DA0
P 9100 1100
F 0 "C12" H 9150 1200 50  0000 L CNN
F 1 "10uF" H 9150 1000 50  0000 L CNN
F 4 "C0603C104K4RACTU" H 9100 1100 60  0001 C CNN "mfg#"
	1    9100 1100
	1    0    0    -1  
$EndComp
$Comp
L C C23
U 1 1 4F8A3DA7
P 9400 1100
F 0 "C23" H 9450 1200 50  0000 L CNN
F 1 "10uF" H 9450 1000 50  0000 L CNN
F 4 "C0603C104K4RACTU" H 9400 1100 60  0001 C CNN "mfg#"
	1    9400 1100
	1    0    0    -1  
$EndComp
$Comp
L C C24
U 1 1 4F8A3DAE
P 9700 1100
F 0 "C24" H 9750 1200 50  0000 L CNN
F 1 "10uF" H 9750 1000 50  0000 L CNN
F 4 "C0603C104K4RACTU" H 9700 1100 60  0001 C CNN "mfg#"
	1    9700 1100
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR023
U 1 1 4F8A3DC2
P 8750 1400
F 0 "#PWR023" H 8750 1400 30  0001 C CNN
F 1 "GND" H 8750 1330 30  0001 C CNN
	1    8750 1400
	1    0    0    -1  
$EndComp
Text Notes 9100 1500 0    60   ~ 0
Capacitors to be placed near VDD's
Wire Wire Line
	4800 3200 7200 3200
Wire Wire Line
	4800 2600 4800 3200
Wire Wire Line
	4800 2600 2550 2600
Wire Wire Line
	2550 3300 7200 3300
Wire Wire Line
	4700 3400 7200 3400
Wire Wire Line
	4700 3400 4700 3550
Wire Wire Line
	4700 3550 2550 3550
Wire Wire Line
	5350 3500 5350 3700
Wire Wire Line
	3100 2700 3100 2600
Connection ~ 3100 2600
Wire Wire Line
	3100 3200 3100 3300
Connection ~ 3100 3300
Wire Notes Line
	5650 2400 5650 5850
Wire Notes Line
	5650 5850 8900 5850
Wire Notes Line
	8900 5850 8900 2400
Wire Notes Line
	8900 2400 5650 2400
Wire Wire Line
	3400 3200 3400 3550
Connection ~ 3400 3550
Wire Wire Line
	3400 2700 3400 2600
Connection ~ 3400 2600
Wire Wire Line
	5350 3500 7100 3500
Wire Wire Line
	8750 1300 8750 1400
Wire Wire Line
	9100 900  9100 900 
Wire Wire Line
	9100 1300 9100 1300
Wire Wire Line
	9400 1300 9400 1300
Wire Wire Line
	9400 900  9400 900 
Wire Wire Line
	8750 900  9700 900 
Wire Wire Line
	8750 1300 9700 1300
Connection ~ 9400 900 
Connection ~ 9400 900 
Connection ~ 9100 900 
Connection ~ 9100 900 
Connection ~ 9100 1300
Connection ~ 9100 1300
Connection ~ 9400 1300
Connection ~ 9400 1300
Wire Wire Line
	7000 5050 7200 5050
Wire Wire Line
	7000 5050 7000 3200
Connection ~ 7000 3200
Wire Wire Line
	7100 3500 7100 3600
Wire Wire Line
	7100 3600 7200 3600
Wire Wire Line
	7200 5150 6900 5150
Wire Wire Line
	6900 5150 6900 3300
Connection ~ 6900 3300
Wire Wire Line
	7200 5250 6800 5250
Wire Wire Line
	6800 5250 6800 3400
Connection ~ 6800 3400
Wire Wire Line
	7200 5450 7100 5450
Wire Wire Line
	7100 5450 7100 5350
Wire Wire Line
	7100 5350 6700 5350
Wire Wire Line
	6700 5350 6700 3500
Connection ~ 6700 3500
Wire Wire Line
	7200 4500 7100 4500
Wire Wire Line
	7100 4500 7100 4400
Wire Wire Line
	7100 4400 6700 4400
Connection ~ 6700 4400
Wire Wire Line
	6800 4300 7200 4300
Connection ~ 6800 4300
Wire Wire Line
	7200 4200 6900 4200
Connection ~ 6900 4200
Wire Wire Line
	7200 4100 7000 4100
Connection ~ 7000 4100
$EndSCHEMATC
