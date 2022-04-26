
#include <stdio.h>
//#include <emmintrin.h>
//#include <immintrin.h>
#include <intrin.h>
#include <stdint.h>
#include <time.h>
#include <chrono>
#include <iostream>
using namespace std;

void time_measure(void func(), const char* msg = "", size_t trials = 10) {
	auto t1{ std::chrono::system_clock::now() };

	for (size_t i = 0; i < trials; i++)
	{
		func();
	}
	auto t2{ std::chrono::system_clock::now() };

	double duration = (std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count()) / trials;


	printf("duration: %.9f\n", duration);
	//printf("Time measured[func: %-20s trials: %d]:%.9f\n\n",
	//	msg,
	//	trials,
	//	duration
	//);

}