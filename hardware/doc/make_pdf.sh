#!/bin/bash

# Para ejecutar desde /hardware: doc/make_pdf.sh

# Exportar esquematico:
# File -> Plot -> PostScript, Color, Plot All
#
# Exportar board:
# File -> Plot (en el mismo directorio)
# Capas: Front, GND, VCC, Back, SilkS_Front, SilkS_Back, Comments
# Scaling 3:1

gs -q -sPAPERSIZE=a4 -dNOPAUSE -dBATCH -sDEVICE=pdfwrite -sOutputFile=doc/sonar_board_v0.pdf \
sonar_board.ps \
sonar_board-MCU.ps \
sonar_board-Bluetooth.ps \
sonar_board-Sensors.ps \
sonar_board-Memory.ps \
sonar_board-Power.ps \
sonar_board-SilkS_Front.ps \
sonar_board-Front.ps \
sonar_board-VCC.ps \
sonar_board-GND.ps \
sonar_board-Back.ps \
sonar_board-SilkS_Back.ps

./clean.sh
