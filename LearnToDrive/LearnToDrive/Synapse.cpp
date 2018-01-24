
#include "Synapse.h"

Synapse::Synapse(Neuron *start, Neuron *end, double weight)
{
	Start = start;
	End = end;
	Weight = weight;
	Value = 0;
}

Synapse::~Synapse()
{
	if (Start) { delete Start; }
	if (End) { delete End; }
	Start = 0;
	End = 0;
}

void Synapse::Update()
{
	Value = Start->Value;
	End->Update();
}

void Synapse::Draw(System::Windows::Forms::PaintEventArgs^ e)
{
	System::Drawing::Graphics^ g = e->Graphics;

	System::Drawing::SolidBrush^ MyBrush =
		gcnew System::Drawing::SolidBrush(System::Drawing::Color::FromArgb(0, 255, 0));
	System::Drawing::Color ColourA;
	System::Drawing::Color Colour;
	if (End->ID == 2)
	{
		ColourA = System::Drawing::Color::FromArgb(static_cast<int>(Value * 255), 0, 255, 0);
		Colour = System::Drawing::Color::FromArgb(static_cast<int>(255), 0, 255, 0);
	}
	else if (Start->ID == 0)
	{
		ColourA = System::Drawing::Color::FromArgb(static_cast<int>(Value * 255), 255, 0, 0);
		Colour = System::Drawing::Color::FromArgb(static_cast<int>(255), 255, 0, 0);
	}
	else
	{
		ColourA = System::Drawing::Color::FromArgb(static_cast<int>(Value * 255), 255, 255, 0);
		Colour = System::Drawing::Color::FromArgb(static_cast<int>(255), 255, 255, 0);
	}
	System::Drawing::Pen^ MyPen =
		gcnew System::Drawing::Pen(ColourA, 3);
	System::Drawing::Pen^ MyPenBlack =
		gcnew System::Drawing::Pen(System::Drawing::Color::Black, 3);
	System::Drawing::Pen^ MyPenOutline =
		gcnew System::Drawing::Pen(Colour, 5);

	g->DrawLine(MyPenOutline, System::Drawing::Point(Start->X, Start->Y), System::Drawing::Point(End->X, End->Y));
	g->DrawLine(MyPenBlack, System::Drawing::Point(Start->X, Start->Y), System::Drawing::Point(End->X, End->Y));
	g->DrawLine(MyPen, System::Drawing::Point(Start->X, Start->Y), System::Drawing::Point(End->X, End->Y));
}