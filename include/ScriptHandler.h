#pragma once
#include <iostream>
#include <string>

#include "ScriptHandlerInternal.h"

#include "EntityHandler.h"
#include "AssetHandler.h"
#include "Player.h"

#include "lua/lua.hpp"

class ScriptHandler
{
private:
	lua_State* ls;
	EntityHandler* entityHandler;
	AssetHandler* assetHandler;
public:
	ScriptHandler(EntityHandler* entityHandler, AssetHandler* assetHandler);
	~ScriptHandler();

	void AddFile(std::string filename);
	void AddFunction(lua_CFunction function, std::string functionName);

	void TriggerEvent(std::string id);
	void ScriptHandler::TriggerEvent(std::string id, float deltaTime);
	void TriggerEvent(SDL_MouseButtonEvent event);
	void TriggerEvent(SDL_MouseMotionEvent event);
	void TriggerEvent(SDL_KeyboardEvent event);

	friend void ScriptHandlerInternal::SetState(lua_State* ls, EntityHandler* entityHandler, AssetHandler* assetHandler);
};


