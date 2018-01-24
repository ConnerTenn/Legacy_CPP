#pragma once

#include "Neuron.h"
#include "Synapse.h"
//using namespace std;

/*class NeuralNetwork
{
	//std::vector<std::vector<std::vector<Neuron>>> _Network = { { {} },{ {} },{ {} } };
	std::vector<std::vector<Neuron*>> _InputNodes = { {} };
	std::vector<std::vector<Neuron*>> _ProcessNodes;
	std::vector<std::vector<Neuron*>> _OutputNodes = { {} };
	std::vector<std::vector<std::vector<Neuron*>>*> _Network = { &_InputNodes, &_ProcessNodes, &_OutputNodes };


public:
	NeuralNetwork()
	{

	}
	NeuralNetwork(int NumInputs, int NumProcessLayers, int NumProcessNodes, int NumOutputs)
	{
		for (int Nodes = 0; Nodes < NumInputs; Nodes++)
		{
			_InputNodes[0].push_back(new Neuron());
		}

		for (int Layers = 0; Layers < NumProcessLayers; Layers++)
		{
			_ProcessNodes.push_back({});
			for (int Nodes = 0; Nodes < NumProcessNodes; Nodes++)
			{
				//_ProcessNodes[Layers].push_back(new Neuron(_InputNodes[0]));
			}
		}

		for (int Nodes = 0; Nodes < NumOutputs; Nodes++)
		{
			_OutputNodes[0].push_back(new Neuron());
		}

		/for (int Nodes = 0; Nodes < NumInputs; Nodes++)
		{
			_Network[0][0].push_back(Neuron());
		}
		for (int Layers = 0; I < NumProcessLayers; Layers++)
		for (int Nodes = 0; Nodes < NumProcessNodes; Nodes++)
		{
			for (Neuron Inputs : _Network[0])
			{
				_Network[1].push_back(Neuron());
			}
		}/
	}
	~NeuralNetwork()
	{
		for (std::vector<std::vector<Neuron*>>* Group : _Network)
		{
			for (std::vector<Neuron*> Layer : *Group)
			{
				for (Neuron* Node : Layer)
				{
					delete(Node);
					Node = 0;
				}
			}
			//delete(Group);
			Group = 0;
		}
	}
};*/

class NeuralNetwork
{
public:
	//DNA
	struct NeuronDNAData
	{
		int Identifier;
		int X;
		int Y;
		NeuronDNAData(int identifier, int x, int y)
		{
			Identifier = identifier; X = x; Y = y;
		}
	};
	struct SynapseDNAData
	{
		int Begin;
		int End;
		SynapseDNAData(int begin, int end)
		{
			Begin = begin;
			End = end;
		}
	};
	//std::vector<NeuronDNAData> DNA_Neuron;
	//std::vector<SynapseDNAData> DNA_Synapse;

	std::vector<Neuron*> NeuronList;
	std::vector<Synapse*> SynapseList;

public:
	/*NeuralNetwork()
	{
		DNA_Neuron.push_back({ 000, 10, 10 });
		DNA_Neuron.push_back({ 001, 10, 20 });
		DNA_Neuron.push_back({ 002, 10, 30 });
		DNA_Neuron.push_back({ 003, 10, 40 });
		DNA_Neuron.push_back({ 004, 10, 50 });

		DNA_Neuron.push_back({ 900, 110, 10 });
		DNA_Neuron.push_back({ 901, 110, 20 });
		//DNA_Neuron.push_back({ 902, 110, 30 });
		//DNA_Neuron.push_back({ 903, 110, 40 });
		//DNA_Neuron.push_back({ 904, 110, 50 });
	}*/
	NeuralNetwork()
	{
		for (int I = 1; I <= 5; I++)
		{
			NeuronList.push_back(new Neuron(10, I*15, 0));
		}
		NeuronList[0]->Value = 0.5;
		NeuronList[1]->Value = 1;

		for (int I = 1; I <= 2; I++)
		{
			NeuronList.push_back(new Neuron(200, I * 15, 2));
		}
		GenearateDNA();
	}
	~NeuralNetwork()
	{
		for (Neuron *neuron : NeuronList)
		{
			//delete(neuron);
			neuron = 0;
		}
		for (Synapse *synapse : SynapseList)
		{
			//delete(synapse);
			synapse = 0;
		}
	}

	void GenearateDNA()
	{
		srand(static_cast<unsigned int>(time(NULL)));
		int Selection;

		//Generate Neurons
		Selection = 3 - int(log10(rand() % 100 + 1) / log10(4));
		for (int I = 0; I < Selection; I++)
		{
			int x = (rand() % (199-10))+10, y = rand() % 100 + 10;
			NeuronList.push_back(new Neuron(x, y, 1));
		}

		//Generate Synapses
		Selection = 6 - int(log10(rand() % 100 + 1) / log10(2));
		std::vector<Neuron*> Possible;
		for (int I = 0; I < Selection; I++)
		{
			Possible.clear();
			//Make list of neurons that are not the output
			for (Neuron* neuron : NeuronList)
			{
				if (neuron->ID != 2)
				{
					Possible.push_back(neuron);
					//System::Console::WriteLine("NeuronX: {0}", neuron->X);
				}
			}

			//Get start neuron
			int len = static_cast<int>(Possible.size());
			Neuron *Start = Possible[rand() % len];
			//Make list of neurons that are after the start neuron
			Possible.clear();
			for (Neuron* neuron : NeuronList)
			{
				//System::Console::Write("{0} {1} ", Start->X, neuron->X);
				if (Start->X < neuron->X)
				{
					//System::Console::Write("ADD");
					Possible.push_back(neuron);
				}
				//System::Console::WriteLine();
			}
			//Get end neuron
			len = static_cast<int>(Possible.size());
			Neuron *End;
			
			End = Possible[rand() % len];
			//System::Console::WriteLine("S: {0}, E: {1}, ID:{2}", Start->X, End->X, End->ID);
			//System::Console::WriteLine("S");
			Synapse *NewSynapse = new Synapse(Start, End, (rand() % 1000) / 1000.0);
			SynapseList.push_back(NewSynapse);
			Start->Output.push_back(NewSynapse);
			End->Input.push_back(NewSynapse);
			NewSynapse = 0;
			//System::Console::WriteLine();
		}
	}
	void Mutate()
	{
		srand(static_cast<unsigned int>(time(NULL)));
	}
	void InitNetworkSim()
	{

	}
	void Update()
	{
		for (Neuron *neuron : NeuronList)
		{
			neuron->Update();
		}
	}

	void Draw(System::Windows::Forms::PaintEventArgs^ e)
	{
		System::Drawing::Graphics^ g = e->Graphics;

		//System::Drawing::SolidBrush^ MyBrush =
		//	gcnew System::Drawing::SolidBrush(System::Drawing::Color::FromArgb(255/4,0, 255, 0));
		System::Drawing::Pen^ MyPen =
			gcnew System::Drawing::Pen(System::Drawing::Color::FromArgb(255, 255, 255));

		g->DrawRectangle(MyPen, System::Drawing::Rectangle(0, 0, 200 + 10, 115 + 10));

		for (int I = 0; I < SynapseList.size(); I++)
		{
			SynapseList[I]->Draw(e);
		}
		for (int I = 0; I < NeuronList.size(); I++)
		{
			NeuronList[I]->Draw(e);
		}
	}
};
