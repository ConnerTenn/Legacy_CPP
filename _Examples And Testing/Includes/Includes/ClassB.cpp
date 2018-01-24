
#include "stdafx.h"
#include "ClassB.h"

ClassB::ClassB()
{
	ptr->foo();
}

ClassB::~ClassB()
{
	delete(ptr);
	//if (ptr) { delete(ptr); }
	ptr = 0;
}

void ClassB::foo()
{

}

