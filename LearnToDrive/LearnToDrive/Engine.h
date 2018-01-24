#pragma once

#include <vector>
#include <string>
#include <Windows.h>

#include "Car.h"
#include "Track.h"
#include "Types.h"

using namespace System;

class Engine
{
public:
	bool Run = true;

	Car car;
	Track track;
	Engine()
	{

	}
	~Engine()
	{

	}
	void Update()
	{
		//System::Console::WriteLine("Update\n");
		//Segment segment0( 0,  0, 10, 10);
		//Segment segment1(10,  0,  0, 10);
		//Line line0 = segment0.ToLine();
		//Line line1 = segment1.ToLine();

		//System::Console::WriteLine("A:{0} B:{1} C:{2}", line0.A, line0.B, line0.C);
		//Point point0 = segment0.Intersection(segment1);
		//System::Console::WriteLine("X:{0} Y:{1} Defined:{2}", point0.X, point0.Y, point0.Defined);

		car.Pos.X = 140; car.Pos.Y = 140;
		car.Update(&track);
	}

	void Render(System::Windows::Forms::PaintEventArgs ^ e, int Width, int Height)
	{
		//Console::WriteLine("Begin Draw\n");
		Drawing::Graphics^ g = e->Graphics;

		Drawing::SolidBrush^ myBrush =
			gcnew Drawing::SolidBrush(Drawing::Color::FromArgb(0, 0, 255));
		//g->FillRectangle(myBrush, LearnToDrive::Rectangle(1, 1, 10, 10));
		for (int I = 0; I < Width; I += 100)
		{
			for (int Q = 0; Q < Height; Q += 100)
			{
				g->FillRectangle(myBrush, Drawing::Rectangle::Rectangle(I, Q, 10, 10));
			}
		}

		track.Draw(e);

		car.Draw(e);

		//car2.Pos[0] = 400; car2.Pos[1] = 200;
		//car2.Update();
		//car2.Draw(e);
	}

	void Crossover()
	{
		srand(static_cast<unsigned int>(time(NULL)));
		int Selection = rand() % 2;

	}

};
