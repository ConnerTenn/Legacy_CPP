////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "graphicsclass.h"


GraphicsClass::GraphicsClass()
{
}


GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}


GraphicsClass::~GraphicsClass()
{
}


bool GraphicsClass::Initialize(int screenHeight, int screenWidth, HWND hwnd)
{

	return true;
}


void GraphicsClass::Shutdown()
{

	return;
}


bool GraphicsClass::Update()
{

	return true;
}


bool GraphicsClass::Render(HDC hdc)
{
	COLORREF Colour;
	Colour = 0x0;
	//DrawRect(hdc, 0, 0, 200, 200, Colour);

	Colour = 0x00ff00;
	static int x = 0;
	DrawRect(hdc, 20+x, 20, 120+x, 120, Colour);
	TextOut(hdc, 0, 0, L"Hello World!", 13);
	x++;

	return true;
}



void GraphicsClass::DrawRect(HDC hdc, int x1, int y1, int x2, int y2, COLORREF Colour)
{
	for (int x = x1; x < x2; x++)
	{
		for (int y = y1; y < y2; y++)
		{
			SetPixel(hdc, x, y, Colour);
		}
	}
}