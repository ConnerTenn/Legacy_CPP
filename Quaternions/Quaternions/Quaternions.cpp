// Quaternions.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include "Quaternion.h"

using namespace std;

string PrintQuaternion(Quaternion In)
{
	string Out = "";
	Out += to_string(In.Num[0]) + "+" + to_string(In.Num[1]) + "i+" + to_string(In.Num[2]) + "j+" + to_string(In.Num[3]) + "k";
	return Out;
}

void main()
{
	Quaternion Num0(0, 1, 1, 1);
	Quaternion Num1(0, 1, 0, 0);
	Quaternion Num2(0, 0, 0, 1);

	Quaternion Num3 = Num0 * Num1;
	//cout << PrintQuaternion(Num0) << "\n * \n";
	//cout << PrintQuaternion(Num1) << "\n = \n";
	cout << PrintQuaternion(Num3) << "\n";

	string Out;
	getline(cin, Out);
}

