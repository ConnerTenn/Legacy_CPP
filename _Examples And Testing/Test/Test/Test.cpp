// Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>
using namespace std;

void main()
{
	cout << "Number: ";
	string In;
	getline(cin, In);
	int Num = stoi(In);
	if (2 == 2 == 2)
	{
		cout << "Yes\n";
	}
	else
	{
		cout << "No\n";
	}

	getline(cin, In);
}

