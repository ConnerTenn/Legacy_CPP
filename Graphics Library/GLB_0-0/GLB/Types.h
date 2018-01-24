
#pragma once
#include <string>
#include <vector>

struct Rect
{
	int X;
	int Y;
	int Width;
	int Height;
};


struct WindowProperties
{
	std::string Title = "Window";
	Rect WindowRect = {SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 900, 600};
	SDL_WindowFlags Flags = SDL_WINDOW_SHOWN;

	WindowProperties() {}
	WindowProperties(std::string title, Rect windowRect, SDL_WindowFlags flags) :
		Title(title), WindowRect(windowRect), Flags(flags) {}
};

struct InternalState
{
	bool Quit = false;
};

