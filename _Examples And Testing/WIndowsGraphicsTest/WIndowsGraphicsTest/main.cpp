
//#include <stdafx.h>
#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>
#include <string>
using namespace std;
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")
#pragma comment (lib, "winmm.lib")

DWORD xPos1, yPos1, xPos2, yPos2;
int zPos1, zPos2;
bool b1[11];
bool b2[11];

//use ASCII
VOID OnPaint(HWND hWnd, PAINTSTRUCT *ps)
{
	HDC hdc;
	HBITMAP hbmMEM, hbmOLD;
	HBRUSH hbrush;
	Graphics graphics(ps->hdc);
	//Gdiplus::SolidBrush Clear(Color(255, 0, 0, 0));
	//graphics.FillRectangle(&Clear, 0, 0, 800, 600);

	RECT rect;
	GetClientRect(hWnd, &rect);
	hdc = CreateCompatibleDC(ps->hdc);

	hbmMEM = CreateCompatibleBitmap(ps->hdc, rect.right - rect.left, rect.bottom - rect.top);
	hbmOLD = (HBITMAP)SelectObject(hdc, hbmMEM);
	hbrush = CreateSolidBrush(RGB(0,0,0));
	FillRect(ps->hdc, &rect, hbrush);
	
	static int x = 0;// , n = 0;
	//n > 0? x++, n=0: n++;
	x++;

	Pen pen(Color(255, 0, 255, 0));
	Gdiplus::SolidBrush brush(Color(255, 0, 255, 0));
	graphics.DrawRectangle(&pen, 100, 100, 65+10, 65+10);
	graphics.FillRectangle(&brush, xPos1/1000+100, yPos1/1000+100, 10, 10);

	graphics.DrawRectangle(&pen, 300, 100, 65, 65);
	graphics.FillRectangle(&brush, xPos1 / 1000 + 300, yPos1 / 1000 + 100, 1, 1);

	static int p = 0, s = 0;
	//s == 0 ? (n > 0 ? p++ : 0) : (n > 0 ? p-- : 0);
	s == 0 ? p++ : p--;
	p >= 100? s = 1 : 0;
	p <= 0? s = 0 : 0;
	graphics.FillRectangle(&brush, 10, 300, p, 40);

	string mystring = "Pos: {" + to_string(xPos1) + "," + to_string(yPos1) + "}";
	//WCHAR string[] = to_wide(mystring); //L"Hello World! ";
	//WCHAR string[10];

	//mystring[12] = char(p);

	//TextOut(hdc, 0, 0, mystring.c_str(), mystring.length());

	
	HFONT MyFont = CreateFont(20, 10, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_CHARACTER_PRECIS, NONANTIALIASED_QUALITY, DEFAULT_PITCH, TEXT("OCR"));

	SelectObject(ps->hdc, MyFont);
	RECT text;
	SetRect(&text, 100, 200, 900, 800);
	SetBkColor(ps->hdc, RGB(0, 0, 0));
	SetTextColor(ps->hdc, RGB(0, 255, 0));
	SetBkMode(ps->hdc, TRANSPARENT);
	DrawText(ps->hdc, mystring.c_str(), -1, &text, DT_NOCLIP);
	DeleteObject(MyFont);
	


	BitBlt(hdc, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, ps->hdc, 0, 0, SRCCOPY);
	SelectObject(hdc, hbmOLD);

	DeleteObject(hbmMEM);
	DeleteObject(hbmOLD);
	DeleteObject(hbrush);
	DeleteDC(hdc);
	// Initialize arguments.
	//Font myFont(L"Consolas", 10);
	//Gdiplus::PointF origin(0.0f, 0.0f);

	// Draw string.
	//graphics.DrawString(to_wide(mystring), 100, &myFont, { 0,0 }, &brush);


	//Sleep(1);
}

VOID OnPaint2(HWND hWnd, PAINTSTRUCT *ps)
{
	HDC hdc;
	HBITMAP hbmMEM, hbmOLD;
	HBRUSH hbrush;
	RECT rect;

	//Gdiplus::SolidBrush Clear(Color(255, 0, 0, 0));
	//graphics.FillRectangle(&Clear, 0, 0, 800, 600);

	GetClientRect(hWnd, &rect);
	hdc = CreateCompatibleDC(ps->hdc);

	hbmMEM = CreateCompatibleBitmap(ps->hdc, rect.right - rect.left, rect.bottom - rect.top);
	hbmOLD = (HBITMAP)SelectObject(hdc, hbmMEM);
	hbrush = CreateSolidBrush(RGB(0, 0, 0));
	FillRect(ps->hdc, &rect, hbrush);


	Graphics graphics(hdc);

	static int x = 0;// , n = 0;
					 //n > 0? x++, n=0: n++;
	x++;

	Pen pen(Color(255, 0, 255, 0));
	Gdiplus::SolidBrush brush(Color(255, 0, 255, 0));
	graphics.DrawRectangle(&pen, 100, 100, 65 + 10, 65 + 10);
	graphics.FillRectangle(&brush, xPos1 / 1000 + 100, yPos1 / 1000 + 100, 10, 10);

	graphics.DrawRectangle(&pen, 300, 100, 65+10, 65+10);
	graphics.FillRectangle(&brush, xPos2 / 1000 + 300, yPos2 / 1000 + 100, 10, 10);

	static int p = 0, s = 0;
	//s == 0 ? (n > 0 ? p++ : 0) : (n > 0 ? p-- : 0);
	s == 0 ? p++ : p--;
	p >= 100 ? s = 1 : 0;
	p <= 0 ? s = 0 : 0;
	graphics.FillRectangle(&brush, 10, 300, p, 40);

	string mystring = "Pos1: {" + to_string(xPos1) + "," + to_string(yPos1) + "}\n" + "Pos2: {" + to_string(xPos2) + "," + to_string(yPos2) + "}";
	//WCHAR string[] = to_wide(mystring); //L"Hello World! ";
	//WCHAR string[10];

	//mystring[12] = char(p);

	//TextOut(hdc, 0, 0, mystring.c_str(), mystring.length());


	HFONT MyFont = CreateFont(20, 10, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_CHARACTER_PRECIS, NONANTIALIASED_QUALITY, DEFAULT_PITCH, TEXT("OCR"));

	SelectObject(hdc, MyFont);
	RECT text;
	SetRect(&text, 100, 200, 900, 800);
	SetBkColor(hdc, RGB(0, 0, 0));
	SetTextColor(hdc, RGB(0, 255, 0));
	SetBkMode(hdc, TRANSPARENT);
	DrawText(hdc, mystring.c_str(), -1, &text, DT_NOCLIP);
	DeleteObject(MyFont);



	BitBlt(ps->hdc, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, hdc, 0, 0, SRCCOPY);
	SelectObject(hdc, hbmOLD);

	DeleteObject(hbmMEM);
	DeleteObject(hbmOLD);
	DeleteObject(hbrush);
	DeleteDC(hdc);
	// Initialize arguments.
	//Font myFont(L"Consolas", 10);
	//Gdiplus::PointF origin(0.0f, 0.0f);

	// Draw string.
	//graphics.DrawString(to_wide(mystring), 100, &myFont, { 0,0 }, &brush);


	//Sleep(1);
}

static void OnPaint3(HWND hWnd, LPPAINTSTRUCT lpPS)
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
		b1[i]? graphics.FillRectangle(&brush, 132, 210 + 10 * i, 10, 10):0;
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

	string mystring = "Pos1: {" + to_string(xPos1) + "," + to_string(yPos1) + "}\n" + "Pos2: {" + to_string(xPos2) + "," + to_string(yPos2) + "}";

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

}

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, PSTR, INT iCmdShow)
{
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

	/*
	hWnd = CreateWindow(
		TEXT("GettingStarted"),   // window class name
		TEXT("Getting Started"),  // window caption
		WS_OVERLAPPEDWINDOW,      // window style
		CW_USEDEFAULT,            // initial x position
		CW_USEDEFAULT,            // initial y position
		CW_USEDEFAULT,            // initial x size
		CW_USEDEFAULT,            // initial y size
		NULL,                     // parent window handle
		NULL,                     // window menu handle
		hInstance,                // program instance handle
		NULL);                    // creation parameters

	hWnd = CreateWindowEx(WS_EX_APPWINDOW, TEXT("WIndowsGraphicsTest"), TEXT("WIndowsGraphicsTest"),
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, NULL, NULL, hInstance, NULL);
	*/
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

	bool done = false;
	while (!done)
	{
		//GetMessage(&msg, NULL, 0, 0);
		PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
		//HDC          hdc;
		//PAINTSTRUCT  ps;

		InvalidateRect(hWnd, NULL, true);
		//hdc = BeginPaint(hWnd, &ps);
		//OnPaint(hdc);
		//EndPaint(hWnd, &ps);
		TranslateMessage(&msg);
		DispatchMessage(&msg);

		//if (msg.message == WM_PAINT)
		//{
		//	hdc = BeginPaint(hWnd, &ps);
		//	OnPaint(hdc);
		//	EndPaint(hWnd, &ps);
		//}
		if (msg.message == WM_QUIT)
		{
			done = true;
		}
	}

	GdiplusShutdown(gdiplusToken);
	return msg.wParam;
}  // WinMain

LRESULT CALLBACK WndProc(HWND hWnd, UINT message,
	WPARAM wParam, LPARAM lParam)
{
	//HDC          hdc;
	PAINTSTRUCT  ps;
	
	switch (message)
	{
	case WM_CREATE:
		joySetCapture(hWnd, JOYSTICKID1, 0, true);
		joySetCapture(hWnd, JOYSTICKID2, 0, true);
	case WM_PAINT:
		BeginPaint(hWnd, &ps);
		OnPaint3(hWnd, &ps);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_ERASEBKGND:
		return (LRESULT)1;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case MM_JOY1BUTTONDOWN:
		(wParam & JOY_BUTTON1) == JOY_BUTTON1 ? b1[0] = true : b1[0] = false;
		(wParam & JOY_BUTTON2) == JOY_BUTTON2 ? b1[1] = true : b1[1] = false;
		(wParam & JOY_BUTTON3) == JOY_BUTTON3 ? b1[2] = true : b1[2] = false;
		(wParam & JOY_BUTTON4) == JOY_BUTTON4 ? b1[3] = true : b1[3] = false;
		return 0;
	case MM_JOY1BUTTONUP:
		(wParam & JOY_BUTTON1) == JOY_BUTTON1 ? b1[0] = true : b1[0] = false;
		(wParam & JOY_BUTTON2) == JOY_BUTTON2 ? b1[1] = true : b1[1] = false;
		(wParam & JOY_BUTTON3) == JOY_BUTTON3 ? b1[2] = true : b1[2] = false;
		(wParam & JOY_BUTTON4) == JOY_BUTTON4 ? b1[3] = true : b1[3] = false;
		return 0;
	case MM_JOY2BUTTONDOWN:
		(wParam & JOY_BUTTON1) == JOY_BUTTON1 ? b2[0] = true : b2[0] = false;
		(wParam & JOY_BUTTON2) == JOY_BUTTON2 ? b2[1] = true : b2[1] = false;
		(wParam & JOY_BUTTON3) == JOY_BUTTON3 ? b2[2] = true : b2[2] = false;
		(wParam & JOY_BUTTON4) == JOY_BUTTON4 ? b2[3] = true : b2[3] = false;
		return 0;
	case MM_JOY2BUTTONUP:
		(wParam & JOY_BUTTON1) == JOY_BUTTON1 ? b2[0] = true : b2[0] = false;
		(wParam & JOY_BUTTON2) == JOY_BUTTON2 ? b2[1] = true : b2[1] = false;
		(wParam & JOY_BUTTON3) == JOY_BUTTON3 ? b2[2] = true : b2[2] = false;
		(wParam & JOY_BUTTON4) == JOY_BUTTON4 ? b2[3] = true : b2[3] = false;
		return 0;
	case MM_JOY1MOVE:
		//xPos1 = LOWORD(lParam);
		//yPos1 = HIWORD(lParam);
		return 0;
	case MM_JOY2MOVE:
		xPos2 = LOWORD(lParam);
		yPos2 = HIWORD(lParam);
		return 0;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
} // WndProc

