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
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer)
	{
		throw std::runtime_error("Failed to create SDL renderer");
	}
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

	assetHandler = new AssetHandler(renderer);
}


System::~System()
{
	delete assetHandler;

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
		SDL_RenderClear(renderer);

		SDL_Rect dest = { 0, 0, 0, 0 };
		SDL_QueryTexture(assetHandler->GetTexture("assets/textures/test.bmp"), nullptr, nullptr, &dest.w, &dest.h);

		SDL_RenderCopy(renderer, assetHandler->GetTexture("assets/textures/test.bmp"), nullptr, &dest);

		SDL_RenderPresent(renderer);
	}
}