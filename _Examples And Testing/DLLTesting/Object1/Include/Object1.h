
#ifndef _OBJECT1_
#define _OBJECT1_

#define DllExport   __declspec( dllexport ) 
#define DllImport   __declspec( dllimport )

#include <Header.h>


extern "C" DllExport int Foo1(int val);

class Object1 : public Object
{
public:
	int B;

	Object1();

	Object1(int a, int b);
};

#endif
