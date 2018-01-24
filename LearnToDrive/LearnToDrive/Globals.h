
#ifndef _GLABALS_
#define _GLOBALS_

#include <Windows.h>
#include <string>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "Types.h"

#define PI 3.14159265358979323
#define TAU 2.0 * PI
#define FrameRate 200//120.0

/*
class Line
{
public:
	double A = 0, B = 0, C = 0;
	Line(double a, double b, double c);
	Line(double x1, double y1, double x2, double y2);
	void MakeLine(double x1, double y1, double x2, double y2);
};*/

double Round(double value, int precision);
Point XMRotation(Point Point, double Angle);
Point XMTranslation(Point Point, double X, double Y);
Point XMScaling(Point Point, double X, double Y);

System::Drawing::Point XMRotation(System::Drawing::Point Point, double Angle);
System::Drawing::Point XMTranslation(System::Drawing::Point Point, int X, int Y);
System::Drawing::Point XMScaling(System::Drawing::Point Point, int X, int Y);

#endif
