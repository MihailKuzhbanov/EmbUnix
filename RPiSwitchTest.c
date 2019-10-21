#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

int latencyTime = 1;
int highTime = 10;
int lowTime = 10;
int count = 5;
int pins[5] = {21,22,23,24,25};

int main (int argc, char* argv[])
{
  printf("RPi switch test\nParameters: latency, high, low\n");
  if (argc > 1) latencyTime = argv[1];
  if (argc > 2) highTime = argv[2];
  if (argc > 3) lowTime = argv[3];
  if (wiringPiSetup() == -1) exit (1);

  //reset pins
  for (int i = 0; i < count; i++)
  {
    pinMode(pins[i], OUTPUT);
    digitalWrite(pins[i], LOW);
  }

  //low period
  delay(lowTime);

  //set pins to HIGH
  for (int i = 0; i < count; i++)
  {
    digitalWrite(pins[i], HIGH);
    delay(latencyTime);
  }
  
  //high period
  delay(highTime);

  return 0;
}
