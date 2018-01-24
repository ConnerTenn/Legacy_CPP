
#ifndef _PARENT_
#define _PARENT_

#include <iostream>

#include "Child.h"

using namespace std;

class Parent
{
public:
	int A = 4;
	//static int CST = 80;
	Parent()
	{
		A = 10;
	}
	Parent(int a)
	{
		A = a;
	}
	void Run()
	{
		//A = 10;
		//Child _Child;
		//_Child.A;
		//getline(cin, "A: " + to_string(_Child.A));
		cout << "Flow::Parent.Run()\n";
	}
};

#endif


