
#include "stdafx.h"
#include"Levels.h"

void Levels::Loop()
{
	a = 1;
	Enemy enemy;
	enemy.func();
	cout << "B:" << enemy.b << "\n";
}