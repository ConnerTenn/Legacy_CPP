// Mouse Journey.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <time.h>
#include <vector>

using namespace std;

const int GridSize = 100;

struct Pos
{
	Pos(unsigned int InX, unsigned int InY)
	{
		X = InX;
		Y = InY;
	}
	Pos(unsigned int In[2])
	{
		X = In[0];
		Y = In[1];
	}
	Pos()
	{
		X = 0;
		Y = 0;
	}
	unsigned int X = 1;
	unsigned int Y = 1;
};

Pos GetPosFromInput()
{
	string In;
	getline(cin, In);
	In.append(" ");

	Pos Out;
	int Switch = 0;
	string Accumulator = "";
	for (int i = 0; i < In.length(); i++)
	{
		if (In[i] == ' ')
		{
			switch (Switch)
			{
			case 0:
				Out.X = stoi(Accumulator);
			case 1:
				Out.Y = stoi(Accumulator);
			}
			Accumulator = "";
			Switch++;
		}
		else
		{
			Accumulator.append(&In[i]);
		}
	}
	return Out;
}

bool ValidSquare(string Data, vector<string> AdjacentDataList)
{
	if (Data == "I" || Data == "E") { return false; }
	bool Out = true;
	for (string AdjacentData : AdjacentDataList)
	{
		if (AdjacentData == "I") { return false; }
		if (AdjacentData.length() == Data.length())
		{
			Out = true;
		}
		else if (AdjacentData.length() < Data.length())
		{
			size_t Find = Data.find(AdjacentData);
			if (Find != string::npos)
			{
				return false;
			}
			else
			{
				Out = true;
			}
		}
		else if (AdjacentData.length() > Data.length())
		{
			size_t Find = AdjacentData.find(Data);
			if (Find != string::npos)
			{
				return false;
			}
			else
			{
				Out = true;
			}
		}
	}
	return Out;
}

bool EqualGrid(vector<string> Grid1[GridSize][GridSize], vector<string> Grid2[GridSize][GridSize])
{
	bool Out = true;

	for (int Y = 0; Y < GridSize; Y++)
	{
		for (int X = 0; X < GridSize; X++)
		{
			if (Grid1[X][Y] != Grid2[X][Y]) { Out = false; }
		}
	}
	return Out;
}

void main()
{
	Pos EndPos = GetPosFromInput();
	vector<string> Grid[GridSize][GridSize];
	vector<string> GridCpy[GridSize][GridSize];
	Grid[0][0] = { "S" }; Grid[EndPos.X - 1][EndPos.Y - 1] = { "E" };

	//time_t Time1;
	//time_t Time2;

	//time(&Time1);
	{
		string In;
		getline(cin, In);
		int NumInvalidPos = stoi(In);
		for (int i = 0; i < NumInvalidPos; i++)
		{
			Pos pos = GetPosFromInput();
			Grid[pos.X - 1][pos.Y - 1].push_back("I");
		}
	}
	//time(&Time2);
	while (!EqualGrid(Grid, GridCpy))
	{
		for (int Y = 0; Y < GridSize; Y++)
		{
			for (int X = 0; X < GridSize; X++)
			{
				GridCpy[X][Y] = Grid[X][Y];
			}
		}
		for (int Y = 0; Y < EndPos.Y; Y++)
		{
			for (int X = 0; X < EndPos.X; X++)
			{
				for (string Data : Grid[X][Y])
				{
					if (Grid[X][Y][0] == "E") { Data = "E"; }
					if (Y > 0)
					{
						if (ValidSquare(Data, Grid[X][Y - 1]))//Up 
						{
							Grid[X][Y - 1].push_back(Data + "U");
						}
					}
					if (X < EndPos.X - 1)
					{
						if (ValidSquare(Data, Grid[X + 1][Y]))//Right
						{
							Grid[X + 1][Y].push_back(Data + "R");
						}
					}
					if (Y < EndPos.Y - 1)
					{
						if (ValidSquare(Data, Grid[X][Y + 1]))//Down				
						{
							Grid[X][Y + 1].push_back(Data + "D");
						}
					}
					if (X > 0)
					{
						if (ValidSquare(Data, Grid[X - 1][Y]))//Left				
						{
							Grid[X - 1][Y].push_back(Data + "L");
						}
					}
				}//X
			}//Y
		}
	}//Repeat
	
	cout << "Possible Paths: " << Grid[EndPos.X - 1][EndPos.Y - 1].size() - 1 << "\n";

	//cout << "{ " << EndPos.X << ", " << EndPos.Y << " }\n";
	//cout << "Time: " << Time2 - Time1 << "ms\n";

	string a;
	getline(cin, a);
}

