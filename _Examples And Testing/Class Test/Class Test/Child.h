
#ifndef _CHILD_
#define _CHILD_

#include <iostream>

#include "Parent.h"

using namespace std;

class Child : public Parent
{
public:
	int B = 0;
	Child()
		:Parent(50)
	{
		B = 5;
	}
	Child(int b)
		:Parent(50)
	{
		B = b;
	}
};

#endif


