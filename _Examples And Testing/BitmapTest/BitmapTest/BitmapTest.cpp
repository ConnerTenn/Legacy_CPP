// BitmapTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
using namespace std;


//Not Finished

void main()
{
	ifstream inFile;
	size_t size = 0;
	inFile.open("Data\\SecAPI", ios::in | ios::binary | ios::ate);

	if (inFile.is_open())
	{

		char* oData = 0;

		inFile.seekg(0, ios::end);
		size = inFile.tellg();
		inFile.seekg(0, ios::beg);

		oData = new char[size + 1];
		inFile.read(oData, size);
		oData[size] = '\0';
	}
}

