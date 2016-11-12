#!/bin/bash
#Se asigna al trabajo el nombre helloomp
#PBS -N atcgridcores
#Se asigna al trabajo la cola ac
#PBS -q ac
#Se imprime información del trabajo usando variables de entorno de PBS

cat /proc/cpuinfo
