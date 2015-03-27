#pragma once

#include <iostream>
#include <exception>
#include <SDL.h>

#include "math\Vec2.h"

class System
{
private:
	Vec2i screenSize;
	bool running;

	SDL_Window* window;
	SDL_Surface* screenSurface;
	SDL_Event event;
public:
	System(Vec2i screenSize);
	~System();

	void Run();
};

