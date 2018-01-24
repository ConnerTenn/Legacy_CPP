
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <stdio.h>
#include <string.h>

class PopulateSquares
{
private:
	std::string input;
	std::string item;
	int width;
	int height;

public:
	std::vector<std::string>dimentions;		             // Vector to allocate dimentions. Only 0 and 1. used for height 
	void GetDimentions();					     // and width
	int GetArea() { return int(width) * (height); }
	int GetWidth() { return int(width); }
	int GetHeight() { return int(height); }
};

void PopulateSquares::GetDimentions()
{

	std::cout << "Enter the dimentions [WxH]: ";
	//std::cin >> input;
	//getline is usually better because it cleares the input buffer (less issues for input later on)
	std::getline(std::cin, input);

	std::stringstream inp(input);				    // Sets up a string buffer

	while (std::getline(inp, item, 'x'))
	{		    // Break the input using the delimiter char 'x' 
		dimentions.push_back(item);				    // Saves the broken string as strings in a vector array
	}
	width = std::stoi(dimentions[0]);			    // From the array
	height = std::stoi(dimentions[1]);			    // Sets the height and the width by calling the first and second
}

class Gameboard
{
private:
	int Width;
	int Height;
	char **gameboard; //pointer to pointer to char
public:
	Gameboard(int width, int height) : Width(width), Height(height)
	{ 
		//gameboard = new char[Width][Height]; 

		//dynamic memory allocation for a 2 dimensional array
		gameboard = new char *[Width];
		for (int i = 0; i < Width; ++i)
		{
			gameboard[i] = new char[Height];
		}
	}
	//destructor; runs when object is destroyed
	~Gameboard()
	{
		//free memory
		for (int i = 0; i < Width; i++)
		{
			delete[] gameboard[i];
		}
	}

	char **GetGameboard() { return gameboard; }

};

/*template<int numberOfRows, int numberOfColumns>
void PrintGameboard(int(&theArray)[numberOfRows][numberOfColumns])
{
	for (int x = 0; x < numberOfRows; x++)
	{
		for (int y = 0; y < numberOfColumns; y++)
		{
			std::cout << theArray[x][y] << " ";
		}
		std::cout << std::endl;
	}
}*/

void PrintGameboard(char **gameboard, int width, int height)
{
	//loop line by line
	for (int y = 0; y < height; y++)
	{
		//print all items in the line
		for (int x = 0; x < width; x++)
		{
			std::cout << gameboard[x][y] << " ";
		}
		std::cout << std::endl;
	}
}

void main()
{
	int width;
	int height;
	//char **gameboard;

	PopulateSquares squares;
	squares.GetDimentions();

	width = squares.GetWidth();
	height = squares.GetHeight();				    // Set the values for the height and width of the array

	std::cout << "Width: " << width << " Height: " << height << std::endl; // Debugging

	Gameboard Tiles(width, height);
	//gameboard = Tiles.GetGameboard();
	PrintGameboard(Tiles.GetGameboard(), width, height);

	std::string Out;
	std::getline(std::cin, Out);

	//destructor runs when gameboard object goes out of scope here
}
