
#include "Include\Object1.h"

int Foo1(int val) { return AddT(val,5); }

Object1::Object1() :
	Object(0)
{
	B = 0;
}

Object1::Object1(int a, int b) :
	Object(a)
{
	B = b;
}