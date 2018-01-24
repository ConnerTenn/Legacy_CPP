
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
5: modulo
*/
struct NeuronAttributes
{
	int Type = 0;

	std::string Label;

	int Operation = 0;
	double X = 0;
	double Y = 0;

	double Value = 0;

	NeuronAttributes(int type = 0, std::string label = "")
	{
		Type = type;

		Label = label;

		X = Rand(-NetworkWidth / 2, NetworkWidth / 2); //rand() % PlayWidth;
		Y = Rand(-NetworkHeight / 2, NetworkHeight / 2); // rand() % PlayHeight;

		Operation = Rand(0, 5);
		if (Operation == 4 && Type == 0)
		{
			Value = DRand(-1.0, 1.0);
		}
	}
	void Mutate()
	{
		if (Rand(0, MutationRate) == 0) { Operation = Rand(0, 5); }
		if (Rand(0, MutationRate) == 0) { X = Rand(-NetworkWidth / 2, NetworkWidth / 2); }
		if (Rand(0, MutationRate) == 0) { Y = Rand(-NetworkHeight / 2, NetworkHeight / 2); }
		if (Operation == 4 && Type == 0)
		{
			if (Rand(0, MutationRate) == 0) { Value = DRand(-1.0, 1.0); }
		}
	}
};

struct Neuron
{
	//0: Normal
	//1: Input
	//2: Output
	int Type = 0;

	std::string Label;

	int Operation = 0;
	double X = 0;
	double Y = 0;

	double Value = 0;

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
	~Neuron()
	{
		for (int i = 0; i < SourceList.size(); i++) { SourceList[i] = 0; }
		for (int i = 0; i < DestinationList.size(); i++) { DestinationList[i] = 0; }
	}
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
		if (Rand(0, MutationRate) == 0) { SourceNeuronIndex = Rand(0, maxIndex); }
		if (Rand(0, MutationRate) == 0) { DestinationNeuronIndex = Rand(0, maxIndex); }
		if (Rand(0, MutationRate) == 0) { Weighting = DRand(-1, 1); }
	}
};

struct Axon
{
	double Value = 0;
	double Weighting = 0;

	Neuron *Source;
	Neuron *Destination;
	Axon(AxonAttributes attributes, Neuron *source, Neuron *destination)
	{
		Weighting = attributes.Weighting;

		Source = source;
		Destination = destination;
	}
	~Axon()
	{
		Source = 0;
		Destination = 0;
	}
};

class NeuralNetwork
{
public:
	std::vector<Neuron *> NeuronList;
	std::vector<Axon *> AxonList;


	Neuron *EyeInput;
	Neuron *CellProximityInput;
	Neuron *WallProximityInput;
	Neuron *EnergyInput;
	Neuron *HealthInput;
	Neuron *PlantGrowthInput;

	Neuron *RotateLeftOutput;
	Neuron *RotateRightOutput;
	Neuron *ForwardOutput;
	Neuron *BackwardOutput;
	Neuron *LeftOutput;
	Neuron *RightOutput;
	Neuron *ReproduceOutput;
	Neuron *EatPlantsOutput;
	Neuron *EatCellOutput;
	Neuron *EyeRotateOutput;

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

		EyeInput = 0;
		CellProximityInput = 0;
		WallProximityInput = 0;
		EnergyInput = 0;
		HealthInput = 0;
		PlantGrowthInput = 0;

		RotateLeftOutput = 0;
		RotateRightOutput = 0;
		ForwardOutput = 0;
		BackwardOutput = 0;
		LeftOutput = 0;
		RightOutput = 0;
		ReproduceOutput = 0;
		EatPlantsOutput = 0;
		EatCellOutput = 0;
		EyeRotateOutput = 0;
	}

	void Update()
	{
		for (int i = 0; i < NeuronList.size(); i++)//Update Neurons with values
		{
			Neuron *neuron = NeuronList[i];
			if (neuron->Value > 1.0) { neuron->Value = 1.0; }
			if (neuron->Value < -1.0) { neuron->Value = -1.0; }

			for (int j = 0; j < neuron->SourceList.size(); j++)
			{
				Axon *axon = neuron->SourceList[j];
				double value = axon->Value;
				switch (neuron->Operation)
				{
				case 0:
					neuron->Value += value;
					break;
				case 1:
					neuron->Value -= value;
					break;
				case 2:
					neuron->Value *= value;
					break;
				case 3:
					if (value != 0) { neuron->Value /= value; }
					else { neuron->Value = 0; }
					break;
				case 4:
					break;
				case 5:
					if (value != 0) { neuron->Value = fmod(neuron->Value, value); }
					else { neuron->Value = 0; }
					break;
				}
				if (neuron->Value > 1.0) { neuron->Value = 1.0; }
				if (neuron->Value < -1.0) { neuron->Value = -1.0; }
			}
		}
		for (int i = 0; i < NeuronList.size(); i++)//update Axons with values
		{
			Neuron *neuron = NeuronList[i];
			for (int j = 0; j < neuron->DestinationList.size(); j++)
			{
				Axon *axon = neuron->DestinationList[j];
				axon->Value = neuron->Value * axon->Weighting;
			}
		}
	}
};

struct EyeAttributes
{
	double Fov = 0;
	double Range = 0;

	EyeAttributes()
	{
		Fov = DRand(0.0, PI);
		Range = DRand(0.0, MaxCellViewRange);
	}
	void Mutate()
	{
		if (Rand(0, MutationRate) == 0) { Fov = DRand(0.0, PI); }
		if (Rand(0, MutationRate) == 0) { Range = DRand(0.0, MaxCellViewRange); }
	}
};

struct Eye
{
	double Fov = 0;
	double Offset = 0;
	double Range = 0;
	double Value = 0;
	Eye(EyeAttributes attributes)
	{
		Fov = attributes.Fov;
		Range = attributes.Range;
	}
};

struct DNA
{
	double Size;
	double Speed;
	bool EatPlants;
	bool EatCell;
	EyeAttributes CellEyeAttributes;
	std::vector<NeuronAttributes> NeuronAttributesList;
	std::vector<AxonAttributes> AxonAttributesList;

	DNA()
	{
		Size = DRand(MinCellSize, MaxCellSize);
		Speed = DRand(0, MaxCellSpeed);
		EatPlants = !!Rand(0, 3);
		EatCell = !Rand(0, 5);

		CellEyeAttributes = EyeAttributes();
		NeuronAttributesList.push_back(NeuronAttributes(1, "EyeInput"));

		NeuronAttributesList.push_back(NeuronAttributes(1, "CellProximityInput"));
		NeuronAttributesList.push_back(NeuronAttributes(1, "WallProximityInput"));
		NeuronAttributesList.push_back(NeuronAttributes(1, "EnergyInput"));
		NeuronAttributesList.push_back(NeuronAttributes(1, "HealthInput"));
		NeuronAttributesList.push_back(NeuronAttributes(1, "PlantGrowthInput"));

		NeuronAttributesList.push_back(NeuronAttributes(2, "RotateLeftOutput"));
		NeuronAttributesList.push_back(NeuronAttributes(2, "RotateRightOutput"));
		NeuronAttributesList.push_back(NeuronAttributes(2, "ForwardOutput"));
		NeuronAttributesList.push_back(NeuronAttributes(2, "BackwardOutput"));
		NeuronAttributesList.push_back(NeuronAttributes(2, "LeftOutput"));
		NeuronAttributesList.push_back(NeuronAttributes(2, "RightOutput"));
		NeuronAttributesList.push_back(NeuronAttributes(2, "ReproduceOutput"));
		NeuronAttributesList.push_back(NeuronAttributes(2, "EatPlantsOutput"));
		NeuronAttributesList.push_back(NeuronAttributes(2, "EatCellOutput"));
		NeuronAttributesList.push_back(NeuronAttributes(2, "EyeRotateOutput"));

		int numAxons = Rand(0, (int)NeuronAttributesList.size() * 2);
		for (int i = 0; i < numAxons; i++) { AxonAttributesList.push_back(AxonAttributes((int)NeuronAttributesList.size() - 1)); }
	}

	DNA(DNA *parent)
	{
		Size = parent->Size;
		Speed = parent->Speed;
		EatPlants = parent->EatPlants;
		EatCell = parent->EatCell;

		CellEyeAttributes = parent->CellEyeAttributes;
		NeuronAttributesList = parent->NeuronAttributesList;
		AxonAttributesList = parent->AxonAttributesList;

		Mutate();
	}

	DNA(DNA *parentA, DNA *parentB)
	{
		if (Rand(0, 1) == 0) { Size = parentA->Size; }
		else { Size = parentB->Size; }
		if (Rand(0, 1) == 0) { Speed = parentA->Speed; }
		else { Speed = parentB->Speed; }
		if (Rand(0, 1) == 0) { EatPlants = parentA->EatPlants; }
		else { EatPlants = parentB->EatPlants; }
		if (Rand(0, 1) == 0) { EatCell = parentA->EatCell; }
		else { EatCell = parentB->EatCell; }

		//Eyes
		if (Rand(0, 1) == 0) { CellEyeAttributes = parentA->CellEyeAttributes; }
		else { CellEyeAttributes = parentB->CellEyeAttributes; }

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

		Mutate();
	}

	void Mutate()
	{
		if (Rand(0, MutationRate) == 0) { Size = DRand(MinCellSize, MaxCellSize); }
		if (Rand(0, MutationRate) == 0) { Speed = DRand(0, MaxCellSpeed); }
		if (Rand(0, MutationRate) == 0) { EatPlants = !!Rand(0, 3); }
		if (Rand(0, MutationRate) == 0) { EatCell = !Rand(0, 50); }

		CellEyeAttributes.Mutate();

		for (int i = 0; i < NeuronAttributesList.size(); i++)
		{
			NeuronAttributesList[i].Mutate();
		}
		int tries = Rand(0, 5);
		for (int i = 0; i < tries; i++) { if (Rand(0, MutationRate) == 0) { NeuronAttributesList.push_back(NeuronAttributes()); } }
		tries = Rand(0, 3);
		for (int i = 0; i < tries; i++) { if (Rand(0, MutationRate) == 0) { int pos = Rand(0, (int)NeuronAttributesList.size() - 1); if (NeuronAttributesList[pos].Type == 0) { NeuronAttributesList.erase(NeuronAttributesList.begin() + pos); } } }

		for (int i = 0; i < AxonAttributesList.size(); i++)
		{
			AxonAttributesList[i].Mutate((int)NeuronAttributesList.size() - 1);
		}
		tries = Rand(0, 6);
		for (int i = 0; i < tries; i++) { if (Rand(0, MutationRate / 3) == 0) { AxonAttributesList.push_back(AxonAttributes((int)AxonAttributesList.size())); } }
		tries = Rand(0, 3);
		for (int i = 0; i < tries; i++) { if (Rand(0, MutationRate / 3) == 0 && AxonAttributesList.size()) { int pos = Rand(0, (int)AxonAttributesList.size() - 1); AxonAttributesList.erase(AxonAttributesList.begin() + pos); } }

		//Axon Check
		for (int i = 0; i < AxonAttributesList.size();)
		{
			if (AxonAttributesList[i].SourceNeuronIndex >= NeuronAttributesList.size() || AxonAttributesList[i].DestinationNeuronIndex >= NeuronAttributesList.size())
			{
				AxonAttributesList.erase(AxonAttributesList.begin() + i);
			}
			else
			{
				i++;
			}
		}
	}
};

class Cell
{
public:
	double X; double Y;
	double Rotation;
	double Energy;
	double Health = MaxCellHealth;
	NeuralNetwork Network;
	bool Alive = false;
	Cell *Mate = 0;
	int BirthTime = 0;

	//DNA
	DNA Dna;
	double Size;
	double Speed;
	bool EatPlants;
	bool EatCell;
	Eye CellEye;

	Cell(int birthTime) :
		Dna(), CellEye(Dna.CellEyeAttributes)
	{
		X = Rand(-PlayWidth / 2, PlayWidth / 2); //rand() % PlayWidth;
		Y = Rand(-PlayHeight / 2, PlayHeight / 2); // rand() % PlayHeight;

		Rotation = DRand(0, TAU); //fmod((double)rand(), TAU);

		BirthTime = birthTime;

		//Dna
		Initilize();
	}

	Cell(Cell *parent, int birthTime) :
		Dna(&(parent->Dna)), CellEye(Dna.CellEyeAttributes)
	{
		{
			double rotation = DRand(0, TAU);
			X = parent->X + sin(rotation) * (4 * (parent->Size + Dna.Size));
			Y = parent->Y - cos(rotation) * (4 * (parent->Size + Dna.Size));
			if (X > PlayWidth / 2) { X = PlayWidth / 2; }
			else if (X < -PlayWidth / 2) { X = -PlayWidth / 2; }
			if (Y > PlayHeight / 2) { Y = PlayHeight / 2; }
			else if (Y < -PlayHeight / 2) { Y = -PlayHeight / 2; }
		}
		Rotation = DRand(0, TAU);

		BirthTime = birthTime;

		Initilize();
	}

	Cell(Cell *parentA, Cell *parentB, int birthTime) :
		Dna(&(parentA->Dna), &(parentB->Dna)), CellEye(Dna.CellEyeAttributes)
	{
		{
			double rotation = DRand(0, TAU);
			X = (parentA->X + parentB->X) / 2.0 + sin(rotation) * (4 * (max(parentA->Size, parentB->Size) + Dna.Size));
			Y = (parentA->Y + parentB->Y) / 2.0 - cos(rotation) * (4 * (max(parentA->Size, parentB->Size) + Dna.Size));
		}
		Rotation = DRand(0, TAU);

		BirthTime = birthTime;

		Initilize();
	}

	~Cell()
	{
		//delete CellEye;
		//CellEye = 0;
		Mate = 0;
	}

	void Initilize()
	{
		Energy = DRand(MinInitialCellEnergy, MaxInitialCellEnergy);

		Size = Dna.Size;
		Speed = Dna.Speed;
		EatPlants = Dna.EatPlants;
		EatCell = Dna.EatCell;

		//CellEye = new Eye(Dna.CellEyeAttributes);	

		for (NeuronAttributes attributes : Dna.NeuronAttributesList)
		{
			Neuron *neuron = new Neuron(attributes);
			Network.NeuronList.push_back(neuron);
			if (attributes.Label == "EyeInput") { Network.EyeInput = neuron; }
			if (attributes.Label == "CellProximityInput") { Network.CellProximityInput = neuron; }
			if (attributes.Label == "WallProximityInput") { Network.WallProximityInput = neuron; }
			if (attributes.Label == "EnergyInput") { Network.EnergyInput = neuron; }
			if (attributes.Label == "HealthInput") { Network.HealthInput = neuron; }
			if (attributes.Label == "PlantGrowthInput") { Network.PlantGrowthInput = neuron; }

			if (attributes.Label == "RotateLeftOutput") { Network.RotateLeftOutput = neuron; }
			if (attributes.Label == "RotateRightOutput") { Network.RotateRightOutput = neuron; }
			if (attributes.Label == "ForwardOutput") { Network.ForwardOutput = neuron; }
			if (attributes.Label == "BackwardOutput") { Network.BackwardOutput = neuron; }
			if (attributes.Label == "LeftOutput") { Network.LeftOutput = neuron; }
			if (attributes.Label == "RightOutput") { Network.RightOutput = neuron; }
			if (attributes.Label == "ReproduceOutput") { Network.ReproduceOutput = neuron; }
			if (attributes.Label == "EatPlantsOutput") { Network.EatPlantsOutput = neuron; }
			if (attributes.Label == "EatCellOutput") { Network.EatCellOutput = neuron; }
			if (attributes.Label == "EyeRotateOutput") { Network.EyeRotateOutput = neuron; }
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

		Alive = true;
	}

	void Update()
	{
		std::vector<Cell *> CollideList;
		Mate = 0;

		if (Alive)
		{
			{/*Update Senses*/}
			{
				Cell* cell;
				for (int i = 0; i < CellList.size(); i++)
				{
					cell = CellList[i];
					if (cell && cell != this && cell->Alive)
					{
						double dist = Dist(X, Y, cell->X, cell->Y);

						{/*Eye*/}
						{
							if (dist <= CellEye.Range)
							{
								//calculate within FOV
								//double angle = GetAngle(cell->X - X, cell->Y - Y);
								//if (angle > fmod(Rotation, TAU) + fmod(eye->Offset, TAU) - fmod(eye->Fov, TAU) && angle < fmod(Rotation, TAU) + fmod(eye->Offset, TAU) + fmod(eye->Fov, TAU))
								//{
								//	int val = (int)(255.0 - 255.0 * (dist / eye->Range));
								//	if (val > eye->Value) { eye->Value = val; }
								//}
								if (AngleBetweenPoints(X, Y, X + sin(CellEye.Offset + Rotation), Y - cos(CellEye.Offset + Rotation), cell->X, cell->Y) <= CellEye.Fov)
								{
									//double xa = X + sin(eye->Offset + Rotation); double ya = Y - cos(eye->Offset + Rotation);
									double val = (1.0 - (dist / CellEye.Range));
									if (val > CellEye.Value)
									{
										CellEye.Value = val;
									}
								}
							}
							else
							{
								CellEye.Value = 0;
							}

							Network.EyeInput->Value = CellEye.Value;
						}

						{/*CellProximity*/}
						{
							if (dist <= Size + cell->Size)
							{
								Network.CellProximityInput->Value = 1.0;
								CollideList.push_back(cell);
							}
						}

						{/*Miscellaneous*/}
						{
							int x = (int)((X + PlayWidth / 2) / (PlayWidth / PlantWidthDevisionNum)); if (x >= PlantWidthDevisionNum) { x = PlantWidthDevisionNum - 1; }
							int y = (int)((Y + PlayHeight / 2) / (PlayHeight / PlantHeightDevisionNum)); if (x >= PlantHeightDevisionNum) { x = PlantHeightDevisionNum - 1; }

							Network.PlantGrowthInput->Value = PlantArray[x][y] / 100.0;
						}
					}
				}
				Network.EnergyInput->Value = (Energy / MaxInitialCellEnergy);
				Network.HealthInput->Value = (Health / MaxCellHealth);
			}

			Network.Update();

			{/*Update Actions*/}
			{
				{/*Eat*/}
				{
					{/*Eat Cell*/}
					{
						if (EatCell)
						{
							Cell *cell;
							for (int i = 0; i < CollideList.size(); i++)
							{
								cell = CollideList[i];
								if (Size > cell->Size * 1.4)
								{
									double value = (abs(Network.EatCellOutput->Value) * (EatPlants ? 0.8 : 1.0)) * 6.0;

									//double before = cell->Health;
									//cell->Health -= (abs(Network.EatCellOutput->Value) * (EatPlants ? 0.8 : 1.0)) * 6.0;
									///Energy += (before - cell->Health) / 2.0;
									//if (cell->Health <= 0) { cell->Alive = false; }

									Energy -= abs(Network.EatPlantsOutput->Value) / 20.0;

									double cellHealth = cell->Health;
									Energy += (cellHealth - value < 0 ? cellHealth : value) / 2.0;
									cell->Health -= value;
									if (cell->Health <= 0) { cell->Alive = false; }
								}

							}
						}
					}
					{/*Eat Plants*/} 
					{
						if (EatPlants)
						{
							int x = (int)((X + PlayWidth / 2) / (PlayWidth / PlantWidthDevisionNum)); if (x >= PlantWidthDevisionNum) { x = PlantWidthDevisionNum - 1; }
							int y = (int)((Y + PlayHeight / 2) / (PlayHeight / PlantHeightDevisionNum)); if (x >= PlantHeightDevisionNum) { x = PlantHeightDevisionNum - 1; }
							double value = abs(Network.EatPlantsOutput->Value) * (EatCell ? 0.8 : 1.0);
							
							//double before = PlantArray[x][y];
							//PlantArray[x][y] -= value;
							//if (PlantArray[x][y] < 0.0) { PlantArray[x][y] = 0.0; }
							//Energy += ((before - PlantArray[x][y])) / 8.0;

							Energy -= abs(Network.EatPlantsOutput->Value) / 20.0;
							
							double PlantGrowth = PlantArray[x][y];
							Energy += (PlantGrowth - value < 0 ? PlantGrowth : value) / 6.0;
							PlantArray[x][y] -= value;
							if (PlantArray[x][y] < 0.0) { PlantArray[x][y] = 0.0; }
						}
					}
				}

				if (clock() - BirthTime > MaxCellAge) { Alive = false; Health = 0.0; }

				CellEye.Offset += Network.EyeRotateOutput->Value * (TAU / 20.0);

				if (CollideList.size()) { Mate = CollideList[Rand(0, (int)CollideList.size() - 1)]; }

				double rotationLeft;
				double rotationRight;
				rotationLeft = Network.RotateLeftOutput->Value * (TAU / 20.0);
				rotationRight = Network.RotateRightOutput->Value * (TAU / 20.0);
				Rotation += rotationLeft + rotationRight;

				double forward = 0;
				double back = 0;
				double left = 0;
				double right = 0;
				forward += Network.ForwardOutput->Value * Speed;
				back += Network.BackwardOutput->Value * Speed;
				left += Network.LeftOutput->Value * Speed;
				right += Network.RightOutput->Value * Speed;

				X += (right - left) * cos(Rotation) + (forward - back) * sin(Rotation);
				Y -= -(right - left) * sin(Rotation) + (forward - back) * cos(Rotation);

				if (X > PlayWidth / 2) { X = PlayWidth / 2; }
				else if (X < -PlayWidth / 2) { X = -PlayWidth / 2; }
				if (Y > PlayHeight / 2) { Y = PlayHeight / 2; }
				else if (Y < -PlayHeight / 2) { Y = -PlayHeight / 2; }

				Energy -= (abs(forward) + abs(back) + abs(left) + abs(right) + abs(rotationLeft) + abs(rotationRight) + Size / 55.0) / 150.0;
				if (Energy <= 0.0)
				{
					Energy = 0;
					Health -= 0.2;
				}
				if (Energy > MaxCellEnergy)
				{
					Energy = MaxCellEnergy;
				}

				if (Health < MaxCellHealth)
				{
					if (Energy - 1 > 0) { Health+=0.1; Energy-=0.1; }
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

