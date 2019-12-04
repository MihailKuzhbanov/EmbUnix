#!/usr/bin/env bash
#
#Script request:
#               sshpass
#               beremiz with python packages
#               STbuilder.py in beremiz folder
#               iec2c exec (configured and build)
#               main.cpp
#
#Be sure in correct parameters before script running
#
#More information and additional files looks in FaST repository
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

if python /home/${targetLogin}/Beremiz/beremiz/STbuilder.py; then
  echo -e "XML to ST translation \e[32mcompleted\e[39m"
else
  echo -e "XML to ST translation \e[31mfailed\e[39m"
fi

cd /home/${targetLogin}/Beremiz/matiec/
if ./iec2c -b ./${STname}; then
  echo -e "ST to C files \e[32mtranslation completed\e[39m\n"
else
  echo -e "ST to C files \e[31mtranslation failed\e[39m\n"
fi
mv ./${STname} /home/${targetLogin}/PLC_PRAGMA/input
mv POUS.c POUS.h resource1.c LOCATED_VARIABLES.h VARIABLES.csv config.c config.h /home/${targetLogin}/PLC_PRAGMA/source/
cd /home/${targetLogin}/PLC_PRAGMA/
#TODO: Makefile for compile from .c/.cpp files
${C} -I$libDir -g3 -c -o ./objects/config.o ./source/config.c
${C} -I$libDir -g3 -c -o ./objects/resource1.o ./source/resource1.c
${C} -I$libDir -g3 -c -o ./objects/CFile_0.o ./source/CFile_0.c
${C} -I$libDir -g3 -c -o ./objects/logic.o ./source/logic.c
${CPP} -I$libDir -g3 -c -o ./objects/main.o ./source/main.cpp
${CPP} -o ./output/$execName ./objects/*.o $LIBFLAGS
echo -e "Program \e[34m${execName}\e[39m built. Type ./${execName} for start program"
