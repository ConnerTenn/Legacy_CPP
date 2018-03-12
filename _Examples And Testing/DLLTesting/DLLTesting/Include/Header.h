

#ifndef _HEADER_
#define _HEADER_

#define DllExport   __declspec( dllexport ) 


template<typename T>
T AddTB(T a, T b);

DllExport int AddT(int a, int b);
DllExport double AddT(double a, double b);

int Add(int a, int b);

class Object
{
public:
	int A;

	Object();

	Object(int a);
};


#endif

