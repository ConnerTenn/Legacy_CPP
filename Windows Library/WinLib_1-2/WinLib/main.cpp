
#include "WinLib.h"

Container *container1;
Container *container2;
Container *container3;

INT WINAPI WinMain(HINSTANCE HInstance, HINSTANCE, PSTR, INT iCmdShow)
{
	Window win(800, 400, HInstance, iCmdShow);
	win.Name = "WinLib_1-2";
	win.Create();

	container1 = win.CreateContainer(0, 0, 800, 400);
	container2 = container1->CreateContainer(100, 100, 50, 50);

	Window win2(600, 300, HInstance, iCmdShow);
	win2.Name = "WinLib_1-2";
	win2.Create();

	container3 = win2.CreateContainer(0, 0, 600, 300);

	Texture3 texture("Falvie.bmp");// , &win.Ps);

	bool done = false;
	while (!done)
	{
		{/*Event Handler*/}
		{
			win.UpdateMsg();
			win2.UpdateMsg();

			if (win.Msg.message == WM_QUIT || win2.Msg.message == WM_QUIT)
			{
				done = true;
			}
		}

		{/*Update*/} 
		{
			static float n = 0;
			container1->SetPos((int)(sin(n) * 50), (int)(-cos(n) * 50));
			container2->SetPos((int)(sin(2.0 * n) * 50 + 100), (int)(cos(2.0 * n) * 50 + 100));
			n += 0.05f;
		}

		{/*Render*/}
		{
			container1->FillRectangle(0, 0, 600, 500, Colour(255, 000, 000));
			container2->FillRectangle(0, 0, 500, 500, Colour(000, 255, 000));
			container1->DrawRectangle(0, 0, 299, 299, Colour(127, 127, 127), 5);
			container1->DrawLine(2, 0, 2, 500, Colour(255, 255, 000), 3);
			container1->FillEllipse(10, 10, 100, 100, Colour(127, 127, 127), TAU/8.0, TAU/4.0);
			container1->DrawEllipse(10, 10, 100, 100, Colour(000, 000, 000), TAU / 8.0, TAU / 4.0, 3);
			container1->DrawEllipse(35, 35, 50, 50, Colour(000, 000, 000), TAU / 8.0, TAU / 4.0, 3);
			container1->DrawImage(500, 0, texture.Width / 2, texture.Height / 2, &texture);
			container3->DrawText(0, 0, "[conner@winlib]$ listcommands\n\
				SetPos\n\
				Translate\n\
				Scale\n\
				\n\
				FillRectangle\n\
				DrawRectangle\n\
				FillEllipse\n\
				DrawEllipse\n\
				DrawLine\n\
				DrawImage\n\
				DrawText\n\
				\n\
				[conner@winlib]$ \v", Font());
			container3->FillRectangle(100, 260, 10, 10, Colour(000, 000, 255));
		}
	}
}

