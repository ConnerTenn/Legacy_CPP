// Arrarys.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

template <class t>
class List
{
private:
	t Value = 0;
	List* Next = 0;
	int Index = 0;

	List(t val, int index)
	{
		Value = val;
		Index = index;
	}
public:
	List(t val)
	{
		Value = val;
	}
	void append(t Val)
	{
		if (Next != 0)
		{
			Next->append(Val);
		}
		else
		{
			Next = new List(Val, Index + 1);
		}
	}
	t operator[](int index)
	{
		if (index == Index)
		{
			return Value;
		}
		else
		{
			if (Next != 0)
			{
				//auto a = (*Next)[index];
				//return (*Next)[0] + sizeof(List) * index;
				return (*Next)[index];
			}
			else
			{
				_DEBUG_ERROR("Error::Out of Range");
			}
		}
	}
};

template <class t>
class List2
{
private:
	t* PointArray = new t[0];
	int Size = 0;

public:
	List2(t val)
	{
		append(val);
	}
	void append_(t val)
	{
		Size += 1;
		t* PointArrayNew = new t[Size];

		t* PointArrayI = PointArray;
		t* PointArrayNewI = PointArrayNew;
		for (int i = 0; i < Size - 1; i++)
		{
			PointArrayNewI = PointArrayI;
			PointArrayI += sizeof(t*);
			PointArrayNewI += sizeof(t*);
		}

		t* Val = new t;
		*Val = val;
		PointArrayNewI = Val;
		PointArray = PointArrayNew;
	}
	void append(t val)
	{
		Size += 1;
		t* PointArrayNew = new t[Size];
		t* PointArrayI = PointArray;
		t* PointArrayNewI = PointArrayNew;
		for (int i = 1; i < Size; i++)
		{
			*PointArrayNewI = *PointArrayI;
			PointArrayNewI += sizeof(t*);
			PointArrayI += sizeof(t*);
		}
		t* Val = new t;
		*Val = val;
		*PointArrayNewI = *Val;
		PointArray = PointArrayNew;
	}
	t operator[](int index)
	{
		return *(PointArray + sizeof(t*) * index);
	}
};

template <class t>
class List3
{
private:
	t* PointArray = new t[0];
	int Size = 0;

public:
	List3(t val)
	{
		append(val);
	}
	~List3()
	{
		PointArray = 0;
		delete PointArray;
	}
	void append(t val)
	{
		Size += 1;
		t* PointArrayNew = new t[Size];

		t* PointArrayI = PointArray;
		t* PointArrayNewI = PointArrayNew;
		for (int i = 0; i < Size - 1; i++)
		{
			*PointArrayNewI = *PointArrayI;
			PointArrayI += sizeof(t*);
			PointArrayNewI += sizeof(t*);
		}

		//t* Val = new t;
		//*Val = val;
		*PointArrayNewI = val;

		delete[] PointArray;
		PointArray = PointArrayNew;

		PointArrayI = 0;
		delete PointArrayI;
		PointArrayNewI = 0;
		delete PointArrayNewI;
	}
	t operator[](int index)
	{
		return *(PointArray + sizeof(t) * index);
	}
};


void main()
{
	//c99
	//int Size = 2;
	//int Array[Size];
	//int *Array[] = new int[Size]
	//Array[2] = 1;
	//cout << Array[2] << "\n";

	{/*Test dynamic memory*/}
	{	
		/*
		int Size = 2;
		int * var = new int[Size];
		*var = 1;
		int* var2 = var + sizeof(int);
		*var2 = 2;
		//*(var + sizeof(int)) = 5;
		cout << *var << " at " << var << "\n";
		*/
	}

	{/*Test List*/} 
	{
		/*
		List<int> Val(2);
		cout << Val[0] << "\n";
		Val.append(3);
		cout << Val[1] << "\n";
		Val.append(9);
		cout << Val[2] << "\n";
		Val.append(1);
		cout << Val[3] << "\n";
		cout << "\n" << Val[0] << " " << Val[1] << " " << Val[2] << " " << Val[3] << "\n";
		*/
	}

	{/*Test List2*/}
	{
		/*
		List2<int> Val(2);
		cout << Val[0] << "\n";
		Val.append(3);
		cout << Val[1] << "\n";
		Val.append(9);
		cout << Val[2] << "\n";
		Val.append(1);
		cout << Val[3] << "\n";
		cout << "\n" << Val[0] << " " << Val[1] << " " << Val[2] << " " << Val[3] << "\n";
		*/
	}
	
	{/*Test List3*/}
	{
		///*
		List3<int> Val(2);
		cout << Val[0] << "\n";
		Val.append(3);
		cout << Val[1] << "\n";
		Val.append(9);
		cout << Val[2] << "\n";
		Val.append(1);
		cout << Val[3] << "\n";
		cout << "\n" << Val[0] << " " << Val[1] << " " << Val[2] << " " << Val[3] << "\n";
		//*/
	}

	//array<int,Size> Array2;

	string End;
	getline(cin, End);
}

