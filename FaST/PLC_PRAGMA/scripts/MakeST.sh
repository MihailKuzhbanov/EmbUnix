#!/usr/bin/env bash
#

targetAddress=192.168.137.2
targetLogin=pi
targetPassword=raspberry
STname=generated_plc.st
libDir=/home/${targetLogin}/Beremiz/matiec/lib/C
execName=logic

C=gcc
CPP=g++

LIBFLAGS=-lwiringPi

cd /home/${targetLogin}/Beremiz/matiec/
if ./iec2c -b ./${STname}; then
  echo -e "ST to C files \e[32mtranslation completed\e[39m\n"
else
  echo -e "ST to C files \e[31mtranslation failed\e[39m\n"
fi
mv ./${STname} /home/${targetLogin}/PLC_PRAGMA/input
mv POUS.c POUS.h resource1.c LOCATED_VARIABLES.h VARIABLES.csv config.c config.h /home/${targetLogin}/PLC_PRAGMA/source/
