// HeaderFiles.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include "Custom.h"

using namespace std;
//using namespace System;

void main()
{
	int a = 1;
	int b = 2;
	cout << a << "+" << b << "=" << add(a, b) << endl;
	int q;
	cout << "Bool:\t\t" << sizeof(bool) << " Bytes" << endl;
	cout << endl;
	cout << "Press [Enter] To Hear a \"Beep\"";
	string i;
	getline(cin, i);
	cout << "BEEP!\a" << endl;

	double e = (double)5 / 2;
	double f = 2.5;
	switch (IsEqual(e, f))
	{
		case true:
			cout << e << "=" << f << endl;
				break;
		case false:
			cout << e << "!=" << f << endl;
	}
	

	end();
	//return 0;
	
}

 