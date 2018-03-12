
#include "WinLib.h"


Window *Win;
Container *MainContainer;
bool Run = true;

INT WINAPI WinMain(HINSTANCE HInstance, HINSTANCE, PSTR, INT iCmdShow)
{
	Win = new Window(1200, 600, HInstance, iCmdShow);
	Win->Name = "Learning";
	Win->Create();

	MainContainer = Win->CreateContainer(0, 0, 1200, 600);

	while (Run)
	{
		MainContainer->Clear();

		{/*Event Handler*/ }
		{
			Win->UpdateMsg();

			if (Win->State.Quit == true)
			{
				Run = false;
			}
		}

		{
			static double a = 0; a += 2.0 * TAU * (Win->Delta / 1000.0);
			static int x = MainContainer->Width / 2, y = MainContainer->Height / 2;

			if (Win->Input->MouseState.LPressed) { x = Win->Input->MouseState.X < 0 ? x : Win->Input->MouseState.X; y = Win->Input->MouseState.Y < 0 ? y : Win->Input->MouseState.Y; }

			MainContainer->DrawRectangle(x + (int)(20.0 * -sin(a)) - 50, y + (int)(20.0 * cos(a)) - 50, 100, 100, Colour(0, 0, 255), 2);
			MainContainer->DrawText(x + (int)(20.0 * -sin(a)) - 50, y + (int)(20.0 * cos(a)) - 50, "Hello!", Font("Consolas", 20, Colour(100,150,255)));
			MainContainer->DrawEllipse(x + (int)(20.0 * -sin(a)) - 20, y + (int)(20.0 * cos(a)) - 20, 40, 40, Colour(0, 0, 255));
		}

		Win->Render();
	}

	delete Win; Win = 0;
}
