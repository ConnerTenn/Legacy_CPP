// Collision_Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<vector>
#include<iostream>
using namespace std;

struct Pos
{
	float x;
	float y;
};

struct Line
{
	float a;
	float b;
	float c;
	//Pos Pos1;
	//Pos Pos2;
};

bool Collide(Line Line1, Line Line2)
{
	return true;
}

Pos CollidePoint(Line Line1, Line Line2)
{
	float X;
	float Y;
	Y = (Line1.a*Line2.c - Line2.a*Line1.c) / (Line1.a*Line2.b - Line2.a*Line1.b);
	X = (-(Line1.b*Y - Line1.c)) / Line1.a;
	if (Line1.a == 0)
	{
		X = (-(Line2.b*Y - Line2.c)) / Line2.a;
	}
	if ((Line1.a*Line2.b - Line2.a*Line1.b) == 0 && (Line1.a*Line2.c - Line2.a*Line1.c) == 0)
	{
		//Same Line
		cout << endl << "Same Line" << endl;
	}
	else if ((Line1.a*Line2.b - Line2.a*Line1.b) == 0)
	{
		//parallel
		cout << endl << "Parallel Lines" << endl;
	}
	return{ X, Y };
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

	float a = -(y2 - y1);
	float b = (x2 - x1);
	float c = a*x1 + b*y1;
	Line Line1 = { a, b, c };

	cout << endl << "X1:";
	cin >> x1;
	cout << "Y1:";
	cin >> y1;
	cout << "X2:";
	cin >> x2;
	cout << "Y2:";
	cin >> y2;

	a = -(y2 - y1);
	b = (x2 - x1);
	c = a*x1 + b*y1;
	Line Line2 = { a, b, c };
	cout << endl << "Line1: A:" << Line1.a << " * X + " << Line1.b << " * Y = " << Line1.c << endl;
	cout << "Line2: A:" << Line2.a << " * X + " << Line2.b << " * Y = " << Line2.c << endl << endl;
	cout << endl << "Point Of Intersection: (" << CollidePoint(Line1, Line2).x << ", " << CollidePoint(Line1, Line2).y << ")" << endl;
	/*
	if (Collide(Line1, Line2))
	{
		cout << "X:" << CollidePoint(Line1, Line2).x << " Y:" << CollidePoint(Line1, Line2).y << endl;
	}
	else
	{
		cout << "No Collision" << endl;
	}*/
	int q;
	cin >> q;
	return 0;
}



