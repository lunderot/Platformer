#pragma once
#include <iostream>
#include <string>

#include "EntityHandler.h"

#include "lua/lua.hpp"

namespace ScriptHandler
{
	namespace Internal
	{
		extern lua_State* ls;

		extern std::string scriptPath;
		extern EntityHandler* entityHandler;

		//Lua functions
		
	}

	//C++ functions
	void AddFile(std::string filename);

	void TriggerEvent(std::string id, int eventData);
	void TriggerEvent(SDL_MouseButtonEvent event);
	void TriggerEvent(SDL_MouseMotionEvent event);

	void Init(std::string scriptPath, EntityHandler* entityHandler);
	void Close();
};