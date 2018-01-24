// Rotations in 3 Dimensions Problem.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;

struct Vector3
{
	double X = 0;
	double Y = 0;
	double Z = 0;
	Vector3() { X = 0; Y = 0; Z = 0; }
	Vector3(double x, double y, double z) { X = x; Y = y; Z = z; }
};

void GetPosFromInput(Vector3 &Position, Vector3 &AxisOfRotation, double &RotationAngle)
{
	string In;
	getline(cin, In);
	In.append(" ");

	int Switch = 0;
	string Accumulator = "";
	for (int i = 0; i < In.length(); i++)
	{
		if (In[i] == ' ')
		{
			switch (Switch)
			{
			case 0:
				Position.X = stod(Accumulator);
			case 1:
				Position.Y = stod(Accumulator);
			case 2:
				Position.Z = stod(Accumulator);
			case 3:
				AxisOfRotation.X = stod(Accumulator);
			case 4:
				AxisOfRotation.Y = stod(Accumulator);
			case 5:
				AxisOfRotation.Z = stod(Accumulator);
			case 6:
				RotationAngle = stod(Accumulator);
			}
			Accumulator = "";
			Switch++;
		}
		else
		{
			Accumulator.append(&In[i]);
		}
	}
}

void main()
{
	Vector3 Position;
	Vector3 NewPosition;
	Vector3 AxisOfRotation;
	double RotationAngle;
	GetPosFromInput(Position, AxisOfRotation, RotationAngle);
	
	

	//cout << "{ " << AxisOfRotation.X << ", " << AxisOfRotation.Y << ", " << AxisOfRotation.Z << " }\n";

	string Wait;
	getline(cin, Wait);
}

