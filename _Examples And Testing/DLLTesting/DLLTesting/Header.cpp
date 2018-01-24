
#include "Include\Header.h"

template<typename T>
T AddTB(T a, T b)
{
	return a + b;
}

DllExport int AddT(int a, int b) { return AddTB(a, b); }
DllExport double AddT(double a, double b) { return AddTB(a, b); }

int Add(int a, int b)
{
	return a + b;
}

Object::Object()
{
	A = 0;
}

Object::Object(int a)
{
	A = a;
}

