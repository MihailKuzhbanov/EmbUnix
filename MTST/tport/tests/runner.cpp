//////////////////////////////////////////////////////////////////////////////
// <@meta=.metablank>
//////////////////////////////////////////////////////////////////////////////

# include <string>
# include <thread>

# include "../include/tport.hpp"
# include "wiringPi.h"
# define CHNUM 1
using namespace tport;

void OnStart() {
  if (wiringPiSetup() == -1) exit(1);
}

std::vector<int> MakeComms(int cntCom, int startPin) {
  std::vector<int> pinCom;
  for (int i = 0; i < cntCom; i++) {
    pinCom.push_back(startPin + i);
  }
  return pinCom;
}

void InitComms(std::vector<int> inputs, std::vector<int> outputs) {
  for (auto pin : inputs) {
    pinMode(pin, INPUT);
  }
  for (auto pin : outputs) {
    pinMode(pin, OUTPUT);
  }
}

void PinReader(TPort<int>& tport) {
    std::vector<int> data(CHNUM);
    Exit_t res;
    while(true) {
        res = tport.write(data, 0);
        for (int i = 0; i < CHNUM; i++) {
            data[i] = digitalRead(24 + i);
        }
        usleep(9);
    }
}

void PinWriter(TPort<int>& tport) {
    std::vector<int> data(CHNUM);
    while(true) {
        if (tport.read(data) == EXIT_SUCCESS) {
            for (int i = 0; i < CHNUM; i++) {
                digitalWrite(25 + i, data[i]);
            }
        }
        usleep(11);
    }
}

int main(int argc, char** argv) {
    OnStart();
    std::vector<int> inputs = MakeComms(CHNUM, 24);
    std::vector<int> outputs = MakeComms(CHNUM, 25);
    InitComms(inputs, outputs);

    TPort<int> tport(CHNUM);
    std::thread t1(PinReader, std::ref(tport));
    std::thread t2(PinWriter, std::ref(tport));

    t1.join();
    t2.join();
    return EXIT_SUCCESS;
}
