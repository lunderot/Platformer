#pragma once

#include <SDL.h>

#include "System.h"
#include "AssetHandler.h"
#include "Player.h"

class Application: public System
{
private:
	AssetHandler* assetHandler;
	Entity* player;
public:
	Application(Vec2i screenSize, std::string title);
	virtual ~Application();

	void HandleEvent(SDL_Event& event);
	void Update(float deltaTime);
	void Render();
};

