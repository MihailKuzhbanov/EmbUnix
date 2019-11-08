#send XML file to target
scp plc.xml pi@192.168.137.2: /home/pi/Beremiz/projects

#build ST file
python STbuilder.py

#generate C files
cd Beremiz/matiec
./iec2c -b ~/Beremiz/projects/build/generated_plc.st
cp ~/Beremiz/projects/build/CFile_0.c

#create entry point
nano main.c

#compile C files
gcc main.c CFile_0.c -o main -I./lib/C
./main
