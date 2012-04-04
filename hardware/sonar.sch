EESchema Schematic File Version 2  date Wed 04 Apr 2012 03:07:09 PM ART
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:special
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:STM32VLDISCOVERY
LIBS:DLP-USB232R
LIBS:SRF02
LIBS:W25Q80BV
LIBS:BTM511
EELAYER 25  0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "sonar-invidentes"
Date "4 apr 2012"
Rev "0.3"
Comp "Departamento de Ingeniería Eléctrica y de Computadoras, Universidad Nacional del Sur"
Comment1 "Directores: Ricardo Cayssials, Edgardo Ferro"
Comment2 "Juan Bajo <jmbajo@gmail.com>"
Comment3 "Pablo Odorico <pablo.odorico@gmail.com>"
Comment4 ""
$EndDescr
$Comp
L GND #PWR01
U 1 1 4F764D2F
P 900 2900
F 0 "#PWR01" H 900 2900 30  0001 C CNN
F 1 "GND" H 900 2830 30  0001 C CNN
	1    900  2900
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR02
U 1 1 4F764D18
P 2200 1000
F 0 "#PWR02" H 2200 1000 30  0001 C CNN
F 1 "GND" H 2200 930 30  0001 C CNN
	1    2200 1000
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR03
U 1 1 4F764CFF
P 2700 950
F 0 "#PWR03" H 2700 1050 30  0001 C CNN
F 1 "VCC" H 2700 1050 30  0000 C CNN
	1    2700 950 
	1    0    0    -1  
$EndComp
Text GLabel 1500 6350 0    60   Input ~ 0
UART_AT
Text GLabel 8050 3850 0    60   BiDi ~ 0
SPI
$Comp
L GND #PWR04
U 1 1 4F76491D
P 3450 3950
F 0 "#PWR04" H 3450 3950 30  0001 C CNN
F 1 "GND" H 3450 3880 30  0001 C CNN
	1    3450 3950
	1    0    0    -1  
$EndComp
$Comp
L BTM511 U?
U 1 1 4F7647A1
P 2150 2800
F 0 "U?" H 2150 2700 50  0000 C CNN
F 1 "BTM511" H 2150 2900 50  0000 C CNN
F 2 "MODULE" H 2150 2800 50  0001 C CNN
F 3 "DOCUMENTATION" H 2150 2800 50  0001 C CNN
	1    2150 2800
	-1   0    0    1   
$EndComp
$Comp
L R Rp2
U 1 1 4F5E33F5
P 10400 1750
F 0 "Rp2" V 10480 1750 50  0000 C CNN
F 1 "2.14k" V 10400 1750 50  0000 C CNN
	1    10400 1750
	-1   0    0    1   
$EndComp
$Comp
L R Rp1
U 1 1 4F5E33E6
P 10550 1750
F 0 "Rp1" V 10630 1750 50  0000 C CNN
F 1 "2.14k" V 10550 1750 50  0000 C CNN
	1    10550 1750
	1    0    0    -1  
$EndComp
$Comp
L USB_2 USB
U 1 1 4F5E3365
P 9500 5050
F 0 "USB" H 9425 5300 60  0000 C CNN
F 1 "USB_2" H 9550 4750 60  0001 C CNN
F 4 "VCC" H 9825 5200 50  0001 C CNN "VCC"
F 5 "D+" H 9800 5100 50  0001 C CNN "Data+"
F 6 "D-" H 9800 5000 50  0001 C CNN "Data-"
F 7 "GND" H 9825 4900 50  0001 C CNN "Ground"
	1    9500 5050
	0    -1   -1   0   
$EndComp
$Comp
L USB_2 STLink
U 1 1 4F5E32E0
P 5850 2800
F 0 "STLink" H 5775 3050 60  0000 C CNN
F 1 "USB_2" H 5900 2500 60  0001 C CNN
F 4 "VCC" H 6175 2950 50  0001 C CNN "VCC"
F 5 "D+" H 6150 2850 50  0001 C CNN "Data+"
F 6 "D-" H 6150 2750 50  0001 C CNN "Data-"
F 7 "GND" H 6175 2650 50  0001 C CNN "Ground"
	1    5850 2800
	0    -1   -1   0   
$EndComp
Text GLabel 3550 4850 2    60   Input ~ 0
AnalogAudio
Text GLabel 7150 2300 0    60   BiDi ~ 0
I2C
Text GLabel 8550 5100 0    60   BiDi ~ 0
UART_STDIO
$Comp
L GND #PWR05
U 1 1 4F5D2938
P 7550 2550
F 0 "#PWR05" H 7550 2550 30  0001 C CNN
F 1 "GND" H 7550 2480 30  0001 C CNN
	1    7550 2550
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR06
U 1 1 4F5D23D8
P 8200 4200
F 0 "#PWR06" H 8200 4300 30  0001 C CNN
F 1 "VCC" H 8200 4300 30  0000 C CNN
	1    8200 4200
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR07
U 1 1 4F5D2377
P 10400 4050
F 0 "#PWR07" H 10400 4150 30  0001 C CNN
F 1 "VCC" H 10400 4150 30  0000 C CNN
	1    10400 4050
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR08
U 1 1 4F5D235D
P 10600 4000
F 0 "#PWR08" H 10600 4000 30  0001 C CNN
F 1 "GND" H 10600 3930 30  0001 C CNN
	1    10600 4000
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR09
U 1 1 4F5D21AD
P 7200 6050
F 0 "#PWR09" H 7200 6050 30  0001 C CNN
F 1 "GND" H 7200 5980 30  0001 C CNN
	1    7200 6050
	1    0    0    -1  
$EndComp
$Comp
L SRF02 SLeft
U 1 1 4F5D1EE0
P 7950 1250
F 0 "SLeft" H 7950 1150 50  0000 C CNN
F 1 "SRF02" H 7950 1350 50  0000 C CNN
F 2 "MODULE" H 7950 1250 50  0001 C CNN
F 3 "DOCUMENTATION" H 7950 1250 50  0001 C CNN
	1    7950 1250
	0    -1   -1   0   
$EndComp
$Comp
L SRF02 SRight
U 1 1 4F5D1ECE
P 9750 1250
F 0 "SRight" H 9750 1150 50  0000 C CNN
F 1 "SRF02" H 9750 1350 50  0000 C CNN
F 2 "MODULE" H 9750 1250 50  0001 C CNN
F 3 "DOCUMENTATION" H 9750 1250 50  0001 C CNN
	1    9750 1250
	0    -1   -1   0   
$EndComp
$Comp
L SRF02 SCenter
U 1 1 4F5D1EC8
P 8850 1250
F 0 "SCenter" H 8850 1150 50  0000 C CNN
F 1 "SRF02" H 8850 1350 50  0000 C CNN
F 2 "MODULE" H 8850 1250 50  0001 C CNN
F 3 "DOCUMENTATION" H 8850 1250 50  0001 C CNN
	1    8850 1250
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR010
U 1 1 4F5D1E6B
P 10700 6400
F 0 "#PWR010" H 10700 6400 30  0001 C CNN
F 1 "GND" H 10700 6330 30  0001 C CNN
	1    10700 6400
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR011
U 1 1 4F5D1D45
P 4450 3050
F 0 "#PWR011" H 4450 3150 30  0001 C CNN
F 1 "VCC" H 4450 3150 30  0000 C CNN
	1    4450 3050
	1    0    0    -1  
$EndComp
$Comp
L W25Q80BV FlashMem
U 0 1 4F5D1604
P 9350 4100
F 0 "FlashMem" H 9350 4000 50  0000 C CNN
F 1 "W25Q80BV" H 9350 4200 50  0000 C CNN
F 2 "MODULE" H 9350 4100 50  0001 C CNN
F 3 "DOCUMENTATION" H 9350 4100 50  0001 C CNN
	0    9350 4100
	-1   0    0    1   
$EndComp
$Comp
L DLP-USB232R UARTtoUSB
U 0 1 4F5D15FA
P 9500 5800
F 0 "UARTtoUSB" H 9500 5700 50  0000 C CNN
F 1 "DLP-USB232R" H 9500 5900 50  0000 C CNN
F 2 "MODULE" H 9500 5800 50  0001 C CNN
F 3 "DOCUMENTATION" H 9500 5800 50  0001 C CNN
	0    9500 5800
	-1   0    0    1   
$EndComp
$Comp
L STM32VLDISCOVERY U1
U 1 1 4F5D0FE0
P 5850 4500
F 0 "U1" H 5850 4400 50  0000 C CNN
F 1 "STM32VLDISCOVERY" H 5850 4600 50  0000 C CNN
F 2 "MODULE" H 5850 4500 50  0001 C CNN
F 3 "DOCUMENTATION" H 5850 4500 50  0001 C CNN
	1    5850 4500
	1    0    0    -1  
$EndComp
Wire Wire Line
	1100 2700 900  2700
Wire Wire Line
	1100 2400 700  2400
Wire Wire Line
	1100 2300 800  2300
Wire Wire Line
	900  2700 900  2900
Connection ~ 2700 1100
Wire Wire Line
	2700 950  2700 1250
Wire Wire Line
	2500 1250 2500 1100
Wire Wire Line
	800  2300 800  6500
Wire Wire Line
	800  6500 7450 6500
Wire Wire Line
	7450 6500 7450 4550
Wire Wire Line
	7450 4550 7000 4550
Wire Wire Line
	7950 6100 8350 6100
Wire Wire Line
	8400 3500 8400 3650
Wire Wire Line
	10800 3600 10800 4150
Wire Wire Line
	10800 3600 8500 3600
Wire Wire Line
	8500 3600 8500 3750
Wire Wire Line
	8500 3750 7250 3750
Wire Wire Line
	7000 5150 7850 5150
Wire Wire Line
	7250 3750 7250 4050
Wire Wire Line
	3200 3800 3450 3800
Wire Wire Line
	10550 2100 7250 2100
Wire Wire Line
	10400 1500 10400 1400
Wire Wire Line
	10400 1400 10800 1400
Wire Wire Line
	10800 1400 10800 2300
Connection ~ 10400 2100
Wire Wire Line
	10550 2100 10550 2000
Connection ~ 9550 2100
Connection ~ 9650 2200
Wire Wire Line
	9650 2200 9650 2000
Wire Wire Line
	7850 5150 7850 6200
Wire Wire Line
	7250 2100 7250 3350
Connection ~ 8750 2200
Wire Wire Line
	8750 2200 8750 2000
Connection ~ 8150 2400
Wire Wire Line
	8150 2000 8150 2400
Connection ~ 7850 2200
Wire Wire Line
	7850 2000 7850 2200
Wire Wire Line
	7350 3450 7350 2200
Wire Wire Line
	7350 3450 7000 3450
Wire Wire Line
	7550 2550 7550 2400
Connection ~ 8650 2100
Wire Wire Line
	9550 2100 9550 2000
Wire Wire Line
	7750 2100 7750 2000
Wire Wire Line
	10550 5500 10700 5500
Wire Wire Line
	10700 5500 10700 5400
Wire Wire Line
	10700 5400 10550 5400
Wire Wire Line
	8500 4250 8200 4250
Wire Wire Line
	10200 3950 10300 3950
Wire Wire Line
	10300 3950 10300 3900
Wire Wire Line
	10200 4050 10400 4050
Wire Wire Line
	7250 3350 7000 3350
Wire Wire Line
	10700 6400 10700 6200
Wire Wire Line
	4450 3050 4450 3350
Wire Wire Line
	4450 3350 4700 3350
Wire Wire Line
	7000 5850 7200 5850
Wire Wire Line
	7200 5850 7200 6050
Wire Wire Line
	10600 4000 10600 3900
Wire Wire Line
	10600 3900 10300 3900
Wire Wire Line
	8200 4250 8200 4200
Wire Wire Line
	8350 4250 8350 4150
Connection ~ 8350 4250
Wire Wire Line
	8350 4150 8500 4150
Wire Wire Line
	10700 6200 10550 6200
Wire Wire Line
	8500 3950 7000 3950
Wire Wire Line
	4700 4950 3300 4950
Wire Wire Line
	8650 2100 8650 2000
Connection ~ 7750 2100
Wire Wire Line
	9950 2000 9950 2400
Wire Wire Line
	7000 3550 7450 3550
Wire Wire Line
	7450 3550 7450 2300
Wire Wire Line
	7950 2300 7950 2000
Connection ~ 7950 2300
Wire Wire Line
	9050 2400 9050 2000
Connection ~ 9050 2400
Wire Wire Line
	8850 2300 8850 2000
Connection ~ 8850 2300
Wire Wire Line
	7950 6100 7950 5250
Wire Wire Line
	8350 6100 8350 6000
Wire Wire Line
	8350 6000 8450 6000
Wire Wire Line
	9750 2000 9750 2300
Connection ~ 9750 2300
Wire Wire Line
	10400 2100 10400 2000
Wire Wire Line
	10700 1500 10700 2200
Wire Wire Line
	10700 1500 10550 1500
Wire Wire Line
	10700 2200 7350 2200
Wire Wire Line
	7450 2300 10800 2300
Wire Wire Line
	9950 2400 7550 2400
Wire Wire Line
	3200 3900 3300 3900
Wire Wire Line
	3300 3900 3300 4950
Wire Wire Line
	3450 3800 3450 3950
Wire Wire Line
	7250 4050 7000 4050
Wire Wire Line
	7000 4150 7350 4150
Wire Wire Line
	7350 4150 7350 4050
Wire Wire Line
	7350 4050 8500 4050
Wire Wire Line
	7950 5250 7000 5250
Wire Wire Line
	7000 3850 7150 3850
Wire Wire Line
	7150 3850 7150 3650
Wire Wire Line
	10800 4150 10200 4150
Wire Wire Line
	8400 3500 10900 3500
Wire Wire Line
	10900 3500 10900 4250
Wire Wire Line
	10900 4250 10200 4250
Wire Wire Line
	7150 3650 8400 3650
Wire Wire Line
	7850 6200 8450 6200
Wire Wire Line
	7000 4450 7550 4450
Wire Wire Line
	7550 4450 7550 6600
Wire Wire Line
	7550 6600 700  6600
Wire Wire Line
	700  6600 700  2400
Wire Wire Line
	2500 1100 2700 1100
Wire Wire Line
	2600 1250 2600 1100
Connection ~ 2600 1100
Wire Wire Line
	2400 1250 2400 900 
Wire Wire Line
	2400 900  2200 900 
Wire Wire Line
	2200 900  2200 1000
Wire Notes Line
	7800 4650 11000 4650
Wire Notes Line
	11000 4650 11000 6550
Wire Notes Line
	11000 6550 7700 6550
Wire Notes Line
	7700 6550 7700 4650
Wire Notes Line
	7700 4650 7900 4650
Text Notes 10250 4800 0    60   ~ 0
Debugging I/O
$EndSCHEMATC
