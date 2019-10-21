#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

int highTime = 10;
int lowTime = 10;
int count = 5;
int glitchCount = 3;
int glitchTime = 1;
int pins[5] = {21,22,23,24,25};

int main (int argc, char* argv[])
{
  printf("RPi noise test\nParameters: glitch amount, glitch time, high, low\n");

  if (argc > 1) glitchCount = argv[1];
  if (argc > 2) glitchTime = argv[2];
  if (argc > 3) highTime = argv[3];
  if (argc > 4) lowTime = argv[4];

  if (wiringPiSetup() == -1) exit (1);

  //reset pins
  for (int i = 0; i < count; i++)
  {
    pinMode(pins[i], OUTPUT);
    digitalWrite(pins[i], LOW);
  }

  //noise push
  for (int i = 0; i < glitchCount; i++)
  {
    digitalWrite(pins[i], HIGH);
    delay((glitchCount - i)*glitchTime);
    digitalWrite(pins[i], LOW);
    delay((glitchCount - i)*glitchTime);
  }

  //low period
  delay(lowTime);

  //set pins to HIGH
  for (int i = 0; i < count; i++)
  {
    digitalWrite(pins[i], HIGH);
  }

  //high period
  delay(highTime);

  return 0;
}
