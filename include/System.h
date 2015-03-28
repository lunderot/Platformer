#pragma once

#include <iostream>
#include <exception>

#include <SDL.h>

#include "math\Vec2.h"
#include "AssetHandler.h"

class System
{
private:
	Vec2i screenSize;
	bool running;

	AssetHandler* assetHandler;

	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event event;

	
public:
	System(Vec2i screenSize);
	~System();

	void Run();
};

