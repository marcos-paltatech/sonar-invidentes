#!/usr/bin/python

# Crear Bill of Materials con las opciones:
#   - 'Single part per line'
#   - Separado por comas
#   - Mostrando el mfg# en el Field 1

import string

f= open('sonar_board.csv','r')

error= False
count= 4;
print 'Cantidad de placas:', count
print

for line in f.readlines():
    toks= map(string.strip, line.split(','))
    error= len(toks) != 4
    if error: break
    
    try:
        n= int(toks[1]) * count
    except ValueError:
        error= True
        break

    ref=toks[0]

    print '%d,%s,%s' % (n, toks[3], ref)
    
f.close()

if error:
    print '!!! ERROR'
