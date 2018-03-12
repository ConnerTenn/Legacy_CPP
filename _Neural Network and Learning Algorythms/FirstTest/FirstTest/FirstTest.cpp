// FirstTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

#include "Brain.h"

void main()
{
	Brain brain;
	brain.PossibleActions = { "A", "B", "C" };

	brain.CurrentInputList.push_back(0);

	bool Done = false;
	while (!Done)
	{
		std::cout << brain.CurrentAction << "\nInput:";
		std::string in;
		std::getline(std::cin, in);
		if (in == "q") { Done = false; }
		else { brain.CurrentInputList[0] = std::stod(in); }
		brain.Update();
	}
}

