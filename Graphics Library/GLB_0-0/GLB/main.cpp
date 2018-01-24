
#include <SDL.h>
#include "GLB.h"

Window *MainWindow;
bool Run = true;

int main(int argc, char* args[])
{
	WindowProperties properties;
	MainWindow = new Window(properties);
	MainWindow->Create();

	while (Run)
	{
		{/*Event Handler*/ }
		{
			/*MainWindow.UpdateMsg();

			if (win.State.Quit == true || win2.State.Quit == true)
			{
				done = true;
			}*/
			MainWindow->WaitEvent();
			//MainWindow->PollEvent();
			Run = !MainWindow->State.Quit;
		}
	}

	delete MainWindow; MainWindow = 0;

	return 0;
}