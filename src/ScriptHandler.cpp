#include "ScriptHandler.h"

namespace ScriptHandler
{
	namespace Internal
	{
		lua_State* ls;
		std::string scriptPath;

		AssetHandler* assetHandler;
		EntityHandler* entityHandler;

		//Lua functions
		static int GetKeyCodeFromName(lua_State* ls)
		{
			std::string keyName(luaL_checkstring(ls, 1));
			SDL_Keycode key = SDL_GetKeyFromName(keyName.c_str());
			lua_pushnumber(ls, static_cast<int>(key));
			return 1;
		}
		static int GetKeyNameFromCode(lua_State* ls)
		{
			int keyCode = luaL_checknumber(ls, 1);
			const char* name = SDL_GetKeyName(keyCode);
			lua_pushstring(ls, name);
			return 1;
		}
	}

	//C++ functions
	void AddFile(std::string filename)
	{
		std::string filepath = Internal::scriptPath + filename;
		luaL_dofile(Internal::ls, filepath.c_str());
	}

	void TriggerEvent(std::string id, int eventData)
	{
		lua_getglobal(Internal::ls, "triggerEvent");
		lua_pushstring(Internal::ls, id.c_str());
		lua_pushnumber(Internal::ls, eventData);
		if (lua_pcall(Internal::ls, 2, 0, 0) != 0)
		{
			throw std::runtime_error("Error running function 'triggerEvent': " + std::string(lua_tostring(Internal::ls, -1)));
		}
	}
	void TriggerEvent(SDL_MouseButtonEvent event)
	{
		lua_getglobal(Internal::ls, "triggerEvent");
		lua_pushstring(Internal::ls, "mouseButtonEvent");
		lua_pushnumber(Internal::ls, static_cast<int>(event.button));
		lua_pushnumber(Internal::ls, static_cast<int>(event.clicks));
		lua_pushnumber(Internal::ls, static_cast<int>(event.state));
		lua_pushnumber(Internal::ls, static_cast<int>(event.x));
		lua_pushnumber(Internal::ls, static_cast<int>(event.y));
		if (lua_pcall(Internal::ls, 6, 0, 0) != 0)
		{
			throw std::runtime_error("Error running function 'triggerEvent': " + std::string(lua_tostring(Internal::ls, -1)));
		}
	}
	void TriggerEvent(SDL_MouseMotionEvent event)
	{
		lua_getglobal(Internal::ls, "triggerEvent");
		lua_pushstring(Internal::ls, "mouseMotionEvent");
		lua_pushnumber(Internal::ls, static_cast<int>(event.state));
		lua_pushnumber(Internal::ls, static_cast<int>(event.x));
		lua_pushnumber(Internal::ls, static_cast<int>(event.y));
		lua_pushnumber(Internal::ls, static_cast<int>(event.xrel));
		lua_pushnumber(Internal::ls, static_cast<int>(event.yrel));
		if (lua_pcall(Internal::ls, 6, 0, 0) != 0)
		{
			throw std::runtime_error("Error running function 'triggerEvent': " + std::string(lua_tostring(Internal::ls, -1)));
		}
	}
	void TriggerEvent(SDL_KeyboardEvent event)
	{
		lua_getglobal(Internal::ls, "triggerEvent");
		lua_pushstring(Internal::ls, "keyboardEvent");
		lua_pushnumber(Internal::ls, static_cast<int>(event.keysym.sym));
		lua_pushnumber(Internal::ls, static_cast<int>(event.state));
		lua_pushboolean(Internal::ls, static_cast<bool>(event.repeat));
		if (lua_pcall(Internal::ls, 4, 0, 0) != 0)
		{
			throw std::runtime_error("Error running function 'triggerEvent': " + std::string(lua_tostring(Internal::ls, -1)));
		}
	}

	void Init(std::string scriptPath, EntityHandler* entityHandler, AssetHandler* assetHandler)
	{
		Internal::ls = luaL_newstate();
		luaL_openlibs(Internal::ls);
		Internal::scriptPath = scriptPath;
		AddFile("global.lua");

		Internal::entityHandler = entityHandler;
		Internal::assetHandler = assetHandler;

		//Push Lua functions on the stack
		lua_pushcfunction(Internal::ls, Internal::GetKeyCodeFromName);
		lua_setglobal(Internal::ls, "GetKeyCodeFromName");

		lua_pushcfunction(Internal::ls, Internal::GetKeyNameFromCode);
		lua_setglobal(Internal::ls, "GetKeyNameFromCode");
	}
	void Close()
	{
		lua_close(Internal::ls);
	}
};