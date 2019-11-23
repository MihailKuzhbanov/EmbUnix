//git clone https://github.com/WiringPi/WiringPi.git

#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

int main (void)
{
  int pinIn = 20, pinOut = 21;
  if (wiringPiSetup() == -1) exit (1);
  printf("Raspberry Pi delay test\n");

  pinMode(pinIn, INPUT);
  pinMode(pinOut, OUTPUT);

  while (1) digitalWrite(pinOut, digitalRead(pinIn));
  return 0;
}

//gcc -o RPiDelayTest RPiDelayTest.c -lwiringPi -lm -lpththread -lcrypt -lrt
//sudo ./RPiDelayTest
