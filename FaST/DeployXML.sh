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
inputDir=~/PLC_PRAGMA
CEXTname=CFile_0.c
MAINname=main.cpp
XMLname=plc.xml
XMLdir=/Beremiz/beremiz
STname=generated_plc.st
STdir=/Beremiz/matiec
libDir=/lib/C
workDir=/workdir
execName=logic

C=gcc
CPP=g++

LIBFLAGS=-lwirinPi
CFLAGS={-I.$libDir -g3 -c -o}
CPPFLAGS={-I.$libDir -g3 -c -o}
LDFLAGS={-o $execName *.o $LIBFLAGS}
if sshpass -p $targetPassword scp $inputDir/$XMLname ${targetLogin}@${targetAddress}:/home/${targetLogin}${XMLdir} ; sshpass -p $targetPassword scp $inputDir/$CEXTname ${targetLogin}@${targetAddress}:/home/${targetLogin}${STdir} ; sshpass -p $targetPassword scp $inputDir/$MAINname ${targetLogin}@${targetAddress}:/home/${targetLogin}${STdir} ; then
  echo -e "Source files: $XMLname $CEXTname $MAINname \e[32mtransferred\e[39m"
else
  echo -e "Source files: $XMLname $CEXTname $MAINname \e[31mnot transferred\e[39m"
fi

if sshpass -p $targetPassword ssh ${targetLogin}@${targetAddress} '/home/pi/MakeFromXML.sh' ; then
  echo -e "Deploy \e[32msuccess\e[39m"
else
  echo -e "\nSSH connection \e[31mfailed\e[39m.\nCheck SSH service on ${targetAddress} for ${targetLogin}\n"
fi
