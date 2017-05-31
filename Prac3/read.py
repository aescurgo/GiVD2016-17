#Autor: Alvaro Escurra
#Datos necesarios airports.dat y 2008.csv

#NOTA_ Para ejecutar el codigo y guardarlo en un JSON
# python read.py airports.dat > outputAir.json

import csv
import sys

f = open(sys.argv[1], 'rt')
f2 = open('2008.csv', 'rt')
data = []
data2 = []#num of distance
data3 = []#air time
aiports = {}
airport_data = {} #to allocate flightnum
airport_data_distance = {}
airport_data_airtime = {}
minX=0.0
maxX=6689.0
maxX2= 1989.0
maxX3= 242.0
try:
    reader = csv.reader(f)
    #recorremos el fichero para obtener todas las coordenadas de los aeropuertos del mundo
    #Dict --> AIRPORT = {LAT,LON}
    for row in reader:
        if row[4] != '\N':
            aiports[row[4]] = [row[6],row[7]]

    reader2 = csv.reader(f2)
    #Los 3 bucles es para guardar la informacion de los vuelos, distancia y minutos en el aire
    #normalizamos los datos
    #Dict --> AIRPORT = {dataValue}
    for r in reader2:
        if (r[16] != 'Origin'):
            airport_data[r[16]] = [r[9]]
            airport_data_distance[r[16]] = [float(r[18])]
            if(r[13] !=  "NA"): airport_data_airtime[r[16]]  = [float(r[13])]
    valor=0
    for a in aiports:
        if a in airport_data_distance:
            nor = (float(airport_data_distance[a][0]) -minX) / (maxX2 - minX)
            valor =repr(nor)
        else:
            valor =repr(0)
        data2+= (aiports[a][0],aiports[a][1],valor)

    for air in aiports:
        if air in airport_data:
            nor = (float(airport_data[air][0]) -minX) / (maxX - minX)
            valor =repr(nor)

        else:
            valor =repr(0)
        data+= (aiports[air][0],aiports[air][1],valor)

    for air in aiports:
        if air in airport_data_airtime:
            nor = (float(airport_data_airtime[air][0]) -minX) / (maxX - minX)
            valor =repr(nor)
        else:
            valor =repr(0)
        data3+= (aiports[air][0],aiports[air][1],valor)

    #Por ultimo hacemos un print, donde nos sacara por pantalla la estructura del JSON necesaria
    #Para poder utilizarlo
    print """
    [["flight", [%s]],
    ["distance", [%s]],
    ["time", [%s]],
    """ % (",".join(data),
       ",".join(data2),
       ",".join(data3))
    
finally:
    f.close()