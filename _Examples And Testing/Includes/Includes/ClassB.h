
class ClassB;

#ifndef _CLASSB_
#define _CLASSB_

#include "ClassA.h"
//#include "Globals.h"

class ClassB
{
private:
	ClassA *ptr;
	//ClassA cpy;

public:
	ClassB();
	~ClassB();
	void foo();
};

#endif
