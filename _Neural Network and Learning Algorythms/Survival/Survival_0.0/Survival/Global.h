
#pragma once
#include "WinLib.h"
#include "Cell.h"
#include <random>
#include <thread>
//#include <vector>
//#include <stdlib.h>

#undef max

//### Window ###

//int Seed = 0;
std::minstd_rand0 Random(0);

bool Done = false;

Window *Win;
	Container *EnvironmentSurface;
	Container *AttributeSurface;
	Container *ControlSurface;

std::thread *UpdateThread;
double UpdateThreadDelta;

Cell *ActiveCell;
Neuron *ActiveNeuron;

//### Environment ###

int MaxEntities = 1000;
std::vector<Cell *> CellList;
int PlayWidth = 100000;
int PlayHeight = 100000;

double EnvironmentViewportX = 0;// -PlayWidth / 2;
double EnvironmentViewportY = 0;// -PlayHeight / 2;
double EnvironmentViewportScale = 1.0;

double NetworkViewportX = 0;// -PlayWidth / 2;
double NetworkViewportY = 0;// -PlayHeight / 2;
double NetworkViewportScale = 1.0;

//### Cell ###

double MinCellSize = 5.0;
double MaxCellSize = 50.0;
double MaxCellSpeed = 3.0;
int MaxInitialCellEyes = 1;
int InitialCellEnergy = 100;
int MaxCellHealth = 100;
int NetworkWidth = 600;
int NetworkHeight = 300;

//### Functions ###

inline int Rand(int min, int max)
{
	//return min + rand() % ((max+1) -min);
	return min + Random() % ((max+1) -min);
}

inline double DRand(double min, double max)
{
	//return min + ((double)rand() / RAND_MAX) * ((max + 1.0) - min);
	//unsigned int Max: 4294967295;
	//factor of num: 1114129;
	return min + ((double)(Random() % 1114129) / (1114129.0 + 1)) * ((max + 1.0) - min);
}

inline double QuadraticRandom(double min, double max, int power, int cycle = 1000)
{
	//return min + (pow(fmod(rand(), cycle), power) / pow(cycle, power - 1)) / cycle * (max - min);
	return min + (pow(fmod(Random(), cycle), power) / pow(cycle, power - 1)) / cycle * (max - min);
}

inline double ApplyTransform(double x, double offset, double scale, double screenCenter)
{
	return (x - offset) * scale + screenCenter;
}

inline double ReverseTransform(double x, double offset, double scale, double screenCenter)
{
	return (x - screenCenter) / scale + offset;
}

inline double Dist(double x1, double y1, double x2, double y2)
{
	return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

