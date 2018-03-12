#pragma once

#include <vector>
#include <string>
#include <Windows.h>

#include "Globals.h"

using namespace System;


class Engine
{
public:
	bool Run = true;

	Engine()
	{

	}
	~Engine()
	{

	}
	void Update()
	{
		System::Console::WriteLine("Update\n");
	}

	void Render(System::Windows::Forms::PaintEventArgs ^ e, int Width, int Height)
	{
		Console::WriteLine("Begin Draw\n");
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
	}

};