
class Cell;
class NeuralNetwork;
struct Neuron;
struct Axion;

#pragma once
#include "Global.h"

/*
Operations:
0: add
1: subtract
2: multiply
3: divide
*/

struct Neuron
{
	//0: Normal
	//1: Input
	//2: Output
	//3: Constant
	uint8_t Type = 0;

	unsigned int Operation;
	double X;
	double Y;

	int8_t Value;

	std::vector<Axion *> SourceList;
	std::vector<Axion *> DestList;
	Neuron(uint8_t type)
	{
		Type = type;

		X = Rand(-NetworkWidth / 2, NetworkWidth / 2); //rand() % PlayWidth;
		Y = Rand(-NetworkHeight / 2, NetworkHeight / 2); // rand() % PlayHeight;

		Operation = Rand(0, 3);
	}
};
struct Axion
{
	int8_t Value;
	int8_t Weighting;

	Neuron *Source;
	Neuron *Dest;
	Axion()
	{

	}
};

class NeuralNetwork
{
public:
	std::vector<Neuron *> NeuronList;
	std::vector<Axion *> AxionList;

	NeuralNetwork()
	{
		for (int i = 0; i < 6; i++)
		{
			NeuronList.push_back(new Neuron(1));
		}
		for (int i = 0; i < 7; i++)
		{
			NeuronList.push_back(new Neuron(2));
		}
		for (int i = 0; i < 400; i++)
		{
			//NeuronList.push_back(new Neuron(0));
		}
	}
	~NeuralNetwork()
	{
		for (Neuron *neuron : NeuronList)
		{
			delete neuron;
		}
		for (Axion *axion : AxionList)
		{
			delete axion;
		}
	}

	void Mutate()
	{

	}

	void Update()
	{
		for (int i = 0; i < NeuronList.size(); i++)
		{
			Neuron *neuron = NeuronList[i];
			for (int q = 0; q < neuron->SourceList.size(); q++)
			{
				Axion *axion = neuron->SourceList[q];
				switch (neuron->Operation)
				{
				case 0:
					neuron->Value += axion->Value;
					break;
				case 1:
					neuron->Value -= axion->Value;
					break;
				case 2:
					neuron->Value *= axion->Value;
					break;
				case 3:
					neuron->Value /= axion->Value;
					break;
				}
			}
		}
		for (int i = 0; i < NeuronList.size(); i++)
		{
			Neuron *neuron = NeuronList[i];
			for (int q = 0; q < neuron->SourceList.size(); q++)
			{
				Axion *axion = neuron->SourceList[q];
				axion->Value = (int8_t)((double)neuron->Value * ((double)axion->Weighting / 255));
			}
		}
	}
};

struct Eye
{
	double Fov;
	double Offset;
	Eye()
	{
		Fov = DRand(0.0, TAU); //fmod((double)rand(), TAU);
		Offset = DRand(0.0, TAU); //fmod((double)rand(), TAU);
	}
};

class Cell
{
public:
	double X; double Y;
	double Rotation;
	int Energy = InitialCellEnergy;
	int Health = MaxCellHealth;

	//DNA
	double Size;
	double Speed;
	bool EatPlants;
	bool EatCell;
	int NumEyes;
	NeuralNetwork Network;
	std::vector<Eye> EyeList;

	Cell()
	{
		X = Rand(-PlayWidth / 2, PlayWidth / 2); //rand() % PlayWidth;
		Y = Rand(-PlayHeight / 2, PlayHeight / 2); // rand() % PlayHeight;

		Rotation = DRand(0, TAU); //fmod((double)rand(), TAU);

		//Dna
		Size = DRand(MinCellSize, MaxCellSize); //MinCellSize + fmod(rand(), MaxCellSize - MinCellSize);
		Speed = DRand(0, MaxCellSpeed); //MinCellSpeed + fmod(rand(), MaxCellSpeed - MinCellSpeed);
		EatPlants = !Rand(0, 1); //rand() % 1;
		EatCell = !Rand(0, 100); //(bool)Rand(0, 1);
		NumEyes = (int)QuadraticRandom(0, MaxInitialCellEyes, 8, 20);
		for (int i = 0; i < NumEyes; i++)
		{
			EyeList.push_back(Eye());
		}
	}

	~Cell()
	{

	}

	void Mutate()
	{

	}

	void Update()
	{

		Network.Update();

	}
};
