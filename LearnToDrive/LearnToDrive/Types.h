#pragma once

struct Point
{
	double X, Y;
	bool Defined = true;
	//Point() {}
	Point(double x = 0, double y = 0, bool defined = true)
	{
		X = x;
		Y = y;
		Defined = defined;
	}
	inline double Distance(Point other)
	{
		return sqrt(pow(other.X - X, 2) + pow(other.Y - Y, 2));
	}
};

struct Line
{
	double A = 0, B = 0, C = 0;
	Line(double a, double b, double c)
	{
		A = a; B = b; C = c;
	}
	Line(double x1, double y1, double x2, double y2)
	{
		MakeLine(x1, y1, x2, y2);
	}
	void MakeLine(double x1, double y1, double x2, double y2)
	{
		A = -(y2 - y1);
		B = (x2 - x1);
		C = A * x1 + B * y1;
	}
	/*bool Intersect(Line other)
	{
		bool parallel = A * other.A - other.B * B == 0 ? 1 : 0;//1 if parallel
		return !parallel;
	}
	Point Interesction(Line other)
	{
		double denom = A * other.A - other.B * B;
		Point point((B*other.C - other.B*C) / denom, (A*other.C - other.A*C) / denom);
	}*/
};

struct Segment
{
	Point points[2];
	Segment(double x1, double y1, double x2, double y2)
	{
		points[0].X = x1;
		points[0].Y = y1;

		points[1].X = x2;
		points[1].Y = y2;
	}
	Segment()
	{
		points[0].X = 0;
		points[0].Y = 0;

		points[1].X = 0;
		points[1].Y = 0;
	}
	Line ToLine()
	{
		return Line(points[0].X, points[0].Y, points[1].X, points[1].Y);
	}
	/*bool Intersect(Segment other)
	{
		Line line0 = ToLine();
		Line line1 = other.ToLine();

		bool parallel = line0.A * line1.A - line1.B * line0.B == 0 ? 1 : 0;//1 if parallel
		//bool within = 
		return !parallel;
	}*/
	Point Intersection(Segment other)
	{
		Line line0 = ToLine();
		Line line1 = other.ToLine();

		double denom = line0.A * line1.A - line1.B * line0.B;
		if (denom == 0)
		{
			return Point(0, 0, false);
		}
		Point point(-(line0.B*line1.C - line1.B*line0.C) / denom, (line0.A*line1.C - line1.A*line0.C) / denom);
		if (min(points[0].X, points[1].X) <= point.X && point.X <= max(points[0].X, points[1].X) &&
			min(points[0].Y, points[1].Y) <= point.Y && point.Y <= max(points[0].Y, points[1].Y))
		{
			//System::Console::WriteLine("Valid:{0}", point.Defined);
			System::Console::WriteLine(" X:{0} Y{1}", point.X, point.Y);
			return point;
		}
		//System::Console::WriteLine("NOT DEFINED");
		//System::Console::WriteLine("MIN(X:{0} Y:{1}) MAX(X:{2} Y:{3})  X:{4} Y{5}",
		//	min(points[0].X, points[1].X), min(points[0].Y, points[1].Y),
		//	max(points[0].X, points[1].X), max(points[0].Y, points[1].Y),
		//	point.X, point.Y);
		point.Defined = false;
		return point;
	}
};