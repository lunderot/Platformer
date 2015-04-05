#pragma once
#include "EntityHandler.h"
#include "AssetHandler.h"

#include "lua/lua.hpp"

namespace ScriptHandlerInternal
{
	extern lua_State* ls;
	extern std::string scriptPath;

	extern AssetHandler* assetHandler;
	extern EntityHandler* entityHandler;

	static void SetState(lua_State* ls, std::string scriptPath, EntityHandler* entityHandler, AssetHandler* assetHandler)
	{
		ScriptHandlerInternal::ls = ls;
		ScriptHandlerInternal::scriptPath = scriptPath;
		ScriptHandlerInternal::entityHandler = entityHandler;
		ScriptHandlerInternal::assetHandler = assetHandler;
	}

	//Lua functions
	static int GetKeyCodeFromName(lua_State* ls) //keycode = GetKeyCodeFromName(keyName)
	{
		std::string keyName(luaL_checkstring(ls, 1));
		SDL_Keycode key = SDL_GetKeyFromName(keyName.c_str());
		lua_pushnumber(ls, static_cast<int>(key));
		return 1;
	}
	static int GetKeyNameFromCode(lua_State* ls) //keyName = GetKeyNameFromCode(keycode)
	{
		int keyCode = luaL_checknumber(ls, 1);
		const char* name = SDL_GetKeyName(keyCode);
		lua_pushstring(ls, name);
		return 1;
	}
}