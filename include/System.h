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
	SDL_Renderer* renderer;
	SDL_Event event;
	
public:
	System(Vec2i screenSize, std::string title);
	virtual ~System();

	void Run();
	Vec2i GetScreenSize() const;
	SDL_Renderer* GetRenderer() const;
	SDL_Window* GetWindow() const;

	virtual void HandleEvent(SDL_Event& event) = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Render() = 0;
};

