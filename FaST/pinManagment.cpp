#include "pinManagment.h"

void OnStart() {
  printf("RPi command test\n");
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

void AutoComms(int cntIn, int startIn, int cntOut, int startOut) {
  InitComms(MakeComms(cntIn, startIn), MakeComms(cntOut, startOut));
}

void SetComms(std::vector<int> comms, int level) {
  for (auto pin : comms) digitalWrite(pin, level);
}

void SetComms(std::vector<int> comms, std::vector<int> level) {
  int size = min(comms.size(), level.size());
  for (int i = 0; i < size; i++) digitalWrite(comms[i], level[i]);
}

void SetComms(std::vector<int> comms, int level, int delay) {
  for (auto pin : comms) {
    digitalWrite(pin, level);
    usleep(delay);
  }
}

std::vector<int> GetComms(std::vector<int> comms) {
  std::vector<int> result;
  for (auto pin : comms) result.push_back(digitalRead(pin));
  return result;
}

void FlipFlopPins(std::vector<int> outputs, int timeUp, int timeDown) {
    while(true) {
      SetComms(outputs, HIGH);
      usleep(timeUp);
      SetComms(outputs, LOW);
      usleep(timeDown);
    }
}

void FlipFlopPins(std::vector<int>& outputs)
{
  while(true) {
    SetComms(outputs, HIGH);
    usleep(10);
    SetComms(outputs, LOW);
    usleep(10);
  }
}

