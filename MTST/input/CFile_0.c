/* Code generated by Beremiz c_ext confnode */

#include <stdio.h>

/* User includes */
#include <stdlib.h>
#include <wiringPi.h>
#include "iec_types_all.h"

/* User variables reference */

/* User internal user variables and routines */
void InitPin(int pin, int val)
{
    pinMode(pin, val);
}
void CheckPin()
{
    if (wiringPiSetup() == -1) exit(1);
}
int ReadPin(int pin)
{
    return digitalRead(pin);
}
void WritePin(int pin, int val)
{
    digitalWrite(pin, val);
}
int GetRand()
{
   return rand(); 
}
/* Beremiz confnode functions */
int __init_0(int argc,char **argv)
{
  return 0;
}

void __cleanup_0(void)
{

}

void __retrieve_0(void)
{

}

void __publish_0(void)
{

}
