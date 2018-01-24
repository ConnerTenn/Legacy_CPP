#ifndef _MAP_CUSTOM_
#define _MAP_CUSTOM_

#include <vector>

//using namespace std;

float Map(std::vector<float> InRange = { 0, 100 }, std::vector<float> NextRange = { 0, 100 }, float Value = 50)
{
	float m = (NextRange[1] - NextRange[0]) / (InRange[1] - InRange[0]);
	float b = NextRange[0] - (m * InRange[0]);
	return m * Value + b;
}

#endif


