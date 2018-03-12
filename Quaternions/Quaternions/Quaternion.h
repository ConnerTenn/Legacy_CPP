#ifndef QUATERNION
#define QUATERNION

#include <vector>
using namespace std;

class Quaternion
{
public:
	double Num[4] = { 0.0, 0.0, 0.0, 0.0 };
public:
	Quaternion(double InNum[4]);
	Quaternion(double InNum0, double InNum1, double InNum2, double InNum3);

	double operator[](int Index);

	Quaternion operator+(Quaternion In);
	Quaternion operator-(Quaternion In);
	Quaternion operator*(Quaternion In);
	Quaternion operator/(Quaternion In);
	bool operator==(Quaternion In);
};

#endif


