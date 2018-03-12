
#include <WS2tcpip.h>
#include <Windows.h>
#include <vector>
#include <string>
#include <time.h>
#include <objidl.h>
#include <gdiplus.h>
#include "InputHandler.h"

using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")
#pragma comment (lib, "winmm.lib")
#pragma comment(lib, "ws2_32.lib")

WSADATA Wsdata;
SOCKET ConnectionSocket;
struct addrinfo *server, client;
uint8_t SendBuffer[2];
char* port = "666";
char* ip = "192.168.42.1";

void NetInit()
{
	WSAStartup(MAKEWORD(2, 2), &Wsdata);
	//printw("SYSTEM::Connecting...");
	//refresh();

	client.ai_family = AF_INET;
	client.ai_socktype = SOCK_STREAM;
	client.ai_protocol = IPPROTO_TCP;

	getaddrinfo(ip, port, &client, &server);

	ConnectionSocket = socket(server->ai_family, server->ai_socktype, server->ai_protocol);

	if (connect(ConnectionSocket, server->ai_addr, server->ai_addrlen) == SOCKET_ERROR)
	{
		//printw("ERROR:: Error Connecting to address.\n");
		//refresh();
		WSACleanup();
		exit(0);
	}
}

void OnClose();

//DWORD xPos1 = 0, yPos1 = 0, xPos2 = 0, yPos2 = 0;
//DWORD zPos1 = 0, zPos2 = 0;
//bool b1[11];
//bool b2[11];

//clock_t t1;
//int Delta = 0;

std::vector<InputHandler*> inputHandlerList;

/*static void OnPaintOld(HWND hWnd, LPPAINTSTRUCT lpPS)
{
	RECT rc;
	HDC hdcMem;
	HBITMAP hbmMem, hbmOld;
	HBRUSH hbrBkGnd;
	HFONT hfntOld;
	HFONT hfnt = CreateFont(20, 10, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_CHARACTER_PRECIS, NONANTIALIASED_QUALITY, DEFAULT_PITCH, TEXT("OCR"));

	//
	// Get the size of the client rectangle.
	//

	GetClientRect(hWnd, &rc);

	//
	// Create a compatible DC.
	//

	hdcMem = CreateCompatibleDC(lpPS->hdc);

	//
	// Create a bitmap big enough for our client rectangle.
	//

	hbmMem = CreateCompatibleBitmap(lpPS->hdc,
		rc.right - rc.left,
		rc.bottom - rc.top);

	//
	// Select the bitmap into the off-screen DC.
	//

	hbmOld = (HBITMAP)SelectObject(hdcMem, hbmMem);

	//
	// Erase the background.
	//

	hbrBkGnd = CreateSolidBrush(RGB(0, 0, 0));
	FillRect(hdcMem, &rc, hbrBkGnd);
	DeleteObject(hbrBkGnd);

	Graphics graphics(hdcMem);


	Pen pen(Color(255, 0, 255, 0));
	Gdiplus::SolidBrush brush(Color(255, 0, 255, 0));


	static int poll = 0;

	JOYINFO data;
	JOYINFOEX dataEx;
	if (poll >= 0)
	{
		//joyGetPos(JOYSTICKID1, &data);

		dataEx.dwSize = sizeof(JOYINFOEX);
		dataEx.dwFlags = JOY_RETURNALL;
		joyGetPosEx(JOYSTICKID1, &dataEx);

		(dataEx.dwButtons & JOY_BUTTON5) == JOY_BUTTON5 ? b1[4] = true : b1[4] = false;
		//if (data.wZpos != 32767){ zPos1 = data.wZpos; }
		//if (dataEx.dwZpos != 32767) { zPos1 = dataEx.dwZpos; }
		zPos1 = dataEx.dwZpos;//32767
							  //zPos1 = data.wZpos;

		if (dataEx.dwFlags & JOY_RETURNX == JOY_RETURNX) { xPos1 = dataEx.dwXpos; }
		if (dataEx.dwFlags & JOY_RETURNY == JOY_RETURNY) { yPos1 = dataEx.dwYpos; }
		DWORD a = dataEx.dwFlags & JOY_RETURNBUTTONS;
		if (dataEx.dwSize != 3435973836)
		{
			poll = 5;
		}
		poll = 0;
	}
	else
	{
		poll++;
	}

	graphics.DrawRectangle(&pen, 100, 100, 65 + 10, 65 + 10);
	graphics.FillRectangle(&brush, xPos1 / 1000 + 100, yPos1 / 1000 + 100, 10, 10);

	graphics.DrawRectangle(&pen, 300, 100, 65 + 10, 65 + 10);
	graphics.FillRectangle(&brush, xPos2 / 1000 + 300, yPos2 / 1000 + 100, 10, 10);

	graphics.DrawRectangle(&pen, 105, 190, 65, 10);
	graphics.FillRectangle(&brush, 105, 190, zPos1 / 1000, 10);
	graphics.DrawRectangle(&pen, 305, 190, 65, 10);
	graphics.FillRectangle(&brush, 305, 190, zPos2 / 1000, 10);

	for (int i = 0; i < 11; i++)
	{
		graphics.DrawRectangle(&pen, 132, 210 + 10 * i, 10, 10);
		b1[i] ? graphics.FillRectangle(&brush, 132, 210 + 10 * i, 10, 10) : 0;
	}
	for (int i = 0; i < 4; i++)
	{
		graphics.DrawRectangle(&pen, 332, 210 + 10 * i, 10, 10);
		b2[i] ? graphics.FillRectangle(&brush, 332, 210 + 10 * i, 10, 10) : 0;
	}

	//
	// Select the font.
	//

	if (hfnt)
	{
		hfntOld = (HFONT)SelectObject(hdcMem, hfnt);
	}

	//
	// Render the image into the offscreen DC.
	//

	std::string mystring = "Pos1: {" + std::to_string(xPos1) + "," + std::to_string(yPos1) + "}\n" + "Pos2: {" + std::to_string(xPos2) + "," + std::to_string(yPos2) + "}";

	SetBkMode(hdcMem, TRANSPARENT);
	SetTextColor(hdcMem, RGB(0, 255, 0));
	DrawText(hdcMem, mystring.c_str(), -1, &rc, DT_LEFT);


	if (hfntOld)
	{
		SelectObject(hdcMem, hfntOld);
	}

	//
	// Blt the changes to the screen DC.
	//

	BitBlt(lpPS->hdc,
		rc.left, rc.top,
		rc.right - rc.left, rc.bottom - rc.top,
		hdcMem,
		0, 0,
		SRCCOPY);

	//
	// Done with off-screen bitmap and DC.
	//

	SelectObject(hdcMem, hbmOld);
	DeleteObject(hbmMem);
	DeleteObject(hbmOld);
	DeleteObject(hfnt);
	DeleteDC(hdcMem);

}*/

static void OnPaint(HWND hWnd, LPPAINTSTRUCT lpPS)
{
	RECT rc;
	HDC hdcMem;
	HBITMAP hbmMem, hbmOld;
	HBRUSH hbrBkGnd;
	HFONT hfntOld;
	HFONT hfnt = CreateFont(20, 10, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_CHARACTER_PRECIS, NONANTIALIASED_QUALITY, DEFAULT_PITCH, TEXT("OCR"));

	// Get the size of the client rectangle.
	GetClientRect(hWnd, &rc);

	// Create a compatible DC.
	hdcMem = CreateCompatibleDC(lpPS->hdc);

	// Create a bitmap big enough for our client rectangle.
	hbmMem = CreateCompatibleBitmap(lpPS->hdc,
		rc.right - rc.left,
		rc.bottom - rc.top);

	// Select the bitmap into the off-screen DC.
	hbmOld = (HBITMAP)SelectObject(hdcMem, hbmMem);

	// Erase the background.
	hbrBkGnd = CreateSolidBrush(RGB(0, 0, 0));
	FillRect(hdcMem, &rc, hbrBkGnd);
	DeleteObject(hbrBkGnd);

	// Init Graphics
	Graphics graphics(hdcMem);

	Pen pen(Color(255, 0, 255, 0));
	Gdiplus::SolidBrush brush(Color(255, 0, 255, 0));

	hfntOld = (HFONT)SelectObject(hdcMem, hfnt);
	SetBkMode(hdcMem, TRANSPARENT);
	SetTextColor(hdcMem, RGB(0, 255, 0));

	// == Begin Draw ==

	//JOYINFO data;
	//JOYINFOEX dataEx;
	//joyGetPos(JOYSTICKID1, &data);

	//dataEx.dwSize = sizeof(JOYINFOEX);
	//dataEx.dwFlags = JOY_RETURNALL;
	//joyGetPosEx(JOYSTICKID1, &dataEx);

	//(dataEx.dwButtons & JOY_BUTTON5) == JOY_BUTTON5 ? b1[4] = true : b1[4] = false;
	//if (data.wZpos != 32767){ zPos1 = data.wZpos; }
	//if (dataEx.dwZpos != 32767) { zPos1 = dataEx.dwZpos; }
	//zPos1 = dataEx.dwZpos;//32767
							//zPos1 = data.wZpos;

	//if (dataEx.dwFlags & JOY_RETURNX == JOY_RETURNX) { xPos1 = dataEx.dwXpos; }
	//if (dataEx.dwFlags & JOY_RETURNY == JOY_RETURNY) { yPos1 = dataEx.dwYpos; }
	//DWORD a = dataEx.dwFlags & JOY_RETURNBUTTONS;

	int xPos1 = int(Map({ 85, 45 }, { 0, 100 }, inputHandlerList[0]->GetValue()));
	int yPos1 = int(Map({ 40, 80 }, { 0, 100 }, inputHandlerList[1]->GetValue()));
	int zPos1 = int(Map({ 90, 30 }, { 0, 100 }, inputHandlerList[2]->GetValue()));

	int xPos2 = int(Map({ 110, 50 }, { 0, 100 }, inputHandlerList[4]->GetValue()));
	int yPos2 = int(Map({ 110, 50 }, { 0, 100 }, inputHandlerList[5]->GetValue()));
	int zPos2 = int(Map({ 90, 30 }, { 0, 100 }, inputHandlerList[2]->GetValue()));
//ayy lmao
	graphics.DrawRectangle(&pen, 100, 100, 100 + 10, 100 + 10);
	graphics.FillRectangle(&brush, xPos1 + 100, yPos1 + 100, 10, 10);

	graphics.DrawRectangle(&pen, 300, 100, 100 + 10, 100 + 10);
	graphics.FillRectangle(&brush, xPos2 + 300, yPos2 + 100, 10, 10);

	graphics.DrawRectangle(&pen, 105, 220, 100, 10);
	graphics.FillRectangle(&brush, 105, 220, zPos1, 10);
	graphics.DrawRectangle(&pen, 305, 220, 100, 10);
	graphics.FillRectangle(&brush, 305, 220, zPos2, 10);

	graphics.DrawRectangle(&pen, 150, 240, 10, 10);
	inputHandlerList[3]->GetValue() ? graphics.FillRectangle(&brush, 150, 240, 10, 10) : 0;

	/*for (int i = 0; i < 11; i++)
	{
		graphics.DrawRectangle(&pen, 132, 210 + 10 * i, 10, 10);
		b1[i] ? graphics.FillRectangle(&brush, 132, 210 + 10 * i, 10, 10) : 0;
	}
	for (int i = 0; i < 4; i++)
	{
		graphics.DrawRectangle(&pen, 332, 210 + 10 * i, 10, 10);
		b2[i] ? graphics.FillRectangle(&brush, 332, 210 + 10 * i, 10, 10) : 0;
	}*/

	std::string mystring = "Pos1: {" + std::to_string(xPos1) + "," + std::to_string(yPos1) + "}\n" + "Pos2: {" + std::to_string(xPos2) + "," + std::to_string(yPos2) + "}";

	DrawText(hdcMem, mystring.c_str(), -1, &rc, DT_LEFT);

	mystring = "\n\n" + std::to_string(inputHandlerList[6]->GetValue());
	DrawText(hdcMem, mystring.c_str(), -1, &rc, DT_LEFT);
	// == End Draw ==

	// Render the image into the offscreen DC.
	SelectObject(hdcMem, hfntOld);
	
	// Blt the changes to the screen DC.
	BitBlt(lpPS->hdc,
		rc.left, rc.top,
		rc.right - rc.left, rc.bottom - rc.top,
		hdcMem,
		0, 0,
		SRCCOPY);

	// Done with off-screen bitmap and DC.
	SelectObject(hdcMem, hbmOld);
	DeleteObject(hbmMem);
	DeleteObject(hbmOld);
	DeleteObject(hfnt);
	DeleteDC(hdcMem);

}

void Loop(HWND &hWnd, MSG &msg)
{
	JOYINFOEX dataEx1;
	JOYINFOEX dataEx2;

	bool done = false;
	while (!done)
	{
		dataEx1.dwSize = sizeof(JOYINFOEX);
		dataEx1.dwFlags = JOY_RETURNALL;
		joyGetPosEx(JOYSTICKID1, &dataEx1);
		dataEx2.dwSize = sizeof(JOYINFOEX);
		dataEx2.dwFlags = JOY_RETURNALL;
		joyGetPosEx(JOYSTICKID2, &dataEx2);

		for (InputHandler* object : inputHandlerList)
		{
			UINT ID = object->GetJoyID();
			if (ID == JOYSTICKID1) { object->Update(dataEx1); }
			if (ID == JOYSTICKID2) { object->Update(dataEx2); }
			object->Send(&ConnectionSocket);
		}

		PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);

		InvalidateRect(hWnd, NULL, true);
		TranslateMessage(&msg);
		DispatchMessage(&msg);

		if (msg.message == WM_QUIT)
		{
			done = true;
		}
	}
}

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, PSTR, INT iCmdShow)
{
	NetInit();
	//atexit(OnClose);

	HWND                hWnd;
	MSG                 msg;
	WNDCLASS            wndClass;
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;

	// Initialize GDI+.
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	wndClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wndClass.lpfnWndProc = WndProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = hInstance;
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = TEXT("WIndowsGraphicsTest");

	RegisterClass(&wndClass);

	hWnd = CreateWindow(
		TEXT("WIndowsGraphicsTest"),
		TEXT("WIndowsGraphicsTest"),
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		800,
		600,
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowWindow(hWnd, iCmdShow);
	UpdateWindow(hWnd);

	/*bool done = false;
	while (!done)
	{
		PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);

		InvalidateRect(hWnd, NULL, true);
		TranslateMessage(&msg);
		DispatchMessage(&msg);

		

		if (msg.message == WM_QUIT)
		{
			done = true;
		}
	}*/
	Loop(hWnd, msg);

	GdiplusShutdown(gdiplusToken);
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message,
	WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT  ps;

	switch (message)
	{
	case WM_CREATE:
		//UINT joyID, int trigger, std::vector<float> range, int type, uint8_t id
		inputHandlerList.push_back(new InputHandler(JOYSTICKID1, 1, 1, { 85, 45 }, 0, 00));		//DriveXAxis
		inputHandlerList.push_back(new InputHandler(JOYSTICKID1, 2, 1, { 40, 80 }, 0, 01));		//DriveYAxis
		inputHandlerList.push_back(new InputHandler(JOYSTICKID1, 4, 5, { 100, 60 }, 2, 03));	//Claw Rotation
		inputHandlerList.push_back(new InputHandler(JOYSTICKID1, 3, 2, { 130, 30 }, 2, 05));	//Claw Pivot

		inputHandlerList.push_back(new InputHandler(JOYSTICKID2, 1, 1, { 110, 50 }, 0, 02));	//Arm Rotation
		inputHandlerList.push_back(new InputHandler(JOYSTICKID2, 2, 1, { 110, 50 }, 0, 07));	//Arm Pivot
		inputHandlerList.push_back(new InputHandler(JOYSTICKID2, 3, 2, { 130, 30 }, 2, 06));	//Arm Extension
		inputHandlerList.push_back(new InputHandler(JOYSTICKID2, 4, 5, { 80, 20 }, 2, 04));	//Claw Grip

		inputHandlerList.push_back(new InputHandler(JOYSTICKID2, 1, 1, { 1, 0 }, 1, 01));		//Suction Cup
		inputHandlerList.push_back(new InputHandler(JOYSTICKID1, 1, 1, { 1, 0 },
			1, 02));		//Pump
		
		//Pump
		return 0;
	case WM_PAINT:
		BeginPaint(hWnd, &ps);
		OnPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_ERASEBKGND:
		return (LRESULT)1;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
} // WndProc

