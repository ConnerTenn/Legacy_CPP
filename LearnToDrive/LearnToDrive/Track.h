#pragma once

#include "Globals.h"

/*struct Point
{
	int pos[2];
};

struct Segment
{
	Point points[2];
	Segment(int a, int b, int c, int d)
	{
		points[0].pos[0] = a;
		points[0].pos[1] = b;

		points[1].pos[0] = c;
		points[1].pos[1] = d;
	}
	Segment()
	{
		points[0].pos[0] = 0;
		points[0].pos[1] = 0;
		
		points[1].pos[0] = 0;
		points[1].pos[1] = 0;
	}
};*/

class Track
{
public:
	//segments, Points, Value

	//Segment(,,,),
	Segment Walls[6] =
	{
		//Inner
		Segment(200,300,300,400),
		Segment(300,400,900,400),
		//Outer
		//Segment(200,100,100,200),
		Segment(200,100,100,200),
		Segment(100,200,100,400),
		Segment(100,400,200,500),
		Segment(200,500,1000,500),
	};
	/*int Walls[2][2] =
	{
		{ 0, 0 },
		{ 0, 0 },
	};*/
public:
	void Draw(System::Windows::Forms::PaintEventArgs^ e)
	{
		System::Drawing::Graphics^ g = e->Graphics;

		System::Drawing::SolidBrush^ MyBrush =
			gcnew System::Drawing::SolidBrush(System::Drawing::Color::FromArgb(0, 255, 0));
		System::Drawing::Pen^ MyPen =
			gcnew System::Drawing::Pen(System::Drawing::Color::FromArgb(0, 255, 0), 2);

		int x1, y1, x2, y2;
		for (int I = 0; I < sizeof(Walls) / sizeof(Segment); I++)
		{
			x1 = static_cast<int>(Walls[I].points[0].X);
			y1 = static_cast<int>(Walls[I].points[0].Y);
			x2 = static_cast<int>(Walls[I].points[1].X);
			y2 = static_cast<int>(Walls[I].points[1].Y);
			g->DrawLine(MyPen, System::Drawing::Point(x1, y1), System::Drawing::Point(x2, y2));
		}
	}
};

