
#include "stdafx.h"
#include "ClassA.h"

ClassA::ClassA()
{
	ptr->foo();
}

ClassA::~ClassA()
{
	delete(ptr);
	//if (ptr) { delete(ptr); }
	ptr = 0;
}

void ClassA::foo()
{

}

