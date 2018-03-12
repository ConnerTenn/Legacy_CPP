
#pragma once

#include "SDL.h"
#include "Types.h"

//### Section ###

class Container
{
private:
	Container *Parent;
	std::vector<Container *> ChildListList;

public:
	Container();
	~Container();

private:

public:
	void Add(Container *child);
	void RecursiveRemove();
	std::vector<Container *> Remove();
};

//### Section ###

class Window
{
private:
	WindowProperties Properties;
	SDL_Window *WindowHWND = 0;
	Uint32 WindowID = 0;
	SDL_Renderer *Renderer = 0;

public:
	InternalState State;

public:
	Window();
	Window(WindowProperties windowProperties);
	~Window();

private:

	void Init();
	void Shutdown();

public:

	void Create();
	void WaitEvent();
	bool PollEvent();
};