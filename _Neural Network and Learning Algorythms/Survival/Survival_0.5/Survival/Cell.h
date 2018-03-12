
#define _V1_
#ifdef _V1_

class Cell;
class NeuralNetwork;
struct Neuron;
struct Axon;
struct Eye;
struct DNA;

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
struct NeuronAttributes
{
	uint8_t Type = 0;

	std::string Label;

	unsigned int Operation = 0;
	double X = 0;
	double Y = 0;

	int Value = 0;

	NeuronAttributes(uint8_t type = 0, std::string label = "")
	{
		Type = type;

		Label = label;

		X = Rand(-NetworkWidth / 2, NetworkWidth / 2); //rand() % PlayWidth;
		Y = Rand(-NetworkHeight / 2, NetworkHeight / 2); // rand() % PlayHeight;

		Operation = Rand(0, 4);
		if (Operation == 4 && Type == 0)
		{
			Value = Rand(0, 1000);
		}
	}
	void Mutate()
	{
		if (Rand(0, 50) == 0) { Operation = Rand(0, 4); }
		if (Rand(0, 50) == 0) { X = Rand(-NetworkWidth / 2, NetworkWidth / 2); }
		if (Rand(0, 50) == 0) { Y = Rand(-NetworkHeight / 2, NetworkHeight / 2); }
		if (Operation == 4 && Type == 0)
		{
			if (Rand(0, 50) == 0) { Value = Rand(0, 1000); }
		}
	}
};

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

	std::vector<Axon *> SourceList;
	std::vector<Axon *> DestinationList;
	Neuron(NeuronAttributes attributes)
	{
		Type = attributes.Type;
		Label = attributes.Label;
		X = attributes.X;
		Y = attributes.Y;
		Operation = attributes.Operation;
		Value = attributes.Value;
	}
	/*Neuron(uint8_t type, std::string label = "")
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
	}*/
};


struct AxonAttributes
{
	int SourceNeuronIndex;
	int DestinationNeuronIndex;
	double Weighting = 0;
	AxonAttributes(int maxIndex)
	{
		SourceNeuronIndex = Rand(0, maxIndex);
		DestinationNeuronIndex = Rand(0, maxIndex);
		Weighting = DRand(0, 1);
	}
	void Mutate(int maxIndex)
	{
		if (Rand(0, 50) == 0) { SourceNeuronIndex = Rand(0, maxIndex); }
		if (Rand(0, 50) == 0) { DestinationNeuronIndex = Rand(0, maxIndex); }
		if (Rand(0, 50) == 0) { Weighting = DRand(0, 1); }
	}
};

struct Axon
{
	int Value = 0;
	double Weighting = 0;

	Neuron *Source;
	Neuron *Destination;
	Axon(AxonAttributes attributes, Neuron *source, Neuron *destination)
	{
		Weighting = attributes.Weighting;

		Source = source;
		Destination = destination;
	}
};

class NeuralNetwork
{
public:
	std::vector<Neuron *> NeuronList;
	std::vector<Axon *> AxonList;


	std::vector<Neuron *> EyeInputs;
	Neuron *CellProximityInput;

	Neuron *RotateLeftOutput;
	Neuron *RotateRightOutput;
	Neuron *ForwardOutput;
	Neuron *BackwardOutput;
	Neuron *LeftOutput;
	Neuron *RightOutput;
	Neuron *ReproduceOutput;
	Neuron *EatPlants;
	Neuron *EatCell;

	NeuralNetwork()
	{
	}
	~NeuralNetwork()
	{
		for (Neuron *neuron : NeuronList)
		{
			delete neuron;
		}
		for (Axon *axon : AxonList)
		{
			delete axon;
		}
	}

	void Update()
	{
		for (int i = 0; i < NeuronList.size(); i++)//Update Neurons with values
		{
			Neuron *neuron = NeuronList[i];
			for (int j = 0; j < neuron->SourceList.size(); j++)
			{
				Axon *axon = neuron->SourceList[j];
				switch (neuron->Operation)
				{
				case 0:
					neuron->Value += axon->Value;
					break;
				case 1:
					neuron->Value -= axon->Value;
					break;
				case 2:
					neuron->Value *= axon->Value;
					break;
				case 3:
					if (axon->Value != 0) { neuron->Value /= axon->Value; }
					else { neuron->Value = 0; }
					break;
				case 4:
					break;
				}
				if (neuron->Value > 1000) { neuron->Value = 1000; }
				if (neuron->Value < 0) { neuron->Value = 0; }
			}
		}
		for (int i = 0; i < NeuronList.size(); i++)//update Axons with values
		{
			Neuron *neuron = NeuronList[i];
			for (int j = 0; j < neuron->DestinationList.size(); j++)
			{
				Axon *axon = neuron->DestinationList[j];
				axon->Value = (int8_t)((double)neuron->Value * axon->Weighting);
			}
		}
	}
};

struct EyeAttributes
{
	double Fov = 0;
	double Offset = 0;
	double Range = 0;

	EyeAttributes()
	{
		Fov = DRand(0.0, PI);
		Offset = DRand(0.0, TAU);
		Range = DRand(0.0, MaxCellViewRange);
	}
	void Mutate()
	{
		if (Rand(0, 50) == 0) { Fov = DRand(0.0, PI); }
		if (Rand(0, 50) == 0) { Offset = DRand(0.0, TAU); }
		if (Rand(0, 50) == 0) { Range = DRand(0.0, MaxCellViewRange); }
	}
};

struct Eye
{
	double Fov = 0;
	double Offset = 0;
	double Range = 0;
	int Value = 0;
	Eye(EyeAttributes attributes)
	{
		Fov = attributes.Fov;
		Offset = attributes.Offset;
		Range = attributes.Range;
	}
};

struct DNA
{
	bool Edit = false;

	double Size;
	double Speed;
	bool EatPlants;
	bool EatCell;
	int NumEyes;
	std::vector<EyeAttributes> EyeAttributesList;
	std::vector<NeuronAttributes> NeuronAttributesList;
	std::vector<AxonAttributes> AxonAttributesList;

	DNA()
	{
		Edit = true;
		Size = DRand(MinCellSize, MaxCellSize);
		Speed = DRand(0, MaxCellSpeed);
		EatPlants = !Rand(0, 1);
		EatCell = !Rand(0, 100);
		NumEyes = NumCellEyes;

		for (int i = 0; i < NumEyes; i++)
		{
			EyeAttributesList.push_back(EyeAttributes());
			NeuronAttributesList.push_back(NeuronAttributes(1, "EyeInput"));
		}

		NeuronAttributesList.push_back(NeuronAttributes(1, "CellProximityInput"));
		NeuronAttributesList.push_back(NeuronAttributes(2, "RotateLeftOutput"));
		NeuronAttributesList.push_back(NeuronAttributes(2, "RotateRightOutput"));
		NeuronAttributesList.push_back(NeuronAttributes(2, "ForwardOutput"));
		NeuronAttributesList.push_back(NeuronAttributes(2, "BackwardOutput"));
		NeuronAttributesList.push_back(NeuronAttributes(2, "LeftOutput"));
		NeuronAttributesList.push_back(NeuronAttributes(2, "RightOutput"));
		NeuronAttributesList.push_back(NeuronAttributes(2, "ReproduceOutput"));
		NeuronAttributesList.push_back(NeuronAttributes(2, "EatPlants"));
		NeuronAttributesList.push_back(NeuronAttributes(2, "EatCell"));
		Edit = false;
	}

	DNA(DNA *parent)
	{
		Edit = true;
		Size = parent->Size;
		Speed = parent->Speed;
		EatPlants = parent->EatPlants;
		EatCell = parent->EatCell;
		NumEyes = parent->NumEyes;

		EyeAttributesList = parent->EyeAttributesList;
		NeuronAttributesList = parent->NeuronAttributesList;
		AxonAttributesList = parent->AxonAttributesList;

		Mutate();
		Edit = false;
	}

	DNA(DNA *parentA, DNA *parentB)
	{
		Edit = true;
		if (Rand(0, 1) == 0) { Size = parentA->Size; }
		else { Size = parentB->Size; }
		if (Rand(0, 1) == 0) { Speed = parentA->Speed; }
		else { Speed = parentB->Speed; }
		if (Rand(0, 1) == 0) { EatPlants = parentA->EatPlants; }
		else { EatPlants = parentB->EatPlants; }
		if (Rand(0, 1) == 0) { EatCell = parentA->EatCell; }
		else { EatCell = parentB->EatCell; }
		if (Rand(0, 1) == 0) { NumEyes = parentA->NumEyes; }
		else { NumEyes = parentB->NumEyes; }

		//Eyes
		for (int i = 0; i < NumEyes; i++)
		{
			if (Rand(0, 1) == 0) { EyeAttributesList.push_back(parentA->EyeAttributesList[i]); }
			else { EyeAttributesList.push_back(parentB->EyeAttributesList[i]); }
		}

		//Neurons
		for (int i = 0; i < max(parentA->NeuronAttributesList.size(), parentB->NeuronAttributesList.size()); i++)
		{
			if (Rand(0, 1) == 0)
			{
				if (parentA->NeuronAttributesList.size() > i)
				{
					NeuronAttributesList.push_back(parentA->NeuronAttributesList[i]);
				}
			}
			else
			{
				if (parentB->NeuronAttributesList.size() > i)
				{
					NeuronAttributesList.push_back(parentB->NeuronAttributesList[i]);
				}
			}
		}

		//Axons
		for (int i = 0; i < max(parentA->AxonAttributesList.size(), parentB->AxonAttributesList.size()); i++)
		{
			if (Rand(0, 1) == 0)
			{
				if (parentA->AxonAttributesList.size() > i)
				{
					AxonAttributesList.push_back(parentA->AxonAttributesList[i]);
				}
			}
			else
			{
				if (parentB->AxonAttributesList.size() > i)
				{
					AxonAttributesList.push_back(parentB->AxonAttributesList[i]);
				}
			}
		}
		//Axon Check
		for (int i = 0; i < AxonAttributesList.size(); i++)
		{
			if (AxonAttributesList[i].SourceNeuronIndex >= AxonAttributesList.size() || AxonAttributesList[i].DestinationNeuronIndex >= AxonAttributesList.size())
			{
				AxonAttributesList.erase(AxonAttributesList.begin() + i);
			}
		}

		Mutate();
		Edit = false;
	}

	void Mutate()
	{
		if (Rand(0, 50) == 0) { Size = DRand(MinCellSize, MaxCellSize); }
		if (Rand(0, 50) == 0) { Speed = DRand(0, MaxCellSpeed); }
		if (Rand(0, 50) == 0) { EatPlants = !Rand(0, 1); }
		if (Rand(0, 50) == 0) { EatCell = !Rand(0, 100); }

		for (int i = 0; i < NumEyes; i++)
		{
			EyeAttributesList[i].Mutate();;
		}

		for (int i = 0; i < NeuronAttributesList.size(); i++)
		{
			NeuronAttributesList[i].Mutate();
		}
		if (Rand(0, 50) == 0) { NeuronAttributesList.push_back(NeuronAttributes()); }
		if (Rand(0, 50) == 0) { int pos = Rand(0, (int)NeuronAttributesList.size() - 1); if (NeuronAttributesList[pos].Type == 0) { NeuronAttributesList.erase(NeuronAttributesList.begin() + pos); } }

		for (int i = 0; i < AxonAttributesList.size(); i++)
		{
			AxonAttributesList[i].Mutate((int)AxonAttributesList.size());
		}
		if (Rand(0, 50) == 0) { AxonAttributesList.push_back(AxonAttributes((int)AxonAttributesList.size())); }
		if (Rand(0, 50) == 0 && AxonAttributesList.size()) { int pos = Rand(0, (int)AxonAttributesList.size() - 1); AxonAttributesList.erase(AxonAttributesList.begin() + pos); }
	}
};

class Cell
{
public:
	double X; double Y;
	double Rotation;
	double Energy = InitialCellEnergy;
	double Health = MaxCellHealth;
	NeuralNetwork Network;
	bool Alive = true;
	Cell *Mate = 0;

	//DNA
	DNA Dna;
	double Size;
	double Speed;
	bool EatPlants;
	bool EatCell;
	int NumEyes;
	std::vector<Eye *> EyeList;

	Cell() :
		Dna()
	{
		X = Rand(-PlayWidth / 2, PlayWidth / 2); //rand() % PlayWidth;
		Y = Rand(-PlayHeight / 2, PlayHeight / 2); // rand() % PlayHeight;

		Rotation = DRand(0, TAU); //fmod((double)rand(), TAU);

								  //Dna
		Initilize();
	}

	Cell(Cell *parent) :
		Dna(&(parent->Dna))
	{
		{
			double rotation = DRand(0, TAU);
			X = parent->X + sin(rotation) * (2 * parent->Size);
			Y = parent->Y - cos(rotation) * (2 * parent->Size);
		}
		Rotation = DRand(0, TAU);

		Initilize();
	}

	Cell(Cell *parentA, Cell *parentB) :
		Dna(&(parentA->Dna), &(parentB->Dna))
	{
		{
			double rotation = DRand(0, TAU);
			X = (parentA->X + parentB->X) / 2.0 + sin(rotation) * (2 * max(parentA->Size, parentB->Size));
			Y = (parentA->Y + parentB->Y) / 2.0 - cos(rotation) * (2 * max(parentA->Size, parentB->Size));
		}
		Rotation = DRand(0, TAU);

		Initilize();
	}

	~Cell()
	{
		for (int i = 0; i < NumEyes; i++)
		{
			delete EyeList[i]; EyeList[i] = 0;
		}
	}

	void Initilize()
	{
		Size = Dna.Size;
		Speed = Dna.Speed;
		EatPlants = Dna.EatPlants;
		EatCell = Dna.EatCell;
		NumEyes = Dna.NumEyes;


		for (EyeAttributes attributes : Dna.EyeAttributesList)
		{
			EyeList.push_back(new Eye(attributes));
		}

		for (NeuronAttributes attributes : Dna.NeuronAttributesList)
		{
			Neuron *neuron = new Neuron(attributes);
			Network.NeuronList.push_back(neuron);
			if (attributes.Label == "EyeInput") { Network.EyeInputs.push_back(neuron); }
			if (attributes.Label == "CellProximityInput") { Network.CellProximityInput = neuron; }
			if (attributes.Label == "RotateLeftOutput") { Network.RotateLeftOutput = neuron; }
			if (attributes.Label == "RotateRightOutput") { Network.RotateRightOutput = neuron; }
			if (attributes.Label == "ForwardOutput") { Network.ForwardOutput = neuron; }
			if (attributes.Label == "BackwardOutput") { Network.BackwardOutput = neuron; }
			if (attributes.Label == "LeftOutput") { Network.LeftOutput = neuron; }
			if (attributes.Label == "RightOutput") { Network.RightOutput = neuron; }
			if (attributes.Label == "ReproduceOutput") { Network.ReproduceOutput = neuron; }
			if (attributes.Label == "EatPlants") { Network.EatPlants = neuron; }
			if (attributes.Label == "EatCell") { Network.EatCell = neuron; }
		}

		for (AxonAttributes attributes : Dna.AxonAttributesList)
		{
			Neuron *source = Network.NeuronList[attributes.SourceNeuronIndex];
			Neuron *destination = Network.NeuronList[attributes.DestinationNeuronIndex];

			Axon *axon = new Axon(attributes, source, destination);
			Network.AxonList.push_back(axon);
			source->DestinationList.push_back(axon);
			destination->SourceList.push_back(axon);
		}
	}

	void Update()
	{
		if (Alive)
		{
			{/*Update Senses*/}
			{
				Cell* cell;
				for (int i = 0; i < CellList.size(); i++)
				{
					cell = CellList[i];
					if (cell != this && cell->Alive)
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

						{/*CellProximity*/}
						{
							if (dist <= Size + cell->Size)
							{
								Network.CellProximityInput->Value = 1000;
								Mate = cell;
							}
						}
					}
				}
			}

			Network.Update();

			{/*Update Actions*/}
			{
				double rotationLeft;
				double rotationRight;
				rotationLeft = ((double)Network.RotateLeftOutput->Value / 1000.0) * (TAU / 1000.0);
				rotationRight = ((double)Network.RotateRightOutput->Value / 1000.0) * (TAU / 1000.0);
				Rotation += rotationLeft + rotationRight;

				double forward = 0;
				double back = 0;
				double left = 0;
				double right = 0;
				forward += (double)(Network.ForwardOutput->Value) / 1000 * Speed;
				back += (double)(Network.BackwardOutput->Value) / 1000 * Speed;
				left += (double)(Network.LeftOutput->Value) / 1000 * Speed;
				right += (double)(Network.RightOutput->Value) / 1000 * Speed;

				X += (right - left) * cos(Rotation) + (forward - back) * sin(Rotation);
				Y -= -(right - left) * sin(Rotation) + (forward - back) * cos(Rotation);

				if (X > PlayWidth / 2) { X = PlayWidth / 2; }
				else if (X < -PlayWidth / 2) { X = -PlayWidth / 2; }
				if (Y > PlayHeight / 2) { Y = PlayHeight / 2; }
				else if (Y < -PlayHeight / 2) { Y = -PlayHeight / 2; }

				Energy -= abs(forward + back + left + right + rotationLeft + rotationRight + 2.0 * Size) / 10.0;
				Energy -= 1.0;
				if (Energy <= 0.0)
				{
					Energy = 0;
					Health -= 1.0;
				}
				if (Health <= 0.0)
				{
					Health = 0.0;
					Alive = false;
				}
			}
		}
	}
};

#endif



#ifdef _V2_

class Cell;
class NeuralNetwork;
struct Neuron;
struct Axon;
struct Eye;
struct DNA;

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
struct NeuronAttributes
{
	uint8_t Type = 0;

	std::string Label;

	unsigned int Operation = 0;
	double X = 0;
	double Y = 0;

	int Value = 0;

	NeuronAttributes(uint8_t type = 0, std::string label = "")
	{
		Type = type;

		Label = label;

		X = Rand(-NetworkWidth / 2, NetworkWidth / 2); //rand() % PlayWidth;
		Y = Rand(-NetworkHeight / 2, NetworkHeight / 2); // rand() % PlayHeight;

		Operation = Rand(0, 4);
		if (Operation == 4 && Type == 0)
		{
			Value = Rand(0, 1000);
		}
	}
	void Mutate()
	{
		if (Rand(0, 50) == 0) { Operation = Rand(0, 4); }
		if (Rand(0, 50) == 0) { X = Rand(-NetworkWidth / 2, NetworkWidth / 2); }
		if (Rand(0, 50) == 0) { Y = Rand(-NetworkHeight / 2, NetworkHeight / 2); }
		if (Operation == 4 && Type == 0)
		{
			if (Rand(0, 50) == 0) { Value = Rand(0, 1000); }
		}
	}
};

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

	std::vector<Axon *> SourceList;
	std::vector<Axon *> DestinationList;
	Neuron(NeuronAttributes attributes)
	{
		Type = attributes.Type;
		Label = attributes.Label;
		X = attributes.X;
		Y = attributes.Y;
		Operation = attributes.Operation;
		Value = attributes.Value;
	}
	/*Neuron(uint8_t type, std::string label = "")
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
	}*/
};


struct AxonAttributes
{
	int SourceNeuronIndex;
	int DestinationNeuronIndex;
	double Weighting = 0;
	AxonAttributes(int maxIndex)
	{
		SourceNeuronIndex = Rand(0, maxIndex);
		DestinationNeuronIndex = Rand(0, maxIndex);
		Weighting = DRand(0, 1);
	}
	void Mutate(int maxIndex)
	{
		if (Rand(0, 50) == 0) { SourceNeuronIndex = Rand(0, maxIndex); }
		if (Rand(0, 50) == 0) { DestinationNeuronIndex = Rand(0, maxIndex); }
		if (Rand(0, 50) == 0) { Weighting = DRand(0, 1); }
	}
};

struct Axon
{
	int Value = 0;
	double Weighting = 0;

	Neuron *Source;
	Neuron *Destination;
	Axon(AxonAttributes attributes, Neuron *source, Neuron *destination)
	{
		Weighting = attributes.Weighting;

		Source = source;
		Destination = destination;
	}
};

class NeuralNetwork
{
public:
	std::vector<Neuron *> NeuronList;
	std::vector<Axon *> AxonList;


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
		for (Axon *axon : AxonList)
		{
			delete axon;
		}
	}

	void Update()
	{
		for (int i = 0; i < NeuronList.size(); i++)//Update Neurons with values
		{
			Neuron *neuron = NeuronList[i];
			for (int j = 0; j < neuron->SourceList.size(); j++)
			{
				Axon *axon = neuron->SourceList[j];
				switch (neuron->Operation)
				{
				case 0:
					neuron->Value += axon->Value;
					break;
				case 1:
					neuron->Value -= axon->Value;
					break;
				case 2:
					neuron->Value *= axon->Value;
					break;
				case 3:
					neuron->Value /= axon->Value;
					break;
				case 4:
					break;
				}
			}
		}
		for (int i = 0; i < NeuronList.size(); i++)//update Axons with values
		{
			Neuron *neuron = NeuronList[i];
			for (int j = 0; j < neuron->DestinationList.size(); j++)
			{
				Axon *axon = neuron->DestinationList[j];
				axon->Value = (int8_t)((double)neuron->Value * axon->Weighting);
			}
		}
	}
};

struct EyeAttributes
{
	double Fov = 0;
	double Offset = 0;
	double Range = 0;

	EyeAttributes()
	{
		Fov = DRand(0.0, PI);
		Offset = DRand(0.0, TAU);
		Range = DRand(0.0, MaxCellViewRange);
	}
	void Mutate()
	{
		if (Rand(0, 50) == 0) { Fov = DRand(0.0, PI); }
		if (Rand(0, 50) == 0) { Offset = DRand(0.0, TAU); }
		if (Rand(0, 50) == 0) { Range = DRand(0.0, MaxCellViewRange); }
	}
};

struct Eye
{
	double Fov = 0;
	double Offset = 0;
	double Range = 0;
	int Value = 0;
	Eye(EyeAttributes attributes)
	{
		Fov = attributes.Fov;
		Offset = attributes.Offset;
		Range = attributes.Range;
	}
};

struct DNA
{
	double Size;
	double Speed;
	bool EatPlants;
	bool EatCell;
	int NumEyes;
	std::vector<EyeAttributes> EyeAttributesList;
	std::vector<NeuronAttributes> NeuronAttributesList;
	std::vector<AxonAttributes> AxonAttributesList;
	
	DNA()
	{
		Size = DRand(MinCellSize, MaxCellSize);
		Speed = DRand(0, MaxCellSpeed);
		EatPlants = !Rand(0, 1);
		EatCell = !Rand(0, 100);
		NumEyes = NumCellEyes;

		for (int i = 0; i < NumEyes; i++)
		{
			EyeAttributesList.push_back(EyeAttributes());
			NeuronAttributesList.push_back(NeuronAttributes(1, "EyeInput"));
		}

		NeuronAttributesList.push_back(NeuronAttributes(1, "CellProximityInput"));
		NeuronAttributesList.push_back(NeuronAttributes(2, "RotateLeftOutput"));
		NeuronAttributesList.push_back(NeuronAttributes(2, "RotateRightOutput"));
		NeuronAttributesList.push_back(NeuronAttributes(2, "ForwardOutput"));
		NeuronAttributesList.push_back(NeuronAttributes(2, "BackwardOutput"));
		NeuronAttributesList.push_back(NeuronAttributes(2, "LeftOutput"));
		NeuronAttributesList.push_back(NeuronAttributes(2, "RightOutput"));
		NeuronAttributesList.push_back(NeuronAttributes(2, "ReproduceOutput"));
	}

	DNA(DNA *parent)
	{
		Size = parent->Size;
		Speed = parent->Speed;
		EatPlants = parent->EatPlants;
		EatCell = parent->EatCell;
		NumEyes = parent->NumEyes;

		EyeAttributesList = parent->EyeAttributesList;
		NeuronAttributesList = parent->NeuronAttributesList;
		AxonAttributesList = parent->AxonAttributesList;

		Mutate();
	}

	DNA(DNA *parentA, DNA *parentB)
	{
		if (Rand(0, 1) == 0) { Size = parentA->Size; } else { Size = parentB->Size; }
		if (Rand(0, 1) == 0) { Speed = parentA->Speed; } else { Speed = parentB->Speed; }
		if (Rand(0, 1) == 0) { EatPlants = parentA->EatPlants; } else { EatPlants = parentB->EatPlants; }
		if (Rand(0, 1) == 0) { EatCell = parentA->EatCell; } else { EatCell = parentB->EatCell; }
		if (Rand(0, 1) == 0) { NumEyes = parentA->NumEyes; } else { NumEyes = parentB->NumEyes; }

		//Eyes
		for (int i = 0; i < NumEyes; i++)
		{
			if (Rand(0, 1) == 0) { EyeAttributesList.push_back(parentA->EyeAttributesList[i]); } else { EyeAttributesList.push_back(parentB->EyeAttributesList[i]); }
		}

		//Neurons
		for (int i = 0; i < max(parentA->NeuronAttributesList.size(), parentB->NeuronAttributesList.size()); i++)
		{
			if (Rand(0, 1) == 0)
			{
				if (parentA->NeuronAttributesList.size() > i)
				{
					NeuronAttributesList.push_back(parentA->NeuronAttributesList[i]);
				}
			}
			else
			{
				if (parentB->NeuronAttributesList.size() > i)
				{
					NeuronAttributesList.push_back(parentB->NeuronAttributesList[i]);
				}
			}
		}

		//Axons
		for (int i = 0; i < max(parentA->AxonAttributesList.size(), parentB->AxonAttributesList.size()); i++)
		{
			if (Rand(0, 1) == 0)
			{
				if (parentA->AxonAttributesList.size() > i)
				{
					AxonAttributesList.push_back(parentA->AxonAttributesList[i]);
				}
			}
			else
			{
				if (parentB->NeuronAttributesList.size() > i)
				{
					AxonAttributesList.push_back(parentB->AxonAttributesList[i]);
				}
			}
		}
		//Axon Check
		for (int i = 0; i < AxonAttributesList.size(); i++)
		{
			if (AxonAttributesList[i].SourceNeuronIndex >= AxonAttributesList.size() || AxonAttributesList[i].DestinationNeuronIndex >= AxonAttributesList.size())
			{
				AxonAttributesList.erase(AxonAttributesList.begin() + i);
			}
		}

		Mutate();
	}

	void Mutate()
	{
		if (Rand(0, 50) == 0) { Size = DRand(MinCellSize, MaxCellSize); }
		if (Rand(0, 50) == 0) { Speed = DRand(0, MaxCellSpeed); }
		if (Rand(0, 50) == 0) { EatPlants = !Rand(0, 1); }
		if (Rand(0, 50) == 0) { EatCell = !Rand(0, 100); }

		for (int i = 0; i < NumEyes; i++)
		{
			EyeAttributesList[i].Mutate();;
		}

		for (int i = 0; i < NeuronAttributesList.size(); i++)
		{
			NeuronAttributesList[i].Mutate();
			if (Rand(0, 50) == 0) { NeuronAttributesList.push_back(NeuronAttributes()); }
		}

		for (int i = 0; i < AxonAttributesList.size(); i++)
		{
			AxonAttributesList[i].Mutate((int)AxonAttributesList.size());
			if (Rand(0, 50) == 0) { AxonAttributesList.push_back(AxonAttributes((int)AxonAttributesList.size())); }
		}
	}
};

class Cell
{
public:
	double X; double Y;
	double Rotation;
	double Energy = InitialCellEnergy;
	double Health = MaxCellHealth;
	NeuralNetwork *Network;
	bool Alive = true;

	//DNA
	DNA *Dna = 0;
	double Size;
	double Speed;
	bool EatPlants;
	bool EatCell;
	int NumEyes;
	std::vector<Eye> EyeList;

	Cell()
	{
		X = Rand(-PlayWidth / 2, PlayWidth / 2); //rand() % PlayWidth;
		Y = Rand(-PlayHeight / 2, PlayHeight / 2); // rand() % PlayHeight;

		Rotation = DRand(0, TAU); //fmod((double)rand(), TAU);

		//Dna
		Initilize();
	}

	~Cell()
	{
		delete Dna;
		delete Network;
		//EyeList.clear();
		//for (int i = 0; i < NumEyes; i++)
		//{
			//delete EyeList[i]; EyeList[i] = 0;
		//}
	}

	void Cleanup()
	{
		delete Dna;
		delete Network;
		EyeList.clear();
	}

	void Initilize()
	{
		Dna = new DNA();
		Network = new NeuralNetwork();

		X = Rand(-PlayWidth / 2, PlayWidth / 2); //rand() % PlayWidth;
		Y = Rand(-PlayHeight / 2, PlayHeight / 2); // rand() % PlayHeight;

		Rotation = DRand(0, TAU); //fmod((double)rand(), TAU);

		Energy = InitialCellEnergy;
		Health = MaxCellHealth;

		InitlilizeDna();

		Alive = true;
	}
	void Initilize(Cell *parent)
	{
		if (Dna) { delete Dna; } Dna = new DNA();

		double rotation = DRand(0, TAU);
		X = parent->X + sin(rotation) * (2 * parent->Size);
		Y = parent->Y - cos(rotation) * (2 * parent->Size);

		Rotation = DRand(0, TAU); //fmod((double)rand(), TAU);

		Energy = InitialCellEnergy;
		Health = MaxCellHealth;

		InitlilizeDna();

		Alive = true;
	}
	void Initilize(Cell *parentA, Cell *parentB)
	{
		if (Dna) { delete Dna; } Dna = new DNA();

		double rotation = DRand(0, TAU);
		X = (parentA->X + parentB->X) / 2.0 + sin(rotation) * (2 * max(parentA->Size, parentB->Size));
		Y = (parentA->Y + parentB->Y) / 2.0 - cos(rotation) * (2 * max(parentA->Size, parentB->Size));

		Rotation = DRand(0, TAU); //fmod((double)rand(), TAU);

		Energy = InitialCellEnergy;
		Health = MaxCellHealth;

		InitlilizeDna();

		Alive = true;
	}

	void InitlilizeDna()
	{
		Size = Dna->Size;
		Speed = Dna->Speed;
		EatPlants = Dna->EatPlants;
		EatCell = Dna->EatCell;
		NumEyes = Dna->NumEyes;


		for (EyeAttributes attributes : Dna->EyeAttributesList)
		{
			EyeList.push_back(Eye(attributes));
		}

		for (NeuronAttributes attributes : Dna->NeuronAttributesList)
		{
			Neuron *neuron = new Neuron(attributes);
			Network->NeuronList.push_back(neuron);
			if (attributes.Label == "EyeInput") { Network->EyeInputs.push_back(neuron); }
			if (attributes.Label == "CellProximityInput") { Network->CellProximityInput = neuron; }
			if (attributes.Label == "RotateLeftOutput") { Network->RotateLeftOutput = neuron; }
			if (attributes.Label == "RotateRightOutput") { Network->RotateRightOutput = neuron; }
			if (attributes.Label == "ForwardOutput") { Network->ForwardOutput = neuron; }
			if (attributes.Label == "BackwardOutput") { Network->BackwardOutput = neuron; }
			if (attributes.Label == "LeftOutput") { Network->LeftOutput = neuron; }
			if (attributes.Label == "RightOutput") { Network->RightOutput = neuron; }
			if (attributes.Label == "ReproduceOutput") { Network->ReproduceOutput = neuron; }
		}

		for (AxonAttributes attributes : Dna->AxonAttributesList)
		{
			Neuron *source = Network->NeuronList[attributes.SourceNeuronIndex];
			Neuron *destination = Network->NeuronList[attributes.DestinationNeuronIndex];

			Axon *axon = new Axon(attributes, source, destination);
			Network->AxonList.push_back(axon);
			source->DestinationList.push_back(axon);
			destination->SourceList.push_back(axon);
		}
	}

	void Update()
	{
		if (Alive)
		{
			{/*Update Senses*/}
			{
				Cell* cell;
				for (int i = 0; i < CellList.size(); i++)
				{
					cell = CellList[i];
					if (cell != this && cell->Alive)
					{
						double dist = Dist(X, Y, cell->X, cell->Y);

						{/*Eye*/}
						{
							if (dist <= MaxCellViewRange)
							{
								for (int j = 0; j < EyeList.size(); j++)
								{
									Eye &eye = EyeList[j];
									if (dist <= eye.Range)
									{
										//calculate within FOV
										//double angle = GetAngle(cell->X - X, cell->Y - Y);
										//if (angle > fmod(Rotation, TAU) + fmod(eye->Offset, TAU) - fmod(eye->Fov, TAU) && angle < fmod(Rotation, TAU) + fmod(eye->Offset, TAU) + fmod(eye->Fov, TAU))
										//{
										//	int val = (int)(255.0 - 255.0 * (dist / eye->Range));
										//	if (val > eye->Value) { eye->Value = val; }
										//}
										if (AngleBetweenPoints(X, Y, X + sin(eye.Offset + Rotation), Y - cos(eye.Offset + Rotation), cell->X, cell->Y) <= eye.Fov)
										{
											double ang = AngleBetweenPoints(X, Y, X + sin(eye.Offset + Rotation), Y - cos(eye.Offset + Rotation), cell->X, cell->Y);
											double xa = X + sin(eye.Offset + Rotation); double ya = Y - cos(eye.Offset + Rotation);
											int val = (int)(1000.0 - 1000.0 * (dist / eye.Range));
											if (val > eye.Value)
											{
												eye.Value = val;
											}
										}
										else
										{
											eye.Value = 0;
										}
									}
									else
									{
										eye.Value = 0;
									}
								}
							}

							for (int i = 0; i < Network->EyeInputs.size(); i++)
							{
								Network->EyeInputs[i]->Value = EyeList[i].Value;
							}
						}

						{/*CellProximity*/}
						{
							if (dist <= Size + cell->Size)
							{
								Network->CellProximityInput->Value = 1000;
							}
						}
					}
				}
			}

			Network->Update();

			{/*Update Actions*/}
			{
				double rotationLeft;
				double rotationRight;
				rotationLeft = ((double)Network->RotateLeftOutput->Value / 1000.0) * (TAU / 1000.0);
				rotationRight = ((double)Network->RotateRightOutput->Value / 1000.0) * (TAU / 1000.0);
				Rotation += rotationLeft + rotationRight;

				double forward = 0;
				double back = 0;
				double left = 0;
				double right = 0;
				forward += (double)(Network->ForwardOutput->Value) / 1000 * Speed;
				back += (double)(Network->BackwardOutput->Value) / 1000 * Speed;
				left += (double)(Network->LeftOutput->Value) / 1000 * Speed;
				right += (double)(Network->RightOutput->Value) / 1000 * Speed;

				X += (right - left) * cos(Rotation) + (forward - back) * sin(Rotation);
				Y -= -(right - left) * sin(Rotation) + (forward - back) * cos(Rotation);

				if (X > PlayWidth / 2) { X = PlayWidth / 2; }
				else if (X < -PlayWidth / 2) { X = -PlayWidth / 2; }
				if (Y > PlayHeight / 2) { Y = PlayHeight / 2; }
				else if (Y < -PlayHeight / 2) { Y = -PlayHeight / 2; }

				Energy -= abs(forward + back + left + right + rotationLeft + rotationRight + 2.0 * Size) / 10.0;
				Energy -= 1.0;
				if (Energy <= 0.0)
				{
					Energy = 0;
					Health -= 1.0;
				}
				if (Health <= 0.0)
				{
					Health = 0.0;
					Alive = false;
				}
			}
		}
	}
};

#endif
