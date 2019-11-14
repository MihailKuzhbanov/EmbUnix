#include "pinManagment.h"

const int CHNUM = 3;
const int HIGHTIME = 10;
const int LOWTIME = 10;

int main()
{
  OnStart();
  std::vector<int> inputs = MakeComms(CHNUM, 23);
  std::vector<int> outputs = MakeComms(CHNUM, 27);
  InitComms(inputs, outputs);
  RESOURCE1_init__();
  TPort<int> tport(CHNUM);

  std::thread t1(RESOURCE1_run__, std::ref(tport));
  std::thread t2(FlipFlopPins, std::ref(tport));
  t1.join();
  t2.join();
  return EXIT_SUCCESS;
}
