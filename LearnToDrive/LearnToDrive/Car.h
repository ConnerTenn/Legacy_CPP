#pragma once

#include "NeuralNetwork.h"
#include "Track.h"
//using namespace std;

class Car
{
public:
	NeuralNetwork _NeuralNetwork;

	//double Pos[2] = { 0, 0 };
	Point Pos = { 0, 0 };
	double Rotation = 0;
	//double Whiskers[5][2] = { { -0.78 * 50, -0.62 * 50 }, { -0.78 * 50, -0.62 * 50 }, { -0.51 * 50, -0.86 * 50 }, { 0 * 50, -1 * 50 }, { 0.51 * 50, -0.86 * 50 }, { 0.78 * 50, -0.62 * 50 } };
	/*double Whiskers[7][2] = 
	{ 
		{ sin(-(3.0 * (TAU/4.0)) / 4.0) * 50 , cos(-(3.0 * (TAU/4.0)) / 4.0) * 50 }, 
		{ sin(-(2.0 * (TAU/4.0)) / 4.0) * 60 , cos(-(2.0 * (TAU/4.0)) / 4.0) * 60 }, 
		{ sin(-(TAU/4.0) / 4.0) * 70 , cos(-(TAU/4.0) / 4.0) * 70 }, 
		{ sin(0) * 80 , cos(0) * 80 }, 
		{ sin( (TAU/4.0) / 4.0) * 70 , cos( (TAU/4.0) / 4.0) * 70 }, 
		{ sin( (2.0 * (TAU/4.0)) / 4.0) * 60 , cos( (2.0 * (TAU/4.0)) / 4.0) * 60 }, 
		{ sin( (3.0 * (TAU/4.0)) / 4.0) * 50 , cos( (3.0 * (TAU/4.0)) / 4.0) * 50 }, 
	};*/
	Segment Whiskers[7] = 
	{
		{ 0, 0, sin(-(3.0 * (TAU / 4.0)) / 4.0) * 50 , cos(-(3.0 * (TAU / 4.0)) / 4.0) * 50 },
		{ 0, 0, sin(-(2.0 * (TAU / 4.0)) / 4.0) * 60 , cos(-(2.0 * (TAU / 4.0)) / 4.0) * 60 },
		{ 0, 0, sin(-(TAU / 4.0) / 4.0) * 70 , cos(-(TAU / 4.0) / 4.0) * 70 },
		{ 0, 0, sin(0) * 80 , cos(0) * 80 },
		{ 0, 0, sin((TAU / 4.0) / 4.0) * 70 , cos((TAU / 4.0) / 4.0) * 70 },
		{ 0, 0, sin((2.0 * (TAU / 4.0)) / 4.0) * 60 , cos((2.0 * (TAU / 4.0)) / 4.0) * 60 },
		{ 0, 0, sin((3.0 * (TAU / 4.0)) / 4.0) * 50 , cos((3.0 * (TAU / 4.0)) / 4.0) * 50 }
	};

public:
	Car()
	{

	}
	~Car()
	{

	}
	void Update(Track *track)
	{
		//Loop through whiskers
		for (int I = 0; I < sizeof(Whiskers) / sizeof(Segment); I++)
		{
			Segment whisker = { Pos.X, Pos.Y, Whiskers[I].points[1].X, Whiskers[I].points[1].Y };
			//Loop through wall segments
			for (int Q = 0; Q < sizeof(track->Walls) / sizeof(Segment); Q++)
			{
				Segment TrackSegment = track->Walls[Q];
				Point Intersection = TrackSegment.Intersection(whisker);
				double Value = 0;
				if (Intersection.Defined)
				{
					Value = Pos.Distance(Intersection);
					//System::Console::WriteLine("Point: ({0},{1})", Intersection.X, Intersection.Y);
				}
				else
				{
					Value = 0;
				}
				_NeuralNetwork.NeuronList[I]->Value = Value;
				//System::Console::WriteLine("Value: {0}", Value);
			}
		}
		_NeuralNetwork.Update();
		//Pos[0] = 200; Pos[1] = 200;

		static float r = 0;
		//r += 0.01f;
		//Rotation = r; TAU / 8.0;
		Rotation += TAU / (2.0 * FrameRate);
	}
	void Draw(System::Windows::Forms::PaintEventArgs^ e)
	{
		System::Drawing::Graphics^ g = e->Graphics;

		System::Drawing::SolidBrush^ MyBrush =
			gcnew System::Drawing::SolidBrush(System::Drawing::Color::FromArgb(0, 255, 0));
		System::Drawing::Pen^ MyPen =
			gcnew System::Drawing::Pen(System::Drawing::Color::FromArgb(255, 0, 0), 2);
		System::Drawing::Pen^ MyPenWhiskers =
			gcnew System::Drawing::Pen(System::Drawing::Color::FromArgb(255, 255, 255), 1);

		//g->FillRectangle(MyBrush, LearnToDrive::Rectangle(1, 1, 10, 10));
		//g->FillRectangle(MyBrush, System::Drawing::Rectangle::Rectangle(Pos[0], Pos[1], 10, 10));
		//g->DrawLine(MyPen, System::Drawing::Point(0, 0), System::Drawing::Point(100, 100));
		Point a, b, c, d;
		System::Drawing::Point A, B, C, D;

		//A = XMTranslation( XMRotation( XMTranslation(A, -5, +10), Rotation), Pos[0], Pos[1]);
		//B = XMTranslation( XMRotation( XMTranslation(B, +5, +10), Rotation), Pos[0], Pos[1]);
		//C = XMTranslation( XMRotation( XMTranslation(C, +5, -10), Rotation), Pos[0], Pos[1]);
		//D = XMTranslation( XMRotation( XMTranslation(D, -5, -10), Rotation), Pos[0], Pos[1]);

		//A = XMTranslation(XMRotation(XMTranslation(A, -5, -10), Rotation), static_cast<int>(Pos[0]), static_cast<int>(Pos[1]));
		//B = XMTranslation(XMRotation(XMTranslation(B, +5, -10), Rotation), static_cast<int>(Pos[0]), static_cast<int>(Pos[1]));
		//C = XMTranslation(XMRotation(XMTranslation(C, +5, +10), Rotation), static_cast<int>(Pos[0]), static_cast<int>(Pos[1]));
		//D = XMTranslation(XMRotation(XMTranslation(D, -5, +10), Rotation), static_cast<int>(Pos[0]), static_cast<int>(Pos[1]));

		a = XMTranslation(XMRotation(XMTranslation(a, -5, -10), Rotation), Pos.X, Pos.Y);
		b = XMTranslation(XMRotation(XMTranslation(b, +5, -10), Rotation), Pos.X, Pos.Y);
		c = XMTranslation(XMRotation(XMTranslation(c, +5, +10), Rotation), Pos.X, Pos.Y);
		d = XMTranslation(XMRotation(XMTranslation(d, -5, +10), Rotation), Pos.X, Pos.Y);
		A.X = static_cast<int>(a.X); A.Y = static_cast<int>(a.Y);
		B.X = static_cast<int>(b.X); B.Y = static_cast<int>(b.Y);
		C.X = static_cast<int>(c.X); C.Y = static_cast<int>(c.Y);
		D.X = static_cast<int>(d.X); D.Y = static_cast<int>(d.Y);
		//System::Console::WriteLine("{0} {1} {2}", A.X, A.Y, round(1.234, 1));

		array<System::Drawing::Point>^ Points = { A, B, C, D };

		g->DrawPolygon(MyPen, Points);
		
		//g->DrawPolygon(MyPen, array<System::Drawing::Point>( {System::Drawing::Point(0, 0), System::Drawing::Point(20, 0), System::Drawing::Point(10, 10) }));

		//Points = { System::Drawing::Point(0, 0), System::Drawing::Point(10, 0), System::Drawing::Point(0, 10), System::Drawing::Point(0, 10) };
		
		for (int I = 0; I < sizeof(Whiskers) / sizeof(Segment); I++)
		{
			g->DrawLine(
				MyPenWhiskers,
				XMTranslation(System::Drawing::Point(0, 0), static_cast<int>(Pos.X), static_cast<int>(Pos.Y)),
				XMTranslation(XMRotation(System::Drawing::Point(static_cast<int>(Whiskers[I].points[1].X), static_cast<int>(Whiskers[I].points[1].Y)), Rotation), static_cast<int>(Pos.X), static_cast<int>(Pos.Y)));
		}
		//g->DrawLines(gcnew System::Drawing::Pen(System::Drawing::Color::FromArgb(255, 0, 0)), array<System::Drawing::Point>({ System::Drawing::Point(0, 0), System::Drawing::Point(100, 100) }));
	
		_NeuralNetwork.Draw(e);
	}
};
