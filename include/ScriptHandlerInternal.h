#pragma once
#include "EntityHandler.h"
#include "AssetHandler.h"

#include "lua/lua.hpp"

namespace ScriptHandlerInternal
{
	extern lua_State* ls;

	extern AssetHandler* assetHandler;
	extern EntityHandler* entityHandler;

	static void SetState(lua_State* ls, EntityHandler* entityHandler, AssetHandler* assetHandler)
	{
		ScriptHandlerInternal::ls = ls;
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
		int keyCode = static_cast<int>(luaL_checknumber(ls, 1));
		const char* name = SDL_GetKeyName(keyCode);
		lua_pushstring(ls, name);
		return 1;
	}

	//Entity handler functions
	static int GetCameraId(lua_State* ls) //id = GetCameraId()
	{
		lua_pushnumber(ls, entityHandler->GetCameraId());
		return 1;
	}
	static int GetCameraSize(lua_State* ls) //w,h = GetCameraSize()
	{
		Camera* camera = dynamic_cast<Camera*>(entityHandler->GetEntity(entityHandler->GetCameraId()));
		Vec2f size = camera->GetSize();
		lua_pushnumber(ls, size.x);
		lua_pushnumber(ls, size.y);
		return 2;
	}
	static int GetWorldPositionFromScreenPosition(lua_State* ls) //x,y = GetWorldPositionFromScreenPosition(x, y)
	{
		float x = static_cast<float>(luaL_checknumber(ls, 1));
		float y = static_cast<float>(luaL_checknumber(ls, 2));
		Camera* camera = dynamic_cast<Camera*>(entityHandler->GetEntity(entityHandler->GetCameraId()));
		Vec2f camSize = camera->GetSize();
		Vec2f camPosition = camera->GetPosition();
		lua_pushnumber(ls, x + camPosition.x - camSize.x / 2);
		lua_pushnumber(ls, y + camPosition.y - camSize.y / 2);
		return 2;
	}

	static int AddEntity(lua_State* ls) //id = AddEntity(type, textureFilename, radius)
	{
		int type = static_cast<int>(luaL_checknumber(ls, 1));
		std::string textureFilename(luaL_checkstring(ls, 2));
		float radius = static_cast<float>(luaL_checknumber(ls, 3));
		int id = entityHandler->Add(static_cast<EntityType>(type), textureFilename, radius, assetHandler);
		lua_pushnumber(ls, id);
		return 1;
	}

	//Entity functions
	static int GetEntityPosition(lua_State* ls) //x,y = GetEntityPosition(id)
	{
		int id = static_cast<int>(luaL_checknumber(ls, 1));
		Vec2f pos = entityHandler->GetEntity(id)->GetPosition();
		lua_pushnumber(ls, pos.x);
		lua_pushnumber(ls, pos.y);
		return 2;
	}
	static int GetEntityVelocity(lua_State* ls) //xvel,yvel = GetEntityVelocity(id)
	{
		int id = static_cast<int>(luaL_checknumber(ls, 1));
		Vec2f vel = entityHandler->GetEntity(id)->GetVelocity();
		lua_pushnumber(ls, vel.x);
		lua_pushnumber(ls, vel.y);
		return 2;
	}
	static int GetEntityAcceleration(lua_State* ls) //x,y = GetEntityAcceleration(id)
	{
		int id = static_cast<int>(luaL_checknumber(ls, 1));
		Vec2f acc = entityHandler->GetEntity(id)->GetAcceleration();
		lua_pushnumber(ls, acc.x);
		lua_pushnumber(ls, acc.y);
		return 2;
	}

	static int SetEntityPosition(lua_State* ls) //SetEntityPosition(id, x, y)
	{
		int id = static_cast<int>(luaL_checknumber(ls, 1));
		float x = static_cast<float>(luaL_checknumber(ls, 2));
		float y = static_cast<float>(luaL_checknumber(ls, 3));
		entityHandler->GetEntity(id)->SetPosition(Vec2f(x, y));
		return 0;
	}
	static int SetEntityVelocity(lua_State* ls) //SetEntityVelocity(id, xvel, yvel)
	{
		int id = static_cast<int>(luaL_checknumber(ls, 1));
		float xvel = static_cast<float>(luaL_checknumber(ls, 2));
		float yvel = static_cast<float>(luaL_checknumber(ls, 3));
		entityHandler->GetEntity(id)->SetVelocity(Vec2f(xvel, yvel));
		return 0;
	}
	static int SetEntityAcceleration(lua_State* ls) //SetEntityAcceleration(id, xacc, yacc)
	{
		int id = static_cast<int>(luaL_checknumber(ls, 1));
		float xacc = static_cast<float>(luaL_checknumber(ls, 2));
		float yacc = static_cast<float>(luaL_checknumber(ls, 3));
		entityHandler->GetEntity(id)->SetAcceleration(Vec2f(xacc, yacc));
		return 0;
	}

	static int GetEntityRadius(lua_State* ls) //r = GetEntityRadius(id)
	{
		int id = static_cast<int>(luaL_checknumber(ls, 1));
		float r = entityHandler->GetEntity(id)->GetRadius();
		lua_pushnumber(ls, r);
		return 1;
	}
}