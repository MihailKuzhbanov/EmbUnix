C=gcc
CPP=g++
CFLAGS=-I/home/${targetLogin}/Beremiz/matiec/lib/C -g3 -c -o
LFLAGS=-lwiringPi
all: logic

logic: CFile_0.o config.o logic.o resource1.o main.o
	$(CPP) $(LFLAGS) main.o resource1.o logic.o config.o CFile_0.o -o ../output/logic

main.o: main.cpp
	$(CPP) $(CFLAGS) ../source/main.cpp

resource1.o: resource1.c
	$(C) $(CFLAGS) ../source/resource1.c

logic.o: logic.c
	$(C) $(CFLAGS) ../source/logic.c

config.o: config.c
	$(C) $(CFLAGS) ../source/config.c

CFile_0.o: CFile_0.c
	$(C) $(CFLAGS) ../source/CFile_0.c

clean:
	rm -rf *.o logic
