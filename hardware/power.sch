EESchema Schematic File Version 2  date Tue 17 Apr 2012 12:41:08 AM ART
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
Sheet 6 6
Title "Power Supply"
Date "17 apr 2012"
Rev "0.4"
Comp "Departamento de Ingeniería Eléctrica y Computadoras, Universidad Nacional del Sur"
Comment1 "Directors: Ricardo Cayssials, Edgardo Ferro"
Comment2 "Authors: Pablo Odorico, Juan Bajo, Marcos Chaparro"
Comment3 ""
Comment4 ""
$EndDescr
Text Label 4450 4350 0    60   ~ 0
GND
Text Label 4450 3850 0    60   ~ 0
VIN
$Comp
L GND #PWR026
U 1 1 4F854CC3
P 7400 4450
F 0 "#PWR026" H 7400 4450 30  0001 C CNN
F 1 "GND" H 7400 4380 30  0001 C CNN
	1    7400 4450
	1    0    0    -1  
$EndComp
Text GLabel 7400 3850 2    60   Output ~ 0
3.3V
Text GLabel 7400 4850 2    60   Output ~ 0
5V
Text Notes 3050 4650 0    60   ~ 0
LD1117xx50C dropout voltage is:\n  1V @ 100mA\n  1.15V @ 500mA\nVIN should be between 6.15V and 15V.\n\n
Text Notes 5650 5200 0    60   ~ 0
LD1115xx Reference Design
Text Notes 700  850  0    118  ~ 24
Power Supply
$Comp
L C C16
U 1 1 4F8633E1
P 5650 4100
F 0 "C16" H 5700 4200 50  0000 L CNN
F 1 "100nF" H 5700 4000 50  0000 L CNN
F 4 "C0603C104K4RACTU" H 5650 4100 60  0001 C CNN "mfg#"
	1    5650 4100
	1    0    0    -1  
$EndComp
$Comp
L C C17
U 1 1 4F8633EE
P 5650 4600
F 0 "C17" H 5700 4700 50  0000 L CNN
F 1 "100nF" H 5700 4500 50  0000 L CNN
F 4 "C0603C104K4RACTU" H 5650 4600 60  0001 C CNN "mfg#"
	1    5650 4600
	1    0    0    -1  
$EndComp
$Comp
L C C18
U 1 1 4F86342B
P 6850 4100
F 0 "C18" H 6900 4200 50  0000 L CNN
F 1 "10uF" H 6900 4000 50  0000 L CNN
F 4 "JMK212BJ106KD-T" H 6850 4100 60  0001 C CNN "mfg#"
	1    6850 4100
	1    0    0    -1  
$EndComp
$Comp
L C C19
U 1 1 4F863432
P 6850 4600
F 0 "C19" H 6900 4700 50  0000 L CNN
F 1 "10uF" H 6900 4500 50  0000 L CNN
F 4 "JMK212BJ106KD-T" H 6850 4600 60  0001 C CNN "mfg#"
	1    6850 4600
	1    0    0    -1  
$EndComp
$Comp
L LD1117 U4
U 1 1 4F8766D2
P 6250 3900
F 0 "U4" H 6400 3704 60  0000 C CNN
F 1 "LD1117DT33C" H 6250 4100 60  0000 C CNN
F 4 "LD1117DT33CTR" H 6250 3900 60  0001 C CNN "mfg#"
	1    6250 3900
	1    0    0    -1  
$EndComp
$Comp
L LD1117 U5
U 1 1 4F8766F3
P 6250 4800
F 0 "U5" H 6400 4604 60  0000 C CNN
F 1 "LD1117DT50C" H 6250 5000 60  0000 C CNN
F 4 "LD1117DT50CTR" H 6250 4800 60  0001 C CNN "mfg#"
	1    6250 4800
	1    0    0    1   
$EndComp
$Comp
L BATTERY BT1
U 1 1 4F8A825D
P 4000 4100
F 0 "BT1" H 4000 4300 50  0000 C CNN
F 1 "BATTERY" H 4000 3910 50  0000 C CNN
F 3 "Keystone 1294" H 4000 4100 60  0001 C CNN
F 4 "534-1294" H 4000 4100 60  0001 C CNN "mfg#"
	1    4000 4100
	0    1    1    0   
$EndComp
$Comp
L R R11
U 1 1 4F8B1AC0
P 4550 3100
F 0 "R11" V 4630 3100 50  0000 C CNN
F 1 "499K" V 4550 3100 50  0000 C CNN
F 4 "ERJ-3EKF4993V" H 4550 3100 60  0001 C CNN "mfg#"
	1    4550 3100
	0    -1   -1   0   
$EndComp
$Comp
L R R12
U 1 1 4F8B1ACD
P 5250 3100
F 0 "R12" V 5330 3100 50  0000 C CNN
F 1 "100k" V 5250 3100 50  0000 C CNN
F 4 "ERJ-3EKF1003V" H 5250 3100 60  0001 C CNN "mfg#"
	1    5250 3100
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR027
U 1 1 4F8B1B1A
P 5600 3200
F 0 "#PWR027" H 5600 3200 30  0001 C CNN
F 1 "GND" H 5600 3130 30  0001 C CNN
	1    5600 3200
	1    0    0    -1  
$EndComp
Text HLabel 4900 2900 1    60   Input ~ 0
BATT_LEVEL
$Comp
L C C25
U 1 1 4F8B1C07
P 4900 3400
F 0 "C25" H 4950 3500 50  0000 L CNN
F 1 "100nF" H 4950 3300 50  0000 L CNN
F 4 "C0603C104K4RACTU" H 4900 3400 60  0001 C CNN "mfg#"
	1    4900 3400
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR028
U 1 1 4F8B1C16
P 4900 3600
F 0 "#PWR028" H 4900 3600 30  0001 C CNN
F 1 "GND" H 4900 3530 30  0001 C CNN
	1    4900 3600
	1    0    0    -1  
$EndComp
Wire Wire Line
	4150 3850 5850 3850
Wire Wire Line
	5050 4850 5850 4850
Wire Wire Line
	6250 4150 6250 4550
Connection ~ 6250 4350
Wire Wire Line
	4150 4350 7400 4350
Wire Wire Line
	5650 3900 5650 3850
Connection ~ 5650 3850
Connection ~ 5650 4350
Wire Wire Line
	5650 4850 5650 4800
Connection ~ 5650 4850
Connection ~ 5650 4850
Wire Wire Line
	6850 4300 6850 4400
Connection ~ 6850 4350
Connection ~ 6850 4350
Wire Wire Line
	6650 4850 7400 4850
Wire Wire Line
	6850 4850 6850 4800
Wire Wire Line
	6850 3900 6850 3850
Wire Wire Line
	6650 3850 7400 3850
Wire Wire Line
	7400 4350 7400 4450
Wire Wire Line
	5050 4850 5050 3850
Connection ~ 5050 3850
Connection ~ 6850 3850
Connection ~ 6850 3850
Connection ~ 6850 4850
Connection ~ 6850 4850
Wire Wire Line
	5650 4300 5650 4400
Wire Wire Line
	4150 3100 4150 3850
Wire Wire Line
	4150 3800 4000 3800
Wire Wire Line
	4150 4350 4150 4400
Wire Wire Line
	4150 4400 4000 4400
Wire Wire Line
	4150 3100 4300 3100
Connection ~ 4150 3800
Wire Wire Line
	5500 3100 5600 3100
Wire Wire Line
	5600 3100 5600 3200
Wire Wire Line
	4800 3100 5000 3100
Connection ~ 4900 3100
Connection ~ 4900 3100
Wire Wire Line
	4900 2900 4900 3200
Text Notes 5150 2700 0    60   ~ 0
1:5 voltage divider to measure battery level.\n  15V will map to 3V\n  9V will map to 1.8V
$EndSCHEMATC
