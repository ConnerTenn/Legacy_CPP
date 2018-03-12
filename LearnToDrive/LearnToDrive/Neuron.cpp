
#include "Neuron.h"

Neuron::Neuron()
{

}

Neuron::Neuron(int x, int y, unsigned int id)//, Synapse *input, Synapse *output)
{
	X = x; Y = y; ID = id;
	Value = 0;
	//Input.push_back(input);
	//Output.push_back(output);
}

Neuron::~Neuron()
{
	//if (Input) { delete(Input); }
	//if (Output) { delete(Output); }
	//Input = 0;
	//Output = 0;
}

void Neuron::Update()
{
	if (ID != 0)
	{
		Value = 0;
		double SumWeights = 0;
		for (Synapse *synapse : Input)
		{
			SumWeights += synapse->Weight;
		}
		for (Synapse *synapse : Input)
		{
			//Value += Synapse Value * calculated Weight
			Value += synapse->Value * (1.0 / ((SumWeights - synapse->Weight) / synapse->Weight + 1));
		}
	}
	if (ID != 2)
	{
		for (Synapse *synapse : Output)
		{
			synapse->Update();
		}
	}
}

void Neuron::Draw(System::Windows::Forms::PaintEventArgs^ e)
{
	System::Drawing::Graphics^ g = e->Graphics;

	System::Drawing::SolidBrush^ MyBrush =
		gcnew System::Drawing::SolidBrush(System::Drawing::Color::FromArgb(static_cast<int>(Value * 255), ID == 0 || ID == 1 ? 255 : 0, ID == 1 || ID == 2 ? 255 : 0, 0));
	System::Drawing::SolidBrush^ MyBrushBlack =
		gcnew System::Drawing::SolidBrush(System::Drawing::Color::Black);
	System::Drawing::Pen^ MyPen =
		gcnew System::Drawing::Pen(System::Drawing::Color::FromArgb(ID == 0 || ID == 1 ? 255 : 0, ID == 1 || ID == 2 ? 255 : 0, 0));

	//g->DrawEllipse(MyPen, System::Drawing::Rectangle(X - 5, Y - 5, 10, 10));
	g->FillEllipse(MyBrushBlack, System::Drawing::Rectangle(X - 5, Y - 5, 10, 10));
	g->FillEllipse(MyBrush, System::Drawing::Rectangle(X - 5, Y - 5, 10, 10));
	g->DrawEllipse(MyPen, System::Drawing::Rectangle(X - 5, Y - 5, 10, 10));
}