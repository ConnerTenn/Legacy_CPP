// Collision_Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
using namespace std;

struct Pos
{
	float x;
	float y;
};

struct Line
{
	Pos Pos1;
	Pos Pos2;
};

bool Collide(Line Line1, Line Line2)
{
	return true;
}

Pos CollidePoint(Line Line1, Line Line2)
{
	float X;
	float Y;
	X = (((Line1.Pos1.x * Line1.Pos2.y - Line1.Pos1.y * Line1.Pos2.x) * (Line2.Pos1.x - Line2.Pos2.x)) - ((Line2.Pos1.x * Line2.Pos2.y - Line2.Pos1.y * Line2.Pos2.x) * (Line1.Pos1.x - Line1.Pos2.x)))
/ ((Line2.Pos1.x - Line2.Pos2.x) * (Line1.Pos1.x - Line1.Pos2.x) - (Line2.Pos1.y - Line2.Pos2.y) * (Line1.Pos1.y - Line1.Pos2.y));
	return {X, 0};
}

int main()
{
	float x1;
	float y1;
	float x2;
	float y2;

	cout << "X1:";
	cin >> x1;
	cout << "Y1:";
	cin >> y1;
	cout << "X2:";
	cin >> x2;
	cout << "Y2:";
	cin >> y2;

	Line Line1 = { { 10, 20 }, { 20, 20 } };

	cout << endl << "X1:";
	cin >> x1;
	cout << "Y1:";
	cin >> y1;
	cout << "X2:";
	cin >> x2;
	cout << "Y2:";
	cin >> y2;

	Line Line2 = { { 5, 30 }, { 15, 15 } };

	if (Collide(Line1, Line2))
	{
		cout << "X:" << CollidePoint(Line1, Line2).x << " Y:" << CollidePoint(Line1, Line2).y << endl;
	}
	else
	{
		cout << "No Collision" << endl;
	}
	int a;
	cin >> a;
	return 0;
}



