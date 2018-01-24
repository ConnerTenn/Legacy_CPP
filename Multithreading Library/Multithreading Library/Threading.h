
class Thread;

#pragma once

#include <thread>

class Thread
{
private:
	void (*Function)(Thread *thread);
	bool Paused = false;
	bool PauseConfirm = false;
	std::thread UpdateThread;

public:
	bool Run = false;
	void *Args;

public:
	Thread(void (*function)(Thread *thread))
	{
		Function = function;
	}

	Thread(void(*function)(Thread *thread), void *args)
	{
		Function = function;
		Args = args;
	}

	~Thread()
	{

	}

	void Begin()
	{
		Run = true;
		UpdateThread = std::thread(Function, this);
	}

	void Join()
	{
		Run = false;
		UpdateThread.join();
	}

	void Pause()
	{
		Paused = true;
	}

	void Continue()
	{
		Paused = false;
	}

	void Update()
	{
		if (Paused)
		{
			PauseConfirm = true;
			while (Paused && Run) {}
			PauseConfirm = false;
		}
	}
};


