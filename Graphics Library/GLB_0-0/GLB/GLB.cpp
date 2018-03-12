
#include "GLB.h"

//### Section ###

Container::Container()
{

}

Container::~Container()
{

}

void Container::Add(Container *child)
{

}

void Container::RecursiveRemove()
{

}

std::vector<Container *> Container::Remove()
{
	return{};
}

//### Section ###

Window::Window()
{
	Init();
}

Window::Window(WindowProperties windowProperties)
{
	Properties = windowProperties;
	Init();
}

Window::~Window()
{
	Shutdown();
}

void Window::Init()
{
	SDL_Init(SDL_INIT_EVERYTHING);
}

void Window::Shutdown()
{
	SDL_DestroyRenderer(Renderer); Renderer = 0;
	SDL_DestroyWindow(WindowHWND); WindowHWND = 0;
	SDL_Quit();
}

void Window::Create()
{
	WindowHWND = SDL_CreateWindow(
		Properties.Title.c_str(),
		Properties.WindowRect.X, Properties.WindowRect.Y,
		Properties.WindowRect.Width, Properties.WindowRect.Height,
		Properties.Flags);

	WindowID = SDL_GetWindowID(WindowHWND);

	//Renderer = SDL_CreateRenderer(WindowHWND, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
	Renderer = SDL_CreateRenderer(0, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
}

void Window::WaitEvent()
{
	SDL_Event event;
	SDL_WaitEvent(&event);
	if (event.window.windowID == WindowID)
	{
		if (event.window.event == SDL_WINDOWEVENT_CLOSE) { State.Quit = true; }
	}
}

bool Window::PollEvent()
{
	SDL_Event event;
	bool result = !!SDL_PollEvent(&event);
	if (result && event.window.windowID == WindowID)
	{
		if (event.window.event == SDL_WINDOWEVENT_CLOSE) { State.Quit = true; }
		return true;
	}
	else
	{
		return false;
	}
}
