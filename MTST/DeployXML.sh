#!/usr/bin/env bash
#
#Be sure in correct parameters before script running
#
#Script request:
#               sshpass
#               beremiz with python packages
#               STbuilder.py in beremiz folder
#               iec2c exec (configured and build)
#               main.cpp
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
XMLdir=~/Beremiz/beremiz
STname=generated_plc.st
STdir=~/Beremiz/matiec
libDir=/lib/C
workDir=/workdir
execName=logic

C=gcc
CPP=g++

LIBFLAGS=-lwirinPi
CFLAGS=-I.$libDir -g3 -c -o
CPPFLAGS=-I.$libDir -g3 -c -o
LDFLAGS=-o $execName *.o $LIBFLAGS

cd $inputDir
sshpass -p $targetPassword scp $XMLname ${targetLogin}@${targetAddress}:${XMLdir}
sshpass -p $targetPassword scp $CEXTname ${targetLogin}@${targetAddress}:${STdir}
sshpass -p $targetPassword scp $MAINname ${targetLogin}@${targetAddress}:${STdir}
echo -e "Source files: $XMLname $CEXTname $MAINname \e[32mtransferred\e[39m"
if sshpass -p $targetPassword ssh ${targetLogin}@${targetAddress}; then
  echo -e "Connection \e[32mestablished\e[39m"
else
  echo -e "Connection \e[31mfailed\e[39m.\nCheck SSH service on ${targetAddress} for ${targetLogin}"
fi
cd $XMLdir
if python STbuilder.py; then
  echo -e "XML to ST translation \e[32mcomplete\e[39m"
else
  echo -e "XML to ST translation \e[31mfailed\e[39m"
fi
cp $STname ${STdir}/${STname}
cd $STdir
if ./iec2c -b ./${STname}; then
  echo -e "ST to C files \e[32translation completed\e[39\n"
else
  echo -e "ST to C files \e[31translation failed\e[39\n"
fi
#TODO: Makefile for compile from .c/.cpp files

${C} ${CFLAGS} .${workDir}/config.o config.c
${C} ${CFLAGS} .${workDir}/resource1.o resource1.c
${C} ${CFLAGS} .${workDir}/CFile_0.o CFile_0.c
${CPP} ${CPPFLAGS} .${workDir}/main.o main.cpp
cd ${workDir}
${CPP} ${LDFLAGS}
echo "Program ${execName} built. Type ./${execName} for start program"
