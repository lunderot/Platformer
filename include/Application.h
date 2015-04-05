#pragma once

#include <SDL.h>

#include "System.h"
#include "AssetHandler.h"
#include "Player.h"
#include "EntityHandler.h"
#include "ScriptHandler.h"

class Application: public System
{
private:
	AssetHandler* assetHandler;
	EntityHandler* entityHandler;
	ScriptHandler* scriptHandler;
public:
	Application(Vec2i screenSize, std::string title);
	virtual ~Application();

	void HandleEvent(SDL_Event& event);
	void Update(float deltaTime);
	void Render();
};

