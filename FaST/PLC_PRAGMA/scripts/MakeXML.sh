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

if python /home/${targetLogin}/Beremiz/beremiz/STbuilder.py; then
  echo -e "XML to ST translation \e[32mcompleted\e[39m"
else
  echo -e "XML to ST translation \e[31mfailed\e[39m"
fi
