
#include "Globals.h"

double Round(double value, int precision)
{
	return round(value * pow(10.0, precision)) / pow(10.0, precision);
}

Point XMRotation(Point point, double Angle)
{
	return Point(
		point.X * cos(Angle) + point.Y * sin(Angle),
		point.X * sin(Angle) - point.Y * cos(Angle)
		);
	return Point(
		point.X * cos(Angle) + point.Y * sin(Angle),
		point.X * sin(Angle) - point.Y * cos(Angle)
		);
}
Point XMTranslation(Point point, double X, double Y)
{
	return Point(point.X + X, point.Y + Y);
}
Point XMScaling(Point point, double X, double Y)
{
	return Point(point.X * X, point.Y * Y);
}


System::Drawing::Point XMRotation(System::Drawing::Point Point, double Angle)
{
	return System::Drawing::Point(
		static_cast<int>(static_cast<double>(Point.X) * cos(Angle) + static_cast<double>(Point.Y) * sin(Angle)),
		static_cast<int>(static_cast<double>(Point.X) * sin(Angle) - static_cast<double>(Point.Y) * cos(Angle))
		);
	return System::Drawing::Point(
		static_cast<int>(static_cast<double>(Point.X) * Round(cos(Angle), 5) + static_cast<double>(Point.Y) * Round(sin(Angle), 5)),
		static_cast<int>(static_cast<double>(Point.X) * Round(sin(Angle), 5) - static_cast<double>(Point.Y) * Round(cos(Angle), 5))
		);
}
System::Drawing::Point XMTranslation(System::Drawing::Point Point, int X, int Y)
{
	return System::Drawing::Point(Point.X + X, Point.Y + Y);
}
System::Drawing::Point XMScaling(System::Drawing::Point Point, int X, int Y)
{
	return System::Drawing::Point(Point.X * X, Point.Y * Y);
}
