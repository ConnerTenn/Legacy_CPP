
#include <string>
#include <iostream>
#include <fstream>

void main()
{
	std::ifstream file;
	file.open("DATA01.txt");
	std::string str1, str2;
	for (int i = 0; i < 5; i++)
	{
		file >> str1 >> str2;
		int counter = 0;
		for (int j = 0; j < (int)str1.size(); j++)
		{
			if (str1[j] == str2[j])
			{
				counter += 5;
			}
		}
		std::cout << counter << "\n";
	}
	int a;
	std::cin >> a;
}