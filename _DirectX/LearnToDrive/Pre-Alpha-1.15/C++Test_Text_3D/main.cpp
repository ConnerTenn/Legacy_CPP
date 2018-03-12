/*
Beginning DirectX 11 Game Programming
By Allen Sherrod and Wendy Jones
*/


#include"Levels.h"
#include"GameObject.h"
#include"Levels.h"
#include"Globals.h"

//#include<xnamath.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPWSTR cmdLine, int cmdShow)
{
	UNREFERENCED_PARAMETER(prevInstance);
	UNREFERENCED_PARAMETER(cmdLine);

	WNDCLASSEX wndClass = { 0 };
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.style = CS_DROPSHADOW;
	wndClass.style = CS_BYTEALIGNWINDOW;
	wndClass.lpfnWndProc = WndProc;
	wndClass.hInstance = hInstance;
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = "DX11BookWindowClass";

	if (!RegisterClassEx(&wndClass))
		return -1;

	RECT rc = { 0, 0, static_cast<long>(Width), static_cast<long>(Height) };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

	HWND hwnd = CreateWindowA("DX11BookWindowClass", "Pre-Alpha-1.15", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top,
		NULL, NULL, hInstance, NULL);

	if (!hwnd)
		return -1;

	ShowWindow(hwnd, cmdShow);

	//Levels Level;
	//Level.LoadLevel1(hInstance, hwnd);
	//MSG msg = { 0 };
	///*
	Levels levels;
	levels.Initialize(hInstance, hwnd);

	MSG msg = { 0 };
	double Delta = 0.0;
	clock_t t1 = 0;

	levels.LoadLevelsContent();
	levels.LoadLevel1Content(msg, Delta, t1);

	/*while (msg.message != WM_QUIT)
	{
		t1 = clock();
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		//Old = Delta;
		//Delta = clock() - Old;

		// Update and Draw
		levels.UpdateLevel1(static_cast<float>(Delta));
		levels.RenderLevel1();
		double Delay = 0.0;
		double ObjectiveTime = 0.02;
		if (Delta <= ObjectiveTime)
		{
			Delay = (ObjectiveTime - Delta);
		}
		//DBOUT("Delay:" << Delay << " Delta Time:" << Delta << "\n");
		//Old = Elapsed;

		//t2 = clock();
		//((float)t) / CLOCKS_PER_SEC)
		Delta = static_cast<double>(clock() - t1) / CLOCKS_PER_SEC;
		Sleep(static_cast<DWORD>(Delay));
	}*/

	// levels Shutdown
	//levels.UnloadLevel1Content();
	//levels.Shutdown();//*/
	return static_cast<int>(msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT paintStruct;
	HDC hDC;

	switch (message)
	{
	case WM_PAINT:
		hDC = BeginPaint(hwnd, &paintStruct);
		EndPaint(hwnd, &paintStruct);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}

	return 0;
}
