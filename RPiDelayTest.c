//cd /tmp
//wget http://project-downloads.drogon.net/files/wiringPi-1.tgz
//tar xfz wiringPi-1.tgz
//cd wiringPi/wiringPi
//make
//sudo make install
//cd ~
//nano blink.c

#include
#include

int main (void)
{
  int pinIn = 20, pinOut = 21;
  printf("Raspberry Pi delay test\n");

  if (wiringPiSetup() == -1) exit (1);

  pinMode(pinIn, INPUT);
  pinMode(pinOut, OUTPUT);

  for (;;)
  {
    if (digitalRead(pinIn)) digitalWrite(pinOut, 1));
    if (!digitalRead(pinIn)) digitalWrite(pinOut, 0));
  }
  return 0;
}

//gcc -o blink blink.c -L/usr/local/lib -lwiringPi
//sudo ./blink
