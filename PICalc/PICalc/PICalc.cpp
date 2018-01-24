// PICalc.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;

void PI();
void PI2();
void PI3();

int Sign(int in)
{
	return ((in % 2) - 0.5) > 0 ? 1 : -1;
}

void main()
{
	int Loops = 1100;// 00000000;
	long double Total = 0;
	//for (long double i = 0; i <= Loops-1; i++)
	//{
		////Total += static_cast<long double>(Sign(i) * (1.0 / (2.0 * i - 1.0)));
		//Total += static_cast<long double>(1.0 / pow(16.0, i)) * ((4.0 / (8 * i + 1.0)) - (2.0 / (8 * i + 4)) - (1.0 / (8 * i + 5)) - (1.0 / (8 * i + 6)));
	//}
	//Total *= 4;
	//cout << "Total:" << to_string(Total) << "\n\n";

	//int c = 10, d = 0, g = c;
	//for (; d != 0 || g != 0; --c) { g = c; cout << "D:" << d << "  G:" << g << "  C:" << c << "\n"; }
	//for (; d = 0, g = c; --c) { cout << "D:" << d << "  G:" << g << "  C:" << c << "\n"; }

	PI(); std::cout << "\n";
	
	std::string out = "\nPress Enter To Continue";
	std::cout << out;
	std::getline(std::cin, out);
}
//ZI

const int DigitsPerUpdate = 1;//1-4 Inclusive
const int NumberOfUpdates = 2;

const int CMul = 2;//2
const double Divisor = 5;//5

const double DigitMul = 1;//1
const int Digits = 14 * DigitMul * NumberOfUpdates;//14
int a = pow(10, DigitsPerUpdate), b, c = Digits, d, e, f[Digits], g;

void PI()
{
	for (; b - c;)f[b++] = a / 5;
	for (; d = 0, g = c * 2; c -= 14, printf("%.4d ", e + d / a), e = d%a)
		for (b = c; d += f[b] * a, printf("%i ", g), f[b] = d%--g, d /= g--, --b; d *= b);
}


void PI2()
{
	for (; b - c != 0;)
	{
		//f[b++] = a / 5;
		f[b] = a / 5;
		++b;
	}

	for (d = 0; g = c * 2; c -= 14)
	{
		//cout << "######\n";

		{
			b = c;
			do
			{
				--b;
				d += f[b] * a;
				f[b] = d%--g;
				d /= g--;
				if (b != 0) { d *= b; }
			} while (b != 0);
		}

		printf("%.1d", e + d / a);
		e = d%a;
	}
}


void PI3()
{
	for (; b - c != 0;)
	{
		//f[b++] = a / 5;
		f[b] = a / Divisor;
		++b;
	}

	for (d = 0; g = c * CMul; c -= 14 * DigitMul)
	{
		//cout << "######\n";

		{
			b = c;
			do
			{
				--b;
				d += f[b] * a;
				f[b] = d%--g;
				d /= g--;
				if (b != 0) { d *= b; }
			} while (b != 0);
		}

		printf("%.4d ", e + d / a);
		e = d%a;
	}
}
