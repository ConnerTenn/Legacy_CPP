#pragma once
///*
#include <vector>

struct Complex
{
	long double Num[2] = { 0.0, 0.0 };
	Complex()
	{
		Num[0] = 0;
		Num[1] = 0;
	}
	Complex(long double InNum[2])
	{
		Num[0] = InNum[0];
		Num[1] = InNum[1];
	}
	Complex(long double InNum0, long double InNum1)
	{
		Num[0] = InNum0;
		Num[1] = InNum1;
	}
	Complex operator+(Complex In)
	{
		return{ this->Num[0] + In.Num[0], this->Num[1] + In.Num[1] };
	}
	Complex operator-(Complex In)
	{
		return{ this->Num[0] - In.Num[0], this->Num[1] - In.Num[1] };
	}
	Complex operator*(Complex In)
	{
		return{ this->Num[0] * In.Num[0] - this->Num[1] * In.Num[1], this->Num[0] * In.Num[1] + this->Num[1] * In.Num[0] };
	}
	Complex operator/(Complex In)
	{
		return{ this->Num[0] / In.Num[0] - this->Num[1] / In.Num[1], this->Num[0] / In.Num[1] + this->Num[1] / In.Num[0] };
	}
	bool operator==(Complex In)
	{
		return this->Num[0] == In.Num[0] && this->Num[1] == In.Num[1];
	}
};

bool TendsToInfinity(Complex In)
{
	std::vector<Complex> NumberList = {};
	Complex Total(0, 0);

	bool Continue = true;
	int Count = 0;
	while (Total.Num[0] < 2.0 && Continue)
	{
		Total = Total * Total + In;
		std::vector<Complex>::iterator It = find(NumberList.begin(), NumberList.end(), Total);
		if (It != NumberList.end() && NumberList.size() > 0)
		{
			Continue = false;
		}
		else
		{
			NumberList.push_back(Total);
		}
		Count++;
		if (Count > 10000) { Continue = false; }
		//if (Count > 1000) { Continue = false; }
	}
	if (Continue)
	{
		return false;
	}
	else
	{
		return true;
	}
}


std::vector<int> waveLengthToRGB(double Wavelength);
float Map(std::vector<float> InRange, std::vector<float> NextRange, float Value);
int MaxCount = 10000;
double Exponent = 1.03;

std::vector<int> TendsToInfinityColour(Complex In)
{
	std::vector<Complex> NumberList = {};
	Complex Total(0, 0);

	bool Continue = true;
	int Count = 0;
	while (Total.Num[0] < 2.0 && Continue)
	{
		Total = Total * Total + In;
		std::vector<Complex>::iterator It = find(NumberList.begin(), NumberList.end(), Total);
		if (It != NumberList.end() && NumberList.size() > 0)
		{
			Continue = false;
		}
		else
		{
			NumberList.push_back(Total);
		}
		Count++;
		if (Count > MaxCount) { Continue = false; }
		//if (Count > 1000) { Continue = false; }
	}
	if (Continue)
	{
		//return waveLengthToRGB(Map({ 0.0, 10000.0}, { 700.0, 400.0 }, static_cast<double>(-10000.0*pow(1.05, -(Count))+10000.0 )));
		//can adjust wavelength range
		//modifiesr above
		return waveLengthToRGB(Map({ 0.0, static_cast<float>(MaxCount) }, { 700.0, 400.0 }, static_cast<double>(-static_cast<double>(MaxCount)*pow(Exponent, -(Count)) + static_cast<double>(MaxCount))));
		//return false;
		if (Count <= 4) { return { 255, 0, 0 }; }
		if (Count <= 6) { return{ 230, 40, 0 }; }
		if (Count <= 10) { return{ 210, 90, 0 }; }
		if (Count <= 50) { return { 190, 100, 0 }; }
		if (Count <= 100) { return { 240, 240, 0 }; }
		if (Count <= 500) { return { 0, 255, 0 }; }
		if (Count <= 1000) { return { 255, 255, 255 }; }
		if (Count <= 5000) { return { 255, 255, 255 }; }
		if (Count <= 10000) { return { 255, 255, 255 }; }
	}
	else
	{
		return{ 0, 0, 0 };
	}
}
//*/

double Map(std::vector<double> InRange = { 0, 100 }, std::vector<double> NextRange = { 0, 100 }, double Value = 50)
{
	float m = (NextRange[1] - NextRange[0]) / (InRange[1] - InRange[0]);
	float b = NextRange[0] - (m * InRange[0]);
	return m * Value + b;

	//return (NextRange[1] - NextRange[0]) / (InRange[1] - InRange[0]) * Value + (NextRange[0] + NextRange[1]) / 2.0;
	//return minOutRange + (maxOutRange - minOutRange) * inValue / (maxInRange - minInRange);
	//return NextRange[0] + (NextRange[1] - NextRange[0]) * (Value / (InRange[1] - InRange[0]));
}

float Map(std::vector<float> InRange = { 0, 100 }, std::vector<float> NextRange = { 0, 100 }, float Value = 50)
{
	float m = (NextRange[1] - NextRange[0]) / (InRange[1] - InRange[0]);
	float b = NextRange[0] - (m * InRange[0]);
	return m * Value + b;

	//return (NextRange[1] - NextRange[0]) / (InRange[1] - InRange[0]) * Value + (NextRange[0] + NextRange[1]) / 2.0;
	//return minOutRange + (maxOutRange - minOutRange) * inValue / (maxInRange - minInRange);
	//return NextRange[0] + (NextRange[1] - NextRange[0]) * (Value / (InRange[1] - InRange[0]));
}

std::vector<int> waveLengthToRGB(double Wavelength)
{
	double Gamma = 0.80;
	double IntensityMax = 255;

	double factor;
	double Red, Green, Blue;

	if ((Wavelength >= 380) && (Wavelength<440))
	{
		Red = -(Wavelength - 440) / (440 - 380);
		Green = 0.0;
		Blue = 1.0;
	}
	else if ((Wavelength >= 440) && (Wavelength<490))
	{
		Red = 0.0;
		Green = (Wavelength - 440) / (490 - 440);
		Blue = 1.0;
	}
	else if ((Wavelength >= 490) && (Wavelength<510))
	{
		Red = 0.0;
		Green = 1.0;
		Blue = -(Wavelength - 510) / (510 - 490);
	}
	else if ((Wavelength >= 510) && (Wavelength<580))
	{
		Red = (Wavelength - 510) / (580 - 510);
		Green = 1.0;
		Blue = 0.0;
	}
	else if ((Wavelength >= 580) && (Wavelength<645))
	{
		Red = 1.0;
		Green = -(Wavelength - 645) / (645 - 580);
		Blue = 0.0;
	}
	else if ((Wavelength >= 645) && (Wavelength<781))
	{
		Red = 1.0;
		Green = 0.0;
		Blue = 0.0;
	}
	else
	{
		Red = 0.0;
		Green = 0.0;
		Blue = 0.0;
	};

	// Let the intensity fall off near the vision limits

	if ((Wavelength >= 380) && (Wavelength<420))
	{
		factor = 0.3 + 0.7*(Wavelength - 380) / (420 - 380);
	}
	else if ((Wavelength >= 420) && (Wavelength<701))
	{
		factor = 1.0;
	}
	else if ((Wavelength >= 701) && (Wavelength<781))
	{
		factor = 0.3 + 0.7*(780 - Wavelength) / (780 - 700);
	}
	else
	{
		factor = 0.0;
	};


	//int[] rgb = new int[3];
	std::vector<int> rgb = { 0,0,0 };

	// Don't want 0^x = 1 for x <> 0
	rgb[0] = Red == 0.0 ? 0 : static_cast<int>(round(IntensityMax * pow(Red * factor, Gamma)));
	rgb[1] = Green == 0.0 ? 0 : static_cast<int>(round(IntensityMax * pow(Green * factor, Gamma)));
	rgb[2] = Blue == 0.0 ? 0 : static_cast<int>(round(IntensityMax * pow(Blue * factor, Gamma)));
	
	return rgb;
}
