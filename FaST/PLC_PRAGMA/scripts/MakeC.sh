#!/usr/bin/env bash
#

libDir=/home/${targetLogin}/Beremiz/matiec/lib/C
execName=logic

C=gcc
CPP=g++

LIBFLAGS=-lwiringPi

${C} -I$libDir -g3 -c -o ./objects/config.o ./source/config.c
${C} -I$libDir -g3 -c -o ./objects/resource1.o ./source/resource1.c
${C} -I$libDir -g3 -c -o ./objects/CFile_0.o ./source/CFile_0.c
${C} -I$libDir -g3 -c -o ./objects/logic.o ./source/logic.c
${CPP} -I$libDir -g3 -c -o ./objects/main.o ./source/main.cpp
${CPP} -o ./output/$execName ./objects/*.o $LIBFLAGS
echo -e "Program \e[34m${execName}\e[39m built. Type ./${execName} for start program"
