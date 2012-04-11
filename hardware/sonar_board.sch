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
Sheet 1 6
Title "Main Blocks"
Date "11 apr 2012"
Rev "0.1"
Comp "Departamento de Ingeniería Eléctrica y Computadoras, Universidad Nacional del Sur"
Comment1 "Directors: Ricardo Cayssials, Edgardo Ferro"
Comment2 "Authors: Pablo Odorico, Juan Bajo, Marcos Chaparro"
Comment3 ""
Comment4 ""
$EndDescr
$Sheet
S 4950 2300 1850 2050
U 4F84A04D
F0 "MCU" 118
F1 "stm32.sch" 60
F2 "AT_TX" O L 4950 2600 60 
F3 "AT_RX" I L 4950 2750 60 
F4 "MEM_CLK" O R 6800 2600 60 
F5 "MEM_MISO" I R 6800 3050 60 
F6 "MEM_MOSI" O R 6800 2750 60 
F7 "MEM_NCS" O R 6800 2900 60 
F8 "SENS_SCL" B R 6800 4050 60 
F9 "SENS_SDA" B R 6800 3900 60 
F10 "DACOutput" O L 4950 3000 60 
$EndSheet
$Sheet
S 1650 2300 1850 2050
U 4F84AD9A
F0 "Bluetooth" 118
F1 "bluetooth.sch" 60
F2 "DACInput" I R 3500 3000 60 
F3 "AT_RX" I R 3500 2600 60 
F4 "AT_TX" O R 3500 2750 60 
$EndSheet
$Sheet
S 8250 3600 1850 1250
U 4F851067
F0 "Sensors" 118
F1 "sensors.sch" 60
F2 "SENS_SDA" B L 8250 3900 60 
F3 "SENS_SCL" B L 8250 4050 60 
$EndSheet
$Sheet
S 8250 2000 1850 1200
U 4F84D207
F0 "Memory" 118
F1 "memory.sch" 60
F2 "MEM_CLK" I L 8250 2600 60 
F3 "MEM_MOSI" I L 8250 2750 60 
F4 "MEM_NCS" I L 8250 2900 60 
F5 "MEM_MISO" O L 8250 3050 60 
$EndSheet
Wire Wire Line
	8250 2600 6800 2600
Wire Wire Line
	6800 2750 8250 2750
Wire Wire Line
	8250 2900 6800 2900
Wire Wire Line
	6800 3050 8250 3050
Wire Wire Line
	4950 2600 3500 2600
Wire Wire Line
	3500 2750 4950 2750
Wire Wire Line
	4950 3000 3500 3000
Wire Wire Line
	8250 3900 6800 3900
Wire Wire Line
	6800 4050 8250 4050
$Sheet
S 1650 5350 1850 1300
U 4F857ACF
F0 "Power" 118
F1 "power.sch" 60
$EndSheet
Text Notes 700  950  0    157  ~ 31
Bluetooth Sonar System for the Blind
$EndSCHEMATC
