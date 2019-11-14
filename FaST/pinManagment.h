#include "wiringPi.h"

void OnStart();
std::vector<int> MakeComms(int cntCom, int startPin);
void InitComms(std::vector<int> inputs, std::vector<int> outputs);
void AutoComms(int cntIn, int startIn, int cntOut, int startOut);
void SetComms(std::vector<int> comms, int level);
void SetComms(std::vector<int> comms, std::vector<int> level);
void SetComms(std::vector<int> comms, int level, int delay);
std::vector<int> GetComms(std::vector<int> comms);
void FlipFlopPins(std::vector<int> outputs, int timeUp, int timeDown);
void FlipFlopPins(std::vector<int>& outputs);
