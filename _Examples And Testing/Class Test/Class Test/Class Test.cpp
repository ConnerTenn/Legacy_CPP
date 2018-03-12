// Class Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>

#include "Child.h"
#include "Parent.h"

using namespace std;



void main()
{
	Parent _Parent;
	_Parent.Run();
	_Parent.A = 100;

	Child _Child;
	_Child.Run();
	cout << "A:" << _Child.A << "\n";

	Parent _Parent2 = _Parent;
	cout << "A:" << _Parent2.A << "\n";

	string END;
	getline(cin, END);
}

