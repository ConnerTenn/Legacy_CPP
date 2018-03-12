#include "stdafx.h"
#include <amp.h>                // C++ AMP header file
#include <iostream>             // For std::cout etc
#include <time.h>
#include <string>
using namespace Concurrency;


int Size = 120000000;
int Version = 1;
double Time1;
double Time2;

void AmpMethod()
{
	//std::vector<int> A(Size);
	//std::vector<int> B(Size);
	//std::vector<int> Sum(Size);
	//for (int i = 0; i < Size; i++) { A[i] = i; B[i] = i; }

	//int *A = (int *)malloc(sizeof(int) * Size);
	//memset(A, 2, sizeof(int) * Size);
	int A = 0;

	Time1 = clock();
	if (Version == 0)
	{
		std::cout << "Using: CPU\n";

		for (int i = 0; i < Size; i++)
		{
			for (int j = 0; j < 50; j++)
			{
				A += i;
				A *= A;
			}
		}
	}
	else if (Version == 1)
	{
		accelerator accel;
		std::wstring desc = accel.get_description();
		int size = (int)accel.get_dedicated_memory();
		std::cout << "Using: " << std::string(desc.begin(), desc.end()) << "  Memory:" << size << "KB" << "\n";

		// Create C++ AMP objects.
		extent<1> e(Size);
		array_view<int, 1> a(1, &A);


		parallel_for_each(
			// Define the compute domain, which is the set of threads that are created.
			e,
			// Define the code to run on each thread on the accelerator.
			[=](index<1> idx) restrict(amp)
			{
				for (int i = 0; i < 50; i++)
				{
					a[0] += idx[0];
					a[0] *= a[0];
				}
			}
		);
		a.synchronize();
	}
	Time2 = clock();

	// Print the results. The expected output is "7, 9, 11, 13, 15".
	std::cout << "Value: " << A << "\n";
}


void main()
{
	std::cout << "\nBeginning Calculation\n";
	AmpMethod();
	std::cout << "\nDone!\nTime:" << Time2 - Time1 << " ms\n\nPress Enter To Continue" << std::endl;
	std::cin.get();
}

/*
extent<2> e(3, 2);
parallel_for_each(e,
	[=](index<2> idx)
	{
		// Code that executes on the accelerator.
		// It gets invoked in parallel by multiple threads
		// once for each index "contained" in extent e
		// and the index is passed in via idx.
		// The following always hold true
		//      e.rank == idx.rank
		//      e.contains(idx) == true
		//      the function gets called e.size() times
		// For this two-dimensional case (.rank == 2)
		//      e.size() == 3*2 = 6 threads calling this lambda
		// The 6 values of idx passed to the lambda are:
		//      { 0,0 } { 0,1 } { 1,0 } { 1,1 } { 2,0 } { 2,1 }
	}
);
// Code that executes on the host CPU (like line 91 and earlier)
*/