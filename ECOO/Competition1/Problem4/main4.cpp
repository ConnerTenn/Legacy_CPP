
#include <string>
#include <iostream>
#include <fstream>

void sort()
{

}

void renumber()
{

}

void swaps()
{

}

void main()
{
	std::ifstream file;
	file.open("DATA01.txt");
	for (int i = 0; i < 10; i++)
	{
		std::string nums;
		int num;
		std::getline(file, nums);
		num = stoi(nums);

		std::string *names = new std::string[num];
		for (int j = 0; j < num; j++)
		{
			std::getline(file, names[j]);
		}


	}
}