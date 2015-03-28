#pragma once

#include <SDL.h>

#include "System.h"
#include "AssetHandler.h"

class Application: public System
{
private:
	AssetHandler* assetHandler;
public:
	Application(Vec2i screenSize, std::string title);
	virtual ~Application();

	void HandleEvent(SDL_Event& event);
	void Update(float deltaTime);
	void Render();
};

