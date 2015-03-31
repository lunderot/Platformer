#include "System.h"

System::System(Vec2i screenSize, std::string title)
{
	this->screenSize = screenSize;
	this->running = true;

	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenSize.x, screenSize.y, SDL_WINDOW_SHOWN);
	if (!window)
	{
		throw std::runtime_error("Failed to create SDL window");
	}
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer)
	{
		throw std::runtime_error("Failed to create SDL renderer");
	}

	int imgFlags = IMG_INIT_PNG;
	if (!IMG_Init(imgFlags) & imgFlags)
	{
		throw std::exception("Failed to init SDL_image");
	}
}

System::~System()
{
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();
}

void System::Run()
{
	float dt = 1 / 60.0f;
	float currentTime = SDL_GetTicks() / 1000.0f;

	while (running)
	{
		//Handle SDL events
		while (SDL_PollEvent(&event) != 0)
		{
			HandleEvent(event);
			switch (event.type)
			{
			case SDL_QUIT:
				running = false;
				break;
			default:
				break;
			}
		}
		//Update
		float newTime = SDL_GetTicks() / 1000.0f;
		float frameTime = newTime - currentTime;
		currentTime = newTime;
		
		while (frameTime > 0.0f)
		{
			float deltaTime = std::min(frameTime, dt);
			Update(deltaTime);
			frameTime -= deltaTime;
		}
		
		//Render
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(renderer);
		Render();
		SDL_RenderPresent(renderer);
	}
}

Vec2i System::GetScreenSize() const
{
	return screenSize;
}

SDL_Renderer* System::GetRenderer() const
{
	return renderer;
}

SDL_Window* System::GetWindow() const
{
	return window;
}