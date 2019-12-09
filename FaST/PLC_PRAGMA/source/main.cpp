#include <iostream>
#include <unistd.h>
#include <vector>
#include <string.h>

#include "resource1.h"

#include "./lib/C/iec_types.h"

#include "../libs/IEC.hpp"
#include "../libs/tb_port.hpp"

#include "logic.h"

IEC_TIME __CURRENT_TIME;

const int ch(4);
const int wait(9);
const int sleepTime(1000000);
unsigned long long ticktime = 1;

//Print array
void ShowData(int * data, int n, std::string msg) {
	std::cout << msg;
	for (int i = 0; i < n; i++) {
		std::cout << " " << *(data+i);
	}
	std::cout << std::endl;
}

//Return vector for use in TbPort
template <typename T>
std::vector<T> ConvertDataToVector(T * data, int n) {
	std::vector<T> result;
	result.reserve(n);
	for (int i = 0; i < n; i++) {
		result.push_back(*(data + i));
	}
	return result;
}

//Return array for use in GetData/SetData functions
template <typename T>
T * ConvertVectorToData(std::vector<T> data, int n) {
	T * result = new T[n];
	for (int i = 0; i < n; i++) {
		*(result + i) = data.at(i);
	}
	return result;
}

//Read data from port and send to plc logic
template <typename T>
void ReadPort(threadbone::TbPort<T> &prt, int n) {
	std::vector<T> vec;
	vec.reserve(n);
	prt.read(vec);
	T * arr = ConvertVectorToData(vec, n);
	SetData(arr, n);
}

//Read data from plc logic and send to port
template <typename T>
void WritePort(threadbone::TbPort<T> &prt, int n, int w) {
	T * data = GetData(n);
	std::vector<T> dataVec = ConvertDataToVector(data, ch);
	prt.write(dataVec, w);
}

int main(int argc, char* argv[]) {

	int * data = new int[ch];
	threadbone::TbPort<int> transfer(ch);

	RESOURCE1_init__();
	writeLogic(1);
	
	if (argc > 1) writeLogic(atoi(argv[1]));
	std::cout << "PLC initialized\n";

	while (true) {

		data = GetData(ch);
		ShowData(data, ch, "Original data: ");

		RESOURCE1_run__(ticktime);
		data = GetData(ch);
		ShowData(data, ch, "After logic: ");

		usleep(sleepTime);

		//manual debug
		std::cout << "_____WHILE___LOOP___STARTS___HERE_____" << std::endl;
		int * data;
		data = GetData(ch);
		ShowData(data, ch, "Data recieved: ");
		for (int i = 0; i < ch; i++) {
			*(data+i) = i;
		}
		ShowData(data, ch, "Data changed: ");
		SetData(data, ch);
		for (int i = 0; i < ch; i++) {
			*(data+i) = 0;
		}
		ShowData(data, ch, "Data flushed: ");
		data = GetData(ch);
		ShowData(data, ch, "Data recieved: ");
		RESOURCE1_run__(ticktime);
		data = GetData(ch);
		ShowData(data, ch, "Data recieved: ");
		usleep(sleepTime);
	}

	return 0;
}
