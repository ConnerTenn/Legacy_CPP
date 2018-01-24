

#include "stdafx.h"
#include<iostream>
#include<vector>

using namespace std;

class Numbers //Class Numbers
{
public:
	int Num; //Variable

	Numbers(int num = -1) //Constructor
	{
		Num = num;
	}
};

int main()
{
	vector<Numbers> List; //List containing all objects

	Numbers Num1(3); //Create a Number object
	List.push_back(Num1); //Add the object to the list
	Num1 = 0; //Delete the object

	Numbers Num2(5); //Create a Number object
	List.push_back(Num2); //Add the object to the list
	Num2 = 0; //Delete the object

	Numbers Num3(9); //Create a Number object
	List.push_back(Num3); //Add the object to the list
	Num3 = 0; //Delete the object

	Numbers Num4(2); //Create a Number object
	List.push_back(Num4); //Add the object to the list
	Num4 = 0; //Delete the object
	
	int i = 1; //Value to be stored
	for (Numbers &num : List)// Loop through each object
	{
		num.Num = i; //Set i to the value of each object
		i++; //Increce i
	}

	for (Numbers num : List)//Print the values of each object (Should be: 1,2,3,4     Instead prints: 3,5,9,2)
	{
		cout << num.Num << endl; //Print Num
	}

	char delay; //Var
	cin >> delay; //Keep the program from closing
	return 0;
}

