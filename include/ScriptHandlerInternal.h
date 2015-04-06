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

	//Keyboard functions
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

	//Entity functions
	static int GetEntityPosition(lua_State* ls) //x,y = GetEntityPosition(id)
	{
		int id = luaL_checknumber(ls, 1);
		Vec2f pos = entityHandler->GetEntity(id)->GetPosition();
		lua_pushnumber(ls, pos.x);
		lua_pushnumber(ls, pos.y);
		return 2;
	}
	static int GetEntityVelocity(lua_State* ls) //xvel,yvel = GetEntityVelocity(id)
	{
		int id = luaL_checknumber(ls, 1);
		Vec2f vel = entityHandler->GetEntity(id)->GetVelocity();
		lua_pushnumber(ls, vel.x);
		lua_pushnumber(ls, vel.y);
		return 2;
	}
	static int GetEntityAcceleration(lua_State* ls) //x,y = GetEntityAcceleration(id)
	{
		int id = luaL_checknumber(ls, 1);
		Vec2f acc = entityHandler->GetEntity(id)->GetAcceleration();
		lua_pushnumber(ls, acc.x);
		lua_pushnumber(ls, acc.y);
		return 2;
	}

	static int SetEntityPosition(lua_State* ls) //SetEntityPosition(id, x, y)
	{
		int id = luaL_checknumber(ls, 1);
		float x = luaL_checknumber(ls, 2);
		float y = luaL_checknumber(ls, 3);
		entityHandler->GetEntity(id)->SetPosition(Vec2f(x, y));
		return 0;
	}
	static int SetEntityVelocity(lua_State* ls) //SetEntityVelocity(id, xvel, yvel)
	{
		int id = luaL_checknumber(ls, 1);
		float xvel = luaL_checknumber(ls, 2);
		float yvel = luaL_checknumber(ls, 3);
		entityHandler->GetEntity(id)->SetVelocity(Vec2f(xvel, yvel));
		return 0;
	}
	static int SetEntityAcceleration(lua_State* ls) //SetEntityAcceleration(id, xacc, yacc)
	{
		int id = luaL_checknumber(ls, 1);
		float xacc = luaL_checknumber(ls, 2);
		float yacc = luaL_checknumber(ls, 3);
		entityHandler->GetEntity(id)->SetAcceleration(Vec2f(xacc, yacc));
		return 0;
	}

	static int GetEntityRadius(lua_State* ls) //r = GetEntityRadius(id)
	{
		int id = luaL_checknumber(ls, 1);
		float r = entityHandler->GetEntity(id)->GetRadius();
		lua_pushnumber(ls, r);
		return 1;
	}
}