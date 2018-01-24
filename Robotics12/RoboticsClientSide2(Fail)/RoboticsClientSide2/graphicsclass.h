////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_


//////////////
// INCLUDES //
//////////////
#include <windows.h>
//#include <ObjIdl.h>
//#include <gdiplus.h>
//using namespace Gdiplus;
//#pragma comment (lib, "gdiplus.lib")


/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;


////////////////////////////////////////////////////////////////////////////////
// Class name: GraphicsClass
////////////////////////////////////////////////////////////////////////////////
class GraphicsClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Update();
	bool Render(HDC hdc);

private:
	void DrawRect(HDC hdc, int x1, int y1, int x2, int y2, COLORREF Colour);

};

#endif