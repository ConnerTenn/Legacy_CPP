
#include "Cell.h"
#include "Global.h"

void Initilize()
{
	//srand(Seed);

	for (int i = 0; i < MaxEntities; i++)
	{
		CellList.push_back(new Cell());
	}
}

void CleanUp()
{
	for (int i = 0; i < MaxEntities; i++)
	{
		delete CellList[i]; CellList[i] = 0;
	}

	delete Win; Win = 0;
}

void Update()
{
	while (!Done)
	{
		static double PreviousTime = 0;
		UpdateThreadDelta = static_cast<double>(clock() - PreviousTime);
		if (PreviousTime == 0) { UpdateThreadDelta = 0; }
		PreviousTime = clock();

		for (Cell *cell : CellList)
		{
			cell->Update();
		}
	}
}

INT WINAPI WinMain(HINSTANCE HInstance, HINSTANCE, PSTR, INT iCmdShow)
{
	Win = new Window(1200, 600, HInstance, iCmdShow);
	Win->Name = "Survival";
	Win->Create();

	EnvironmentSurface = Win->CreateContainer(0, 0, 600, 600);
	//PlaySurface = EnvironmentSurface->CreateContainer(ViewportX, ViewportY, PlayWidth, PlayHeight);
	//PlaySurface = EnvironmentSurface->CreateContainer(0, 0, PlayWidth, PlayHeight); PlaySurface->SetShow(false);
	AttributeSurface = Win->CreateContainer(600, 0, 600, 300);
	ControlSurface = Win->CreateContainer(600, 300, 600, 300);

	Initilize();

	Win->Focus = EnvironmentSurface;

	UpdateThread = new std::thread(Update);

	while (!Done)
	{
		{/*Event Handler*/}
		{
			Win->UpdateMsg();

			if (Win->State.Quit == true)
			{
				Done = true;
			}
		}

		{/*Update*/}
		{
			if (EnvironmentSurface->State.Focus)
			{
				if (Win->Input->KeyState[Win->Input->CharacterMap['W' - 65][0]].Pressed)
				{
					EnvironmentViewportY -= 1.0 * 1.0 / EnvironmentViewportScale;
				}
				if (Win->Input->KeyState[Win->Input->CharacterMap['S' - 65][0]].Pressed)
				{
					EnvironmentViewportY += 1.0 * 1.0 / EnvironmentViewportScale;
				}
				if (Win->Input->KeyState[Win->Input->CharacterMap['A' - 65][0]].Pressed)
				{
					EnvironmentViewportX -= 1.0 * 1.0 / EnvironmentViewportScale;
				}
				if (Win->Input->KeyState[Win->Input->CharacterMap['D' - 65][0]].Pressed)
				{
					EnvironmentViewportX += 1.0 * 1.0 / EnvironmentViewportScale;
				}
				if (Win->Input->KeyState[Win->Input->CharacterMap['E' - 65][0]].Pressed)
				{
					EnvironmentViewportScale * 1.01 < 2 ? EnvironmentViewportScale *= 1.01 : 0;
				}
				if (Win->Input->KeyState[Win->Input->CharacterMap['Q' - 65][0]].Pressed)
				{
					(PlayWidth + 200 / EnvironmentViewportScale) * (EnvironmentViewportScale * 0.99) >= EnvironmentSurface->Width ? EnvironmentViewportScale *= 0.99 : 0;
				}

				if (Win->Input->MouseState.LClick)
				{
					ActiveCell = 0;
					double mouseX = ReverseTransform(Win->Input->MouseState.X, EnvironmentViewportX, EnvironmentViewportScale, (double)EnvironmentSurface->Width / 2.0);
					double mouseY = ReverseTransform(Win->Input->MouseState.Y, EnvironmentViewportY, EnvironmentViewportScale, (double)EnvironmentSurface->Height / 2.0);
					for (Cell *cell : CellList)
					{
						if (Dist(mouseX, mouseY, cell->X, cell->Y) < cell->Size)
						{
							ActiveCell = cell;
						}
					}
				}
			}
			if (AttributeSurface->State.Focus)
			{
				if (Win->Input->KeyState[Win->Input->CharacterMap['W' - 65][0]].Pressed)
				{
					NetworkViewportY -= 1.0 * 1.0 / NetworkViewportScale;
				}
				if (Win->Input->KeyState[Win->Input->CharacterMap['S' - 65][0]].Pressed)
				{
					NetworkViewportY += 1.0 * 1.0 / NetworkViewportScale;
				}
				if (Win->Input->KeyState[Win->Input->CharacterMap['A' - 65][0]].Pressed)
				{
					NetworkViewportX -= 1.0 * 1.0 / NetworkViewportScale;
				}
				if (Win->Input->KeyState[Win->Input->CharacterMap['D' - 65][0]].Pressed)
				{
					NetworkViewportX += 1.0 * 1.0 / NetworkViewportScale;
				}
				if (Win->Input->KeyState[Win->Input->CharacterMap['E' - 65][0]].Pressed)
				{
					NetworkViewportScale * 1.01 < 2 ? NetworkViewportScale *= 1.01 : 0;
				}
				if (Win->Input->KeyState[Win->Input->CharacterMap['Q' - 65][0]].Pressed)
				{
					(NetworkWidth + 200 / NetworkViewportScale) * (NetworkViewportScale * 0.99) >= EnvironmentSurface->Width ? NetworkViewportScale *= 0.99 : 0;
				}

				if (Win->Input->MouseState.LClick && ActiveCell)
				{
					ActiveNeuron = 0;
					double mouseX = ReverseTransform(Win->Input->MouseState.X - AttributeSurface->AbsX, NetworkViewportX, NetworkViewportScale, (double)AttributeSurface->Width / 2.0);
					double mouseY = ReverseTransform(Win->Input->MouseState.Y - AttributeSurface->AbsY, NetworkViewportY, NetworkViewportScale, (double)AttributeSurface->Height / 2.0);
					for (Neuron *neuron : ActiveCell->Network.NeuronList)
					{
						if (Dist(mouseX, mouseY, neuron->X, neuron->Y) < 10.0)
						{
							ActiveNeuron = neuron;
						}
					}
				}
			}
		}

		{/*Render*/}
		{
			EnvironmentSurface->Clear();
			AttributeSurface->Clear();
			ControlSurface->Clear();
			//EnvironmentSurface->FillRectangle(0, 0, 600, 600, Colour(240, 240, 255));
			EnvironmentSurface->FillRectangle(0, 0, 600, 600, Colour(39, 67, 95));
			EnvironmentSurface->FillRectangle(
				(int)ApplyTransform((-PlayWidth / 2), EnvironmentViewportX, EnvironmentViewportScale, (double)EnvironmentSurface->Width / 2.0),
				(int)ApplyTransform((-PlayHeight / 2), EnvironmentViewportY, EnvironmentViewportScale, (double)EnvironmentSurface->Height / 2.0),
				(int)(PlayWidth * EnvironmentViewportScale),
				(int)(PlayHeight * EnvironmentViewportScale),
				Colour(0xD6, 0xDB, 0xD9));
			AttributeSurface->FillRectangle(0, 0, 600, 300, Colour(39, 67, 95));
			AttributeSurface->FillRectangle(
				(int)ApplyTransform((-NetworkWidth / 2), NetworkViewportX, NetworkViewportScale, (double)AttributeSurface->Width / 2.0),
				(int)ApplyTransform((-NetworkHeight / 2), NetworkViewportY, NetworkViewportScale, (double)AttributeSurface->Height / 2.0),
				(int)(NetworkWidth * NetworkViewportScale),
				(int)(NetworkHeight * NetworkViewportScale),
				Colour(59, 87, 115));
			//ControlSurface->FillRectangle(0, 0, 600, 300, Colour(59, 87, 115));


			{/*EnvironmentSurface*/}
			{
				EnvironmentSurface->DrawLine(
					(int)ApplyTransform((-PlayWidth / 2), EnvironmentViewportX, EnvironmentViewportScale, (double)EnvironmentSurface->Width / 2.0),
					(int)ApplyTransform(0.0, EnvironmentViewportY, EnvironmentViewportScale, (double)EnvironmentSurface->Height / 2.0),
					(int)ApplyTransform((PlayWidth / 2), EnvironmentViewportX, EnvironmentViewportScale, (double)EnvironmentSurface->Width / 2.0),
					(int)ApplyTransform(0.0, EnvironmentViewportY, EnvironmentViewportScale, (double)EnvironmentSurface->Height / 2.0),
					Colour(100, 100, 100));
				EnvironmentSurface->DrawLine(
					(int)ApplyTransform(0.0, EnvironmentViewportX, EnvironmentViewportScale, (double)EnvironmentSurface->Width / 2.0),
					(int)ApplyTransform((-PlayHeight / 2), EnvironmentViewportY, EnvironmentViewportScale, (double)EnvironmentSurface->Height / 2.0),
					(int)ApplyTransform(0.0, EnvironmentViewportX, EnvironmentViewportScale, (double)EnvironmentSurface->Width / 2.0),
					(int)ApplyTransform((PlayHeight / 2), EnvironmentViewportY, EnvironmentViewportScale, (double)EnvironmentSurface->Height / 2.0),
					Colour(100, 100, 100));
				for (Cell *cell : CellList)
				{
					int x = (int)ApplyTransform(cell->X, EnvironmentViewportX, EnvironmentViewportScale, (double)EnvironmentSurface->Width / 2.0);//(int)((cell->X - cell->Dna.Size) * ViewportScale);
					int y = (int)ApplyTransform(cell->Y, EnvironmentViewportY, EnvironmentViewportScale, (double)EnvironmentSurface->Height / 2.0);//(int)((cell->Y - cell->Dna.Size) * ViewportScale);
					int size = (int)(cell->Size * EnvironmentViewportScale);
					size < 1 ? size = 1 : 0;//Ensure Cell is always seen
					int width = 2 * size;
					int height = 2 * size;
					//draw rectangles when zoomed out
					if (cell == ActiveCell)
					{
						size == 1 ? EnvironmentSurface->FillRectangle(x - size, y - size, width, height, Colour(202, 81, 0)) : EnvironmentSurface->FillEllipse(x - size, y - size, width, height, Colour(202, 81, 0));
					}
					else
					{
						size == 1 ? EnvironmentSurface->FillRectangle(x - size, y - size, width, height, Colour(0, 122, 204)) : EnvironmentSurface->FillEllipse(x - size, y - size, width, height, Colour(0, 122, 204));
					}
					EnvironmentSurface->DrawLine(x, y, x + (int)(sin(cell->Rotation) * size), y - (int)(cos(cell->Rotation) * size), Colour(0, 72, 154), 2.0f);
				}
				for (Cell *cell : CellList)
				{
					if (cell == ActiveCell)
					{
						int x = (int)ApplyTransform(cell->X, EnvironmentViewportX, EnvironmentViewportScale, (double)EnvironmentSurface->Width / 2.0);//(int)((cell->X - cell->Dna.Size) * ViewportScale);
						int y = (int)ApplyTransform(cell->Y, EnvironmentViewportY, EnvironmentViewportScale, (double)EnvironmentSurface->Height / 2.0);//(int)((cell->Y - cell->Dna.Size) * ViewportScale);
						EnvironmentSurface->FillEllipse(x - 10, y - 10, 20, 20, Colour(202, 81, 0, 255 / 2));

						for (Eye *eye : cell->EyeList)
						{
							double range = eye->Range * EnvironmentViewportScale;
							EnvironmentSurface->DrawLine(x, y, x + (int)(sin(cell->Rotation + eye->Offset - eye->Fov) * range), y - (int)(cos(cell->Rotation + eye->Offset - eye->Fov) * range), Colour(0, 255, 0, 255 / 4), 2.0f);
							EnvironmentSurface->DrawLine(x, y, x + (int)(sin(cell->Rotation + eye->Offset + eye->Fov) * range), y - (int)(cos(cell->Rotation + eye->Offset + eye->Fov) * range), Colour(0, 255, 0, 255 / 4), 2.0f);
						}
					}
				}
				EnvironmentSurface->DrawText(10, 10,
					"ID: " + (ActiveCell ? std::to_string((long long)ActiveCell) : "N/A") +
					"\nX: " + (ActiveCell ? std::to_string(ActiveCell->X) : "N/A") +
					"\nY: " + (ActiveCell ? std::to_string(ActiveCell->Y) : "N/A") +
					"\nRotation:" + (ActiveCell ? std::to_string(ActiveCell->Rotation) : "N/A") +
					"\n\nScale: " + std::to_string(EnvironmentViewportScale),
					Font(Colour(0, 0, 0)));

				if (EnvironmentSurface->State.Focus)
				{
					EnvironmentSurface->DrawRectangle(0, 0, EnvironmentSurface->Width, EnvironmentSurface->Height, Colour(0, 0, 255));
				}
			}

			{/*AttributeSurface*/}
			{
				AttributeSurface->DrawLine(
					(int)ApplyTransform((-NetworkWidth / 2), NetworkViewportX, NetworkViewportScale, (double)AttributeSurface->Width / 2.0),
					(int)ApplyTransform(0.0, NetworkViewportY, NetworkViewportScale, (double)AttributeSurface->Height / 2.0),
					(int)ApplyTransform((NetworkWidth / 2), NetworkViewportX, NetworkViewportScale, (double)AttributeSurface->Width / 2.0),
					(int)ApplyTransform(0.0, NetworkViewportY, NetworkViewportScale, (double)AttributeSurface->Height / 2.0),
					Colour(100, 100, 100));
				AttributeSurface->DrawLine(
					(int)ApplyTransform(0.0, NetworkViewportX, NetworkViewportScale, (double)AttributeSurface->Width / 2.0),
					(int)ApplyTransform((-NetworkHeight / 2), NetworkViewportY, NetworkViewportScale, (double)AttributeSurface->Height / 2.0),
					(int)ApplyTransform(0.0, NetworkViewportX, NetworkViewportScale, (double)AttributeSurface->Width / 2.0),
					(int)ApplyTransform((NetworkHeight / 2), NetworkViewportY, NetworkViewportScale, (double)AttributeSurface->Height / 2.0),
					Colour(100, 100, 100));
				if (ActiveCell)
				{
					for (Neuron *neuron : ActiveCell->Network.NeuronList)
					{
						int x = (int)ApplyTransform(neuron->X, NetworkViewportX, NetworkViewportScale, (double)AttributeSurface->Width / 2.0);//(int)((neuron->X - neuron->Dna.Size) * ViewportScale);
						int y = (int)ApplyTransform(neuron->Y, NetworkViewportY, NetworkViewportScale, (double)AttributeSurface->Height / 2.0);//(int)((neuron->Y - neuron->Dna.Size) * ViewportScale);
						int size = (int)(10 * NetworkViewportScale);
						size < 1 ? size = 1 : 0;//Ensure Cell is always seen
						int width = 2 * size;
						int height = 2 * size;
						if (neuron == ActiveNeuron)
						{
							AttributeSurface->FillEllipse(x - size, y - size, width, height, Colour(202, 81, 0));
						}
						else
						{
							if (neuron->Type == 1)
							{
								AttributeSurface->FillEllipse(x - size, y - size, width, height, Colour(0, 204, 50));
							}
							else if (neuron->Type == 2)
							{
								AttributeSurface->FillEllipse(x - size, y - size, width, height, Colour(204, 204, 0));
							}
							else
							{
								AttributeSurface->FillEllipse(x - size, y - size, width, height, Colour(0, 122, 204));
							}
						}
					}
				}
				AttributeSurface->DrawText(10, 10,
					"ID: " + (ActiveNeuron ? std::to_string((long long)ActiveNeuron) : "N/A") +
					"\nX: " + (ActiveNeuron ? std::to_string(ActiveNeuron->X) : "N/A") +
					"\nY: " + (ActiveNeuron ? std::to_string(ActiveNeuron->Y) : "N/A") +
					"\nScale: " + std::to_string(NetworkViewportScale),
					Font(Colour(255, 255, 255)));

				if (AttributeSurface->State.Focus)
				{
					AttributeSurface->DrawRectangle(0, 0, AttributeSurface->Width, AttributeSurface->Height, Colour(0, 0, 255));
				}
			}

			{/*ControlSurface*/} 
			{
				ControlSurface->DrawText(10, 10,
					"Delta Time: " + std::to_string(Win->Delta) +
					"\nUpdateThread Delta Time: " + std::to_string(UpdateThreadDelta),
					Font(Colour(255, 255, 255)));

				if (ControlSurface->State.Focus)
				{
					ControlSurface->DrawRectangle(0, 0, ControlSurface->Width, ControlSurface->Height, Colour(0, 0, 255));
				}
			}


			Win->Render();
		}
	}

	UpdateThread->join();

	CleanUp();
}
