
class Container;
#pragma once


#include "WinLib.h"
#include "WinLibTypes.h"
#include <windows.h>
#include <vector>
#include <string>
#include <objidl.h>
#include <gdiplus.h>
#pragma comment (lib,"Gdiplus.lib")
#pragma comment (lib, "winmm.lib")

class Container
{
private:
	std::vector<Container *> ContainerList;
	Container *Parent;
	Window *SrcWindow;

	HDC Hdc;
	HBITMAP Hbm;
	HFONT Hfnt;

public:
	int X, Y;
	int Width, Height;
	double ScaleX = 1, ScaleY = 1;
	int AbsX, AbsY;
	bool Show = true;

public:
	Container(int x, int y, int width, int height, Container *parent, Window *srcWindow);

	~Container();


	Container *CreateContainer(int x, int y, int width, int height);

	void UpdateTransformations();

	void Render();

public:
	void Translate(int x, int y);
	void SetPos(int x, int y);
	void Scale(double x, double y);

public:
	void FillRectangle(int x, int y, int width, int height, Colour colour);
	void DrawRectangle(int x, int y, int width, int height, Colour colour, float size = 0.5);
	void FillEllipse(int x, int y, int width, int height, Colour colour);
	void FillEllipse(int x, int y, int width, int height, Colour colour, double startAngle, double sweepAngle);
	void DrawEllipse(int x, int y, int width, int height, Colour colour, float size = 0.5);
	void DrawEllipse(int x, int y, int width, int height, Colour colour, double startAngle, double sweepAngle, float size = 0.5);
	void DrawLine(int x1, int y1, int x2, int y2, Colour colour, float size = 0.5);
	void DrawImage(int x, int y, int width, int height, std::string filename);
	void DrawText(int x, int y, std::string text, Font font);
};



