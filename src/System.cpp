#include "System.h"

System::System(Vec2i screenSize)
{
	this->screenSize = screenSize;
	running = true;

	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow("Platformer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenSize.x, screenSize.y, SDL_WINDOW_SHOWN);
	if (!window)
	{
		throw std::runtime_error("Failed to create SDL window");
	}
	screenSurface = SDL_GetWindowSurface(window);
}


System::~System()
{
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void System::Run()
{
	while (running)
	{
		//Handle SDL events
		while (SDL_PollEvent(&event) != 0)
		{
			switch (event.type)
			{
			case SDL_QUIT:
				running = false;
				break;
			default:
				break;
			}
		}
		//Render
		SDL_FillRect(screenSurface, nullptr, SDL_MapRGB(screenSurface->format, 255, 0, 0));
		SDL_UpdateWindowSurface(window);
	}
}