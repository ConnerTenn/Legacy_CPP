
#include <iostream>
#include <vector>
#include <string>

std::vector<int> List = { 2, 4, 6, 8, 10, 12 };
double Significance;

void main()
{
	Significance = ((double)List.size() * 0.9);

	std::cout << "Significance:" << Significance << "\n";

	std::cout << "\nPress Any Key To Continue"; std::string out; std::getline(std::cin, out);
}
