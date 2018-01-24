
class ClassA;

#ifndef _CLASSA_
#define _CLASSA_

#include "Globals.h"
#include "ClassB.h"

class ClassA
{
private:
	ClassB *ptr;

public:
	ClassA();
	~ClassA();
	void foo();
};

#endif
