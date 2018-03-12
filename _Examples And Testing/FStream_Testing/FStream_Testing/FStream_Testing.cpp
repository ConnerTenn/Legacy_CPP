// FStream_Testing.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

void OutputToFiles()
{
	fstream myfile;
	myfile.open("TEST.txt", ios::app);//
	for (int i = 0; i < 10; i++)
	{
		myfile << "Writing This To A File.\n";
	}
	myfile.close();
}

void InputFromFiles()
{
	string line;
	fstream myfile("TEST.txt");
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			cout << line << '\n';
		}
		myfile.close();
	}

	else cout << "Unable to open file";
}

void PositionOperators()
{
	streampos begin, end;
	ifstream myfile("example.bin", ios::binary);
	begin = myfile.tellg();
	myfile.seekg(0, ios::end);
	end = myfile.tellg();
	myfile.close();
	cout << "size is: " << (end - begin) << " bytes.\n";
}

void PositionOperators2()
{
	streampos it;
	ifstream myfile("TEST.txt");
	myfile.seekg(0,ios::end);
	it = myfile.tellg();
	myfile.seekg(0, ios::beg);
	cout << "it: " << it << "\n";
	string in;

	while (myfile >> in)
	{
		cout << in;
	}
	
	//myfile.seekg(0, ios::end);
	//end = myfile.tellg();
	myfile.close();
	//cout << "size is: " << (end - begin) << " bytes.\n";
}

void main()
{
	OutputToFiles();
	//InputFromFiles();
	PositionOperators2();

	cout << "\n::DONE::\n";
	string OUT;
	getline(cin, OUT);
}

