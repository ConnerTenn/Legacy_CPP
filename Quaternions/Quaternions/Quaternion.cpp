
#include "stdafx.h"
#include "Quaternion.h"

Quaternion::Quaternion(double InNum[4])
{
	Num[0] = InNum[0];
	Num[1] = InNum[1];
	Num[2] = InNum[2];
	Num[3] = InNum[3];
}

Quaternion::Quaternion(double InNum0, double InNum1, double InNum2, double InNum3)
{
	Num[0] = InNum0;
	Num[1] = InNum1;
	Num[2] = InNum2;
	Num[3] = InNum3;
}


double Quaternion::operator[](int Index)
{
	return Num[Index];
}


Quaternion Quaternion::operator+(Quaternion In)
{
	return{ Num[0] + In.Num[0], Num[1] + In.Num[1] , Num[2] + In.Num[2] , Num[3] + In.Num[3] };
}

Quaternion Quaternion::operator-(Quaternion In)
{
	return{ Num[0] - In.Num[0], Num[1] - In.Num[1] , Num[2] - In.Num[2] , Num[3] - In.Num[3] };
}

Quaternion Quaternion::operator*(Quaternion In)
{
	return
	{ 
		Num[0] * In.Num[0] - Num[1] * In.Num[1] - Num[2] * In.Num[2] - Num[3] * In.Num[3],
		Num[0] * In.Num[1] + Num[1] * In.Num[0] + Num[2] * In.Num[3] - Num[3] * In.Num[2],
		Num[0] * In.Num[2] - Num[1] * In.Num[3] + Num[2] * In.Num[0] + Num[3] * In.Num[1],
		Num[0] * In.Num[3] + Num[1] * In.Num[2] - Num[2] * In.Num[1] + Num[3] * In.Num[0]
	};
}

Quaternion Quaternion::operator/(Quaternion In)
{
	return
	{
		Num[0] / In.Num[0] - Num[1] / In.Num[1] - Num[2] / In.Num[2] - Num[3] / In.Num[3],
		Num[0] / In.Num[1] + Num[1] / In.Num[0] + Num[2] / In.Num[3] - Num[3] / In.Num[2],
		Num[0] / In.Num[2] - Num[1] / In.Num[3] + Num[2] / In.Num[0] + Num[3] / In.Num[1],
		Num[0] / In.Num[3] + Num[1] / In.Num[2] - Num[2] / In.Num[1] + Num[3] / In.Num[0]
	};
}

bool Quaternion::operator==(Quaternion In)
{
	return Num[0] == In.Num[0] && Num[1] == In.Num[1] && Num[2] == In.Num[2] && Num[3] == In.Num[3];
}
