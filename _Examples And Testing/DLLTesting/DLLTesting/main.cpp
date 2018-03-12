
#include <iostream>
#include <string>
#include <Windows.h>
#include "Include\Header.h"



void main()
{
	HMODULE hDLL = ::LoadLibrary(std::string("Object1.dll").c_str());

	int (*foo)(int);
	if (hDLL)
	{
		foo = (int (*)(int))::GetProcAddress(hDLL, "Foo1");
		if (foo)
		{
			std::cout << "foo(1):" << foo(5) << "\n";
		}
		else
		{
			std::cout << "Error Loading Functio:" << GetLastError() << "\n";
		}
	}
	else
	{
		std::cout << "Error Loading Library\n";
	}

	std::string out = "Press Enter To Continue:"; std::cout << out; std::getline(std::cin, out);
}

