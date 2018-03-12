
#include "Globals.h"

double Round(double value, int precision)
{
	return round(value * pow(10.0, precision)) / pow(10.0, precision);
}