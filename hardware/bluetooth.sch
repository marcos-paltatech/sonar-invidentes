EESchema Schematic File Version 2  date Wed 11 Apr 2012 02:45:27 AM ART
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
Sheet 3 6
Title "Bluetooth Module"
Date "11 apr 2012"
Rev "0.1"
Comp "Departamento de Ingeniería Eléctrica y Computadoras, Universidad Nacional del Sur"
Comment1 "Directors: Ricardo Cayssials, Edgardo Ferro"
Comment2 "Authors: Pablo Odorico, Juan Bajo, Marcos Chaparro"
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L BTM511 U2
U 1 1 4F84ADA4
P 5650 4100
F 0 "U2" H 5650 4000 50  0000 C CNN
F 1 "BTM511" H 5650 4200 50  0000 C CNN
F 2 "MODULE" H 5650 4100 50  0001 C CNN
F 3 "DOCUMENTATION" H 5650 4100 50  0001 C CNN
	1    5650 4100
	-1   0    0    1   
$EndComp
$Comp
L CP1 C20
U 1 1 4F84ADF0
P 9100 5000
F 0 "C20" H 9150 5100 50  0000 L CNN
F 1 "1uF" H 9150 4900 50  0000 L CNN
	1    9100 5000
	0    -1   -1   0   
$EndComp
$Comp
L C C21
U 1 1 4F84ADF6
P 9700 5350
F 0 "C21" H 9750 5450 50  0000 L CNN
F 1 "4.7nF" H 9750 5250 50  0000 L CNN
	1    9700 5350
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR017
U 1 1 4F84ADFC
P 9700 5800
F 0 "#PWR017" H 9700 5800 30  0001 C CNN
F 1 "GND" H 9700 5730 30  0001 C CNN
	1    9700 5800
	1    0    0    -1  
$EndComp
Text HLabel 10250 5000 2    60   Input ~ 0
DACInput
Text Notes 9500 5250 2    60   ~ 0
Coupling Cap.
Text Notes 10000 5400 0    60   ~ 0
Low-pass filter to\nsmooth DAC's output.
$Comp
L JUMPER AU+1
U 1 1 4F84AECC
P 8350 5000
F 0 "AU+1" H 8350 5150 60  0000 C CNN
F 1 "JUMPER" H 8350 4920 40  0000 C CNN
	1    8350 5000
	1    0    0    -1  
$EndComp
$Comp
L JUMPER AU-1
U 1 1 4F84AF11
P 8350 5350
F 0 "AU-1" H 8350 5500 60  0000 C CNN
F 1 "JUMPER" H 8350 5270 40  0000 C CNN
	1    8350 5350
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR018
U 1 1 4F84B3A8
P 6950 4300
F 0 "#PWR018" H 6950 4300 30  0001 C CNN
F 1 "GND" H 6950 4230 30  0001 C CNN
	1    6950 4300
	1    0    0    -1  
$EndComp
Text Notes 8050 4650 0    60   ~ 0
The jumpers can be used to use another audio input,\nor use the audio output elsewhere.
Text GLabel 6300 2400 2    60   Input ~ 0
3.3V
$Comp
L GND #PWR019
U 1 1 4F84B82D
P 4400 4100
F 0 "#PWR019" H 4400 4100 30  0001 C CNN
F 1 "GND" H 4400 4030 30  0001 C CNN
	1    4400 4100
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR020
U 1 1 4F84B83C
P 5750 2400
F 0 "#PWR020" H 5750 2400 30  0001 C CNN
F 1 "GND" H 5750 2330 30  0001 C CNN
	1    5750 2400
	1    0    0    -1  
$EndComp
Text HLabel 2300 3600 0    60   Input ~ 0
AT_RX
Text HLabel 2300 3950 0    60   Output ~ 0
AT_TX
NoConn ~ 6700 4800
NoConn ~ 6700 4700
NoConn ~ 6700 4600
NoConn ~ 6700 4500
NoConn ~ 6700 4400
NoConn ~ 6700 4100
NoConn ~ 6700 4000
NoConn ~ 6700 3900
NoConn ~ 6700 3800
NoConn ~ 6700 3700
NoConn ~ 6700 3600
NoConn ~ 6700 3500
NoConn ~ 6700 3400
NoConn ~ 5600 2550
NoConn ~ 5500 2550
NoConn ~ 5400 2550
NoConn ~ 5300 2550
NoConn ~ 5200 2550
NoConn ~ 5100 2550
NoConn ~ 4600 3300
NoConn ~ 4600 3800
NoConn ~ 4600 3900
NoConn ~ 4600 4100
NoConn ~ 4600 4200
NoConn ~ 4600 4300
NoConn ~ 4600 4400
NoConn ~ 4600 4500
NoConn ~ 4600 4600
NoConn ~ 4600 4700
NoConn ~ 4600 3400
NoConn ~ 4600 3500
NoConn ~ 5700 2550
NoConn ~ 5800 2550
$Comp
L JUMPER AT_RX1
U 1 1 4F84CD79
P 2800 3600
F 0 "AT_RX1" H 2800 3750 60  0000 C CNN
F 1 "JUMPER" H 2800 3520 40  0000 C CNN
	1    2800 3600
	-1   0    0    -1  
$EndComp
$Comp
L JUMPER AT_TX1
U 1 1 4F84CD7F
P 2800 3950
F 0 "AT_TX1" H 2800 4100 60  0000 C CNN
F 1 "JUMPER" H 2800 3870 40  0000 C CNN
	1    2800 3950
	-1   0    0    -1  
$EndComp
Text Notes 1750 3200 0    60   ~ 0
The jumpers allow the module's UART to\nbe connected to a PC to be configured.
Text Notes 1750 4250 0    60   ~ 0
Default: 9600, N, 8, 1
Text GLabel 9550 750  0    60   Input ~ 0
3.3V
$Comp
L C C13
U 1 1 4F8547A5
P 9900 950
F 0 "C13" H 9950 1050 50  0000 L CNN
F 1 "100nF" H 9950 850 50  0000 L CNN
	1    9900 950 
	1    0    0    -1  
$EndComp
$Comp
L C C14
U 1 1 4F8547AB
P 10200 950
F 0 "C14" H 10250 1050 50  0000 L CNN
F 1 "100nF" H 10250 850 50  0000 L CNN
	1    10200 950 
	1    0    0    -1  
$EndComp
$Comp
L C C15
U 1 1 4F8547B1
P 10500 950
F 0 "C15" H 10550 1050 50  0000 L CNN
F 1 "100nF" H 10550 850 50  0000 L CNN
	1    10500 950 
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR021
U 1 1 4F8547B7
P 9550 1250
F 0 "#PWR021" H 9550 1250 30  0001 C CNN
F 1 "GND" H 9550 1180 30  0001 C CNN
	1    9550 1250
	1    0    0    -1  
$EndComp
Text Notes 9200 1500 0    60   ~ 0
Capacitors to place near VDD's
Wire Wire Line
	9300 5000 10250 5000
Connection ~ 9700 5000
Connection ~ 9700 5000
Wire Wire Line
	9700 5550 9700 5800
Wire Notes Line
	11000 4700 11000 5950
Wire Notes Line
	11000 5950 8600 5950
Wire Wire Line
	6700 5200 7000 5200
Wire Wire Line
	6700 4900 6850 4900
Wire Wire Line
	6850 5100 6700 5100
Wire Wire Line
	9700 5650 8650 5650
Wire Wire Line
	8650 5650 8650 5350
Wire Wire Line
	8900 5000 8650 5000
Wire Notes Line
	7950 4450 7950 5950
Wire Notes Line
	7950 5950 8650 5950
Wire Wire Line
	6850 4300 6850 5350
Connection ~ 6850 5100
Wire Wire Line
	6850 4300 6700 4300
Connection ~ 6850 4900
Wire Wire Line
	6950 3300 6950 4300
Wire Notes Line
	7950 4450 11000 4450
Wire Notes Line
	11000 4450 11000 4750
Wire Wire Line
	8050 5000 6700 5000
Wire Wire Line
	6850 5350 8050 5350
Wire Wire Line
	6000 2550 6000 2400
Wire Wire Line
	6200 2550 6200 2400
Connection ~ 6200 2400
Wire Wire Line
	6100 2550 6100 2400
Connection ~ 6100 2400
Wire Wire Line
	6000 2400 6300 2400
Wire Wire Line
	6950 3300 6700 3300
Wire Wire Line
	4400 4000 4400 4100
Wire Wire Line
	4400 4000 4600 4000
Wire Wire Line
	5900 2550 5900 2300
Wire Wire Line
	5900 2300 5750 2300
Wire Wire Line
	5750 2300 5750 2400
Wire Wire Line
	3100 3600 4600 3600
Wire Wire Line
	3200 3700 4600 3700
Wire Wire Line
	2500 3600 2300 3600
Wire Wire Line
	2300 3950 2500 3950
Wire Wire Line
	3200 3700 3200 3950
Wire Wire Line
	3200 3950 3100 3950
Wire Notes Line
	1650 3000 1650 4350
Wire Notes Line
	1650 4350 3700 4350
Wire Notes Line
	3700 4350 3700 3000
Wire Notes Line
	3700 3000 1650 3000
Wire Wire Line
	7000 5200 7000 5000
Connection ~ 7000 5000
Wire Wire Line
	9550 1150 9550 1250
Wire Wire Line
	10500 750  9550 750 
Wire Wire Line
	10500 1150 9550 1150
Wire Wire Line
	9900 750  9900 750 
Connection ~ 9900 750 
Connection ~ 9900 750 
Wire Wire Line
	10200 750  10200 750 
Connection ~ 10200 750 
Connection ~ 10200 750 
Wire Wire Line
	10200 1150 10200 1150
Connection ~ 10200 1150
Connection ~ 10200 1150
Wire Wire Line
	9900 1150 9900 1150
Connection ~ 9900 1150
Connection ~ 9900 1150
Wire Wire Line
	6700 4200 6950 4200
Connection ~ 6950 4200
Wire Wire Line
	9700 5000 9700 5150
Connection ~ 9700 5650
$EndSCHEMATC
