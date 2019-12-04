#include <iostream>
#include <unistd.h>
#include <vector>

#include "resource1.h"

#include "./lib/C/iec_types.h"

#include "../libs/IEC.hpp"
#include "../libs/tb_port.hpp"

#include "logic.h"

const int ch(32);

IEC_TIME __CURRENT_TIME;

unsigned long long ticktime = 1;

int sleepTime(10);

//port >> output
template <typename T>
T * ReadPort(threadbone::TbPort<T> &tport) {
	T * output;
	output = new T[ch];
	tport.read(output);
	return output;
}

//input >> port
template <typename T>
void WritePort(threadbone::TbPort<T> &tport, T &input, int64_t wait) {
	tport.write(input, wait);
}


int main(int argc, char* argv[]) {

	threadbone::TbPort<int> writer;
	threadbone::TbPort<bool> reader;
	RESOURCE1_init__();
	writeLogic(1);
	if (argc > 1) writeLogic(atoi(argv[1]));
	printf("PLC initialized\n");

	while (true) {

		RESOURCE1_run__(ticktime);
		usleep(sleepTime);
	}

	return 0;
}
