// Collision_Test_Answers.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include<vector>
using namespace std;

/// A factor suitable to be passed to line \arg a as argument to calculate 
/// the intersection point.
/// \NOTE A value in the range [0, 1] indicates a point between
/// a.p() and a.p() + a.v().
/// \NOTE The result is Scalar::nan() if the lines do not intersect. 
/// \SEE  intersection_point
template <typename Scalar>
Scalar inline intersection(const Line2D<Scalar>& a, const Line2D<Scalar>& b)
{
	Scalar d = a.v().x() * b.v().y() - a.v().y() * b.v().x();
	if (!d) return Scalar::nan();
	else
	{
		Scalar n = (b.p().x() - a.p().x()) * b.v().y()
			- (b.p().y() - a.p().y()) * b.v().x();
		return n / d;
	}
}

/// The intersection of two lines.
/// \NOTE The result is Point2D::nan() if the lines do not intersect. 
template <typename Scalar>
Point2D<Scalar>
inline intersection_point(const Line2D<Scalar>& a, const Line2D<Scalar>& b)
{
	return a(intersection(a, b));
}


int main()
{
	vector<float> a;
	//a.push_back
	a = { 1, 2, 3 };
	intersection(a, a);
	return 0;
}

