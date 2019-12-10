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
	std::vector<T> vec(n,0);
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

	//uncomment for debug section
	//int * data = new int[ch];
	//threadbone::TbPort<int> transfer(ch);

	threadbone::TbPort<int> input(ch);
	threadbone::TbPort<int> output(ch);

	std::vector<int> inputData(ch, 0);
	std::vector<int> outputData(ch, 0);

	RESOURCE1_init__();
	
	writeLogic((argc > 1) ? atoi(argv[1]) : 1);
	std::cout << "PLC initialized\n";

	while (true) {

		ReadPort(input, ch);
		RESOURCE1_run__(ticktime);
		WritePort(output, ch, wait);
		usleep(sleepTime);

		/////////////////////////

		//Set logic data manually and grab result to vector via TbPort
		/*
		std::vector<int> v{1,2,3,4};

		SetData(ConvertVectorToData(v, ch), ch);
		ShowData(ConvertVectorToData(v, ch), ch, "Vector data: ");

		RESOURCE1_run__(ticktime);

		WritePort(transfer, ch, wait);
		transfer.read(v);
		ShowData(ConvertVectorToData(v, ch), ch, "After logic: ");

		usleep(sleepTime);
		*/
		/////////////////////////

		//Send vector to logic example
		/*
		std::vector<int> v{2,7,1,8};
		data = GetData(ch);
		ShowData(data, ch, "Original data: ");

		transfer.write(v,wait);
		ReadPort(transfer, ch);
		data = GetData(ch);
		ShowData(data, ch, "Wrotten data: ");

		RESOURCE1_run__(ticktime);

		data = GetData(ch);
		ShowData(data, ch, "After logic: ");

		usleep(sleepTime);
		*/
		/////////////////////////

		//Get and Set logic data example
		/*
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
		*/
		/////////////////////////
	}

	return 0;
}
