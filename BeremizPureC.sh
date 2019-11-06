#Beremiz->Build Project
cd Beremiz/matiec
./iec2c -b ~/Beremiz/projects/build/generated_plc.st
cp ~/Beremiz/projects/build/CFile_0.c
nano main.c
#include optional libs as flags
gcc main.c CFile_0.c -o main -I./lib/C
./main
