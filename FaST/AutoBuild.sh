#send XML file to target
scp plc.xml pi@192.168.137.2:~/Beremiz/projects/

#build ST file
#put STBuilder.py into /Beremiz/beremiz folder
ssh pi@192.168.137.2
cd /home/pi/Beremiz/beremiz
python STbuilder.py

#generate C files
cd ~/Beremiz/matiec
cp ~/Beremiz/projects/generated_plc.st .
./iec2c -b generated_plc.st
cp ~/Beremiz/projects/build/CFile_0.c .

#create entry point in nano or put main.c into Beremiz/matiec folder
nano main.c

#compile C files
gcc main.c CFile_0.c -o main -I./lib/C

#copy exec file to project folder
cd ~/Beremiz/projects
cp ~/Beremiz/matiec/main .
./main
