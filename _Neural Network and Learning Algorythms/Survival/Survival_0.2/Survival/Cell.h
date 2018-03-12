
class Cell;
class NeuralNetwork;
struct Neuron;
struct Axion;
struct Eye;

#pragma once
#include "Global.h"

/*
Operations:
0: add
1: subtract
2: multiply
3: divide
4: Constant
*/

struct Neuron
{
	//0: Normal
	//1: Input
	//2: Output
	uint8_t Type = 0;

	std::string Label;

	unsigned int Operation = 0;
	double X = 0;
	double Y = 0;

	int Value = 0;

	std::vector<Axion *> SourceList;
	std::vector<Axion *> DestList;
	Neuron(uint8_t type, std::string label = "")
	{
		Type = type;

		Label = label;

		X = Rand(-NetworkWidth / 2, NetworkWidth / 2); //rand() % PlayWidth;
		Y = Rand(-NetworkHeight / 2, NetworkHeight / 2); // rand() % PlayHeight;

		Operation = Rand(0, 4);
		if (Operation == 4)
		{
			Value = Rand(0, 1000);
		}
	}
};

struct Axion
{
	int8_t Value = 0;
	int8_t Weighting = 0;

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


	std::vector<Neuron *> EyeInputs;
	Neuron *CellProximityInput;

	Neuron *RotateLeftOutput;
	Neuron *RotateRightOutput;
	Neuron *ForwardOutput;
	Neuron *BackwardOutput;
	Neuron *LeftOutput;
	Neuron *RightOutput;
	Neuron *ReproduceOutput;

	NeuralNetwork()
	{
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
			for (int j = 0; j < neuron->SourceList.size(); j++)
			{
				Axion *axion = neuron->SourceList[j];
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
				case 4:
					break;
				}
			}
		}
		for (int i = 0; i < NeuronList.size(); i++)
		{
			Neuron *neuron = NeuronList[i];
			for (int j = 0; j < neuron->SourceList.size(); j++)
			{
				Axion *axion = neuron->SourceList[j];
				axion->Value = (int8_t)((double)neuron->Value * ((double)axion->Weighting / 255));
			}
		}
	}
};

struct Eye
{
	double Fov = 0;
	double Offset = 0;
	double Range = 0;
	int Value = 0;
	Eye()
	{
		Fov = DRand(0.0, PI); //fmod((double)rand(), TAU);
		Offset = DRand(0.0, TAU); //fmod((double)rand(), TAU);
		Range = DRand(0.0, MaxCellViewRange);
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
	std::vector<Eye *> EyeList;

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
		NumEyes = NumCellEyes;//(int)QuadraticRandom(0, MaxInitialCellEyes, 8, 20);
		

		Neuron *neuron;
		for (int i = 0; i < NumEyes; i++)
		{
			EyeList.push_back(new Eye());
			Neuron *eye = new Neuron(1, "EyeInput");
			Network.EyeInputs.push_back(eye);
		}
		neuron = new Neuron(1, "CellProximityInput");
		Network.NeuronList.push_back(neuron);
		Network.CellProximityInput = neuron;

		neuron = new Neuron(2, "RotateLeftOutput");
		Network.NeuronList.push_back(neuron);
		Network.RotateLeftOutput = neuron;
		neuron = new Neuron(2, "RotateRightOutput");
		Network.NeuronList.push_back(neuron);
		Network.RotateRightOutput = neuron;
		neuron = new Neuron(2, "ForwardOutput");
		Network.NeuronList.push_back(neuron);
		Network.ForwardOutput = neuron;
		neuron = new Neuron(2, "BackwardOutput");
		Network.NeuronList.push_back(neuron);
		Network.BackwardOutput = neuron;
		neuron = new Neuron(2, "LeftOutput");
		Network.NeuronList.push_back(neuron);
		Network.LeftOutput = neuron;
		neuron = new Neuron(2, "RightOutput");
		Network.NeuronList.push_back(neuron);
		Network.RightOutput = neuron;
		neuron = new Neuron(2, "ReproduceOutput");
		Network.NeuronList.push_back(neuron);
		Network.ReproduceOutput = neuron;
	}

	~Cell()
	{
		for (int i = 0; i < NumEyes; i++)
		{
			delete EyeList[i]; EyeList[i] = 0;
		}
	}

	void Mutate()
	{

	}

	void Reproduce()
	{

	}

	void Update()
	{
		{/*Update Senses*/}
		{
			Cell* cell;
			for (int i = 0; i < CellList.size(); i++)
			{
				cell = CellList[i];
				if (cell != this)
				{
					double dist = Dist(X, Y, cell->X, cell->Y);

					{/*Eye*/}
					{
						if (dist <= MaxCellViewRange)
						{
							Eye* eye;
							for (int j = 0; j < EyeList.size(); j++)
							{
								eye = EyeList[j];
								if (dist <= eye->Range)
								{
									//calculate within FOV
									//double angle = GetAngle(cell->X - X, cell->Y - Y);
									//if (angle > fmod(Rotation, TAU) + fmod(eye->Offset, TAU) - fmod(eye->Fov, TAU) && angle < fmod(Rotation, TAU) + fmod(eye->Offset, TAU) + fmod(eye->Fov, TAU))
									//{
									//	int val = (int)(255.0 - 255.0 * (dist / eye->Range));
									//	if (val > eye->Value) { eye->Value = val; }
									//}
									if (AngleBetweenPoints(X, Y, X + sin(eye->Offset + Rotation), Y - cos(eye->Offset + Rotation), cell->X, cell->Y) <= eye->Fov)
									{
										double ang = AngleBetweenPoints(X, Y, X + sin(eye->Offset + Rotation), Y - cos(eye->Offset + Rotation), cell->X, cell->Y);
										double xa = X + sin(eye->Offset + Rotation); double ya = Y - cos(eye->Offset + Rotation);
										int val = (int)(1000.0 - 1000.0 * (dist / eye->Range));
										if (val > eye->Value)
										{
											eye->Value = val;
										}
									}
									else
									{
										eye->Value = 0;
									}
								}
								else
								{
									eye->Value = 0;
								}
							}
						}

						for (int i = 0; i < Network.EyeInputs.size(); i++)
						{
							Network.EyeInputs[i]->Value = EyeList[i]->Value;
						}
					}

					if (dist <= Size + cell->Size)
					{
						Network.CellProximityInput->Value = 1000;
					}
				}
			}
		}
		
		Network.Update();

		Rotation -= Network.RotateLeftOutput->Value;
		Rotation += Network.RotateRightOutput->Value;

		double forward = 0;
		double side = 0;
		forward += (double)(Network.ForwardOutput->Value) / 1000 * Speed;
		forward -= (double)(Network.BackwardOutput->Value) / 1000 * Speed;
		side += (double)(Network.LeftOutput->Value) / 1000 * Speed;
		side -= (double)(Network.RightOutput->Value) / 1000 * Speed;

		X += side * cos(Rotation) + forward * sin(Rotation);
		Y -= -side * sin(Rotation) + forward * cos(Rotation);

		if (X > PlayWidth / 2) { X = PlayWidth / 2; } else if (X < -PlayWidth / 2) { X = -PlayWidth / 2; }
		if (Y > PlayHeight / 2) { Y = PlayHeight / 2; } else if (Y < -PlayHeight / 2) { Y = -PlayHeight / 2; }

		if (Energy <= 0.0)
		{
			Health -= 1;
		}
	}
};
