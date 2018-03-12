// Time Testing.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <chrono>
#include <string>
#include <math.h>

//using namespace std;

std::chrono::time_point<std::chrono::steady_clock> _Time1, _Time2;
long double _DeltaTime;

void main()
{
	long double o = 1.0000001;
	long double a = o;
	int b = 10000000000;

	_Time1 = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < b; ++i)
	{
		a = a * a;
	}

	_Time2 = std::chrono::high_resolution_clock::now();
	//Time in milliseconds
	_DeltaTime = std::chrono::duration_cast<std::chrono::nanoseconds>(_Time2 - _Time1).count() / 1000000.0;
	std::cout << "A:" << a << "  Time:" << _DeltaTime << "\n";
	
	a = o;

	_Time1 = std::chrono::high_resolution_clock::now();

	a = pow(a, pow(2.0, b));

	_Time2 = std::chrono::high_resolution_clock::now();
	_DeltaTime = std::chrono::duration_cast<std::chrono::nanoseconds>(_Time2 - _Time1).count() / 1000000.0;
	std::cout << "A:" << a << "  Time:" << _DeltaTime << "\n";

	std::string OUT;
	std::getline(std::cin, OUT);
}

