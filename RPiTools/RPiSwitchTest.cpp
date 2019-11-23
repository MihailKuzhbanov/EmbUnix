#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

using namespace std;

const int baseTime = 2;
vector<int> pinCom = { 21, 22, 23, 24, 25 };
vector<thread> threads;
mutex mtx;

void PinSwitch(int pin, int time)
{
	lock_guard<mutex> lock(mtx);
	digitalWrite(pin, HIGH);
	delay(time);
	digitalWrite(pin, LOW);
	lock_guard<mutex> unlock(mtx);
}

int main()
{
	cout << "RPi switch test\n";
	if (wiringPiSetup() == -1) exit(1);
	if (argc > 1) baseTime = *argv[1] - '0';

	while(true)
	{
		for (int el : pinCom)
		{
			pinMode(el, OUTPUT);
			thread simpleThread(PinSwitch, el, baseTime);
			threads.emplace_back(move(simpleThread));
			delay(baseTime / 2);
		}
		for (auto& thr : threads) thr.join();
	}
	return 0;
}
