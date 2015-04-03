#pragma once
#include <iostream>
#include <string>


#include "EntityHandler.h"
#include "AssetHandler.h"
#include "Player.h"

#include "lua/lua.hpp"

namespace ScriptHandler
{
	namespace Internal
	{
		extern lua_State* ls;
		extern std::string scriptPath;

		extern AssetHandler* assetHandler;
		extern EntityHandler* entityHandler;

		//Lua functions
		static int GetKeyCodeFromName(lua_State* ls); //keycode = GetKeyCodeFromName(keyName)
		static int GetKeyNameFromCode(lua_State* ls); //keyName = GetKeyNameFromCode(keycode)
	}

	//C++ functions
	void AddFile(std::string filename);

	void TriggerEvent(std::string id, int eventData);
	void TriggerEvent(SDL_MouseButtonEvent event);
	void TriggerEvent(SDL_MouseMotionEvent event);
	void TriggerEvent(SDL_KeyboardEvent event);

	void Init(std::string scriptPath, EntityHandler* entityHandler, AssetHandler* assetHandler);
	void Close();
};