EESchema Schematic File Version 2  date Thu 12 Apr 2012 01:54:54 AM ART
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
Sheet 6 6
Title "Power Supply"
Date "12 apr 2012"
Rev "0.3"
Comp "Departamento de Ingeniería Eléctrica y Computadoras, Universidad Nacional del Sur"
Comment1 "Directors: Ricardo Cayssials, Edgardo Ferro"
Comment2 "Authors: Pablo Odorico, Juan Bajo, Marcos Chaparro"
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L CONN_2 P5
U 1 1 4F854A2A
P 4100 3950
F 0 "P5" V 4050 3950 40  0000 C CNN
F 1 "CONN_2" V 4150 3950 40  0000 C CNN
F 4 "68001-202HLF" H 4100 3950 60  0001 C CNN "mfg#"
	1    4100 3950
	-1   0    0    -1  
$EndComp
Text Label 4450 4050 0    60   ~ 0
GND
Text Label 4450 3850 0    60   ~ 0
VIN
$Comp
L LM7805 U4
U 1 1 4F854A45
P 6250 3900
F 0 "U4" H 6400 3704 60  0000 C CNN
F 1 "LD1117DT33C" H 6250 4100 60  0000 C CNN
F 4 "LD1117DT33CTR" H 6250 3900 60  0001 C CNN "mfg#"
	1    6250 3900
	1    0    0    -1  
$EndComp
$Comp
L LM7805 U5
U 1 1 4F854A57
P 6250 4800
F 0 "U5" H 6400 4604 60  0000 C CNN
F 1 "LD1117DT50C" H 6250 5000 60  0000 C CNN
F 4 "LD1117DT50CTR" H 6250 4800 60  0001 C CNN "mfg#"
	1    6250 4800
	1    0    0    1   
$EndComp
$Comp
L GND #PWR025
U 1 1 4F854CC3
P 7400 4450
F 0 "#PWR025" H 7400 4450 30  0001 C CNN
F 1 "GND" H 7400 4380 30  0001 C CNN
	1    7400 4450
	1    0    0    -1  
$EndComp
Text GLabel 7400 3850 2    60   Output ~ 0
3.3V
Text GLabel 7400 4850 2    60   Output ~ 0
5V
Text Notes 3350 3300 0    60   ~ 0
LD1117xx50C dropout voltage is:\n  1V @ 100mA\n  1.15V @ 500mA\nVIN should be between 6.15V and 15V.\n\n
Text Notes 5650 3500 0    60   ~ 0
LD1115xx Reference Design
Text Notes 700  850  0    118  ~ 24
Power Supply
$Comp
L C C16
U 1 1 4F8633E1
P 5650 4100
F 0 "C16" H 5700 4200 50  0000 L CNN
F 1 "100n" H 5700 4000 50  0000 L CNN
F 4 "C0603C104K4RACTU" H 5650 4100 60  0001 C CNN "mfg#"
	1    5650 4100
	1    0    0    -1  
$EndComp
$Comp
L C C17
U 1 1 4F8633EE
P 5650 4600
F 0 "C17" H 5700 4700 50  0000 L CNN
F 1 "100n" H 5700 4500 50  0000 L CNN
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
Wire Wire Line
	4450 3850 5850 3850
Wire Wire Line
	5050 4850 5850 4850
Wire Wire Line
	6250 4150 6250 4550
Connection ~ 6250 4350
Wire Wire Line
	4450 4350 7400 4350
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
	4450 4350 4450 4050
Wire Wire Line
	5650 4300 5650 4400
$EndSCHEMATC
