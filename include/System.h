#pragma once

#include <iostream>
#include <exception>
#include <algorithm>

#include <SDL.h>
#include <SDL_image.h>

#include <glm/glm.hpp>

class System
{
private:
	glm::ivec2 screenSize;
	bool running;

	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event event;
	
public:
	System(glm::ivec2 screenSize, std::string title);
	virtual ~System();

	void Run();
	glm::ivec2 GetScreenSize() const;
	SDL_Renderer* GetRenderer() const;
	SDL_Window* GetWindow() const;

	virtual void HandleEvent(SDL_Event& event) = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Render() = 0;
};

