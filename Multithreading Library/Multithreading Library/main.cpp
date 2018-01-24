
#include <iostream>
#include <string>
#include "Threading.h"
#include <Windows.h>
#include <mutex>
#include <condition_variable>

void Test1Thread(Thread *thread)
{
	while (thread->Run)
	{
		thread->Update();

		std::cout << "Hello\n";
		Sleep(50);
	}
}

void Test2Thread(Thread *thread)
{
	while (thread->Run)
	{
		thread->Update();

		std::cout << "Args: " << *((int *)thread->Args) << "\n";
		Sleep(50);
	}
}

std::mutex Mutex;

void Test3Thread(Thread *thread)
{
	int *threadNum = (int *)(thread->Args);
	for (int i = 0; i < 10; i++)
	{
		Mutex.lock();
		std::cout << "Worker " << *threadNum << "  Val:" << i << "\n";
		Mutex.unlock();
	}
	delete threadNum;
}

std::condition_variable conditionVariable;
bool Ready = false;

void Test4Thread1(Thread *thread)
{
	std::cout << "Thread 1: Unlocking Thread 2 in:\n3\n"; 
	Sleep(1000); std::cout << "2\n"; Sleep(1000); std::cout << "1\n";
	{
		//std::lock_guard<std::mutex> lock(Mutex);
		Ready = true;
		std::cout << "Thread 1: Unlocked Thread 2\n";
	}
	conditionVariable.notify_all();
}

void Test4Thread2(Thread *thread)
{
	{
		std::unique_lock<std::mutex> Lock(Mutex);
		conditionVariable.wait(Lock, [] { return Ready; });
	}
	std::cout << "Thread 2: Released\n";
}

void main()
{
	std::cout << "Enter Test Number:";
	int testNum = 0;
	std::string in;
	{ std::getline(std::cin, in); try { testNum = std::stoi(in); } catch (...) {}}

	if (testNum == 1)
	{
		Thread *thread = new Thread(Test1Thread);

		std::cout << "Control::Begin Test 1\n";
		thread->Begin();
		Sleep(500);

		std::cout << "Control::Paused\n";
		thread->Pause();
		Sleep(500);

		std::cout << "Control::Continue\n";
		thread->Continue();
		Sleep(500);

		std::cout << "Control::Done Test 1\n";
		thread->Join();

		delete thread; thread = 0;
	}
	else if (testNum == 2)
	{
		int val = 10;
		Thread *thread = new Thread(Test2Thread, (void *)&val);

		std::cout << "Control::Begin Test 2\n";
		thread->Begin();
		Sleep(500);

		std::cout << "Control::Paused\n";
		thread->Pause();
		Sleep(500);

		std::cout << "Control::Continue\n";
		thread->Continue();
		Sleep(500);

		std::cout << "Control::Done Test 2\n";
		thread->Join();

		delete thread; thread = 0;
	}
	else if (testNum == 3)
	{
		Thread **thread = new Thread *[10];
		for (int i = 0; i < 10; i++) { thread[i] = new Thread(Test3Thread, (void *)(new int(i))); }

		std::cout << "Control::Begin Test 3\n";
		for (int i = 0; i < 10; i++) { thread[i]->Begin(); }

		for (int i = 0; i < 10; i++) { thread[i]->Join(); }
		std::cout << "Control::Done Test 3!n";

		for (int i = 0; i < 10; i++) { delete thread[i]; thread[i] = 0; }
	}
	else if (testNum == 4)
	{
		std::cout << "Control::Begin Test 4\n";
		Thread *thread1 = new Thread(Test4Thread1);
		Thread *thread2 = new Thread(Test4Thread2);
		thread1->Begin();
		thread2->Begin();

		thread1->Join();
		thread2->Join();
		delete thread1;
		delete thread2;
		std::cout << "Control::Done Test 4\n";
	}
	else
	{
		std::cout << "Invalid Test Number\n";
	}


	std::cout << "\nPress Any Key to Continue";

	std::string Out;
	std::getline(std::cin, Out);
}
