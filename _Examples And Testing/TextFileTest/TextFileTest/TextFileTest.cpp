// TextFileTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;


int main()
{
	ofstream myfile;
	myfile.open("Data/example.txt");
	myfile << "Deaths:4\nPos:5,7\nAge:6";
	myfile.close();

	string line;
	string All;
	ifstream file("Data/example.txt");

	if (file.is_open())
	{
		while (getline(file, line))
		{
			All = All + line + "\n";
		}
		cout << "<File>\n" << All << "</File>\n\n";

		string Target = "Pos:";
		size_t found = All.find(Target);
		if (found != string::npos)
		{
			cout << "Pos:  " << All.substr(found + Target.length(), 3) << '\n';
		}

		file.close();
	}

	int a;
	cin >> a;
	return 0;
}

