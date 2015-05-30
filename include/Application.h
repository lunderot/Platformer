#pragma once

#include <SDL.h>

#include "System.h"

#include "AssetHandler.h"
#include "EntityHandler.h"
#include "ScriptHandler.h"
#include "MapHandler.h"

#include "Player.h"
#include "Tile.h"

class Application: public System
{
private:
	AssetHandler* assetHandler;
	EntityHandler* entityHandler;
	ScriptHandler* scriptHandler;
	MapHandler* mapHandler;
public:
	Application(Vec2i screenSize, std::string title, int argc, char* argv[]);
	virtual ~Application();

	void HandleEvent(SDL_Event& event);
	void Update(float deltaTime);
	void Render();
};

