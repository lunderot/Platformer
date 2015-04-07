#include "ScriptHandler.h"

ScriptHandler::ScriptHandler(std::string scriptPath, EntityHandler* entityHandler, AssetHandler* assetHandler)
{
	this->ls = luaL_newstate();
	luaL_openlibs(ls);

	this->scriptPath = scriptPath;
	this->entityHandler = entityHandler;
	this->assetHandler = assetHandler;

	AddFile("global.lua");

	//Push Lua functions on the stack
	AddFunction(ScriptHandlerInternal::GetKeyCodeFromName, "GetKeyCodeFromName");

	AddFunction(ScriptHandlerInternal::GetKeyNameFromCode, "GetKeyNameFromCode");

	AddFunction(ScriptHandlerInternal::GetCameraId, "GetCameraId");

	AddFunction(ScriptHandlerInternal::GetEntityPosition, "GetEntityPosition");
	AddFunction(ScriptHandlerInternal::GetEntityVelocity, "GetEntityVelocity");
	AddFunction(ScriptHandlerInternal::GetEntityAcceleration, "GetEntityAcceleration");

	AddFunction(ScriptHandlerInternal::SetEntityPosition, "SetEntityPosition");
	AddFunction(ScriptHandlerInternal::SetEntityVelocity, "SetEntityVelocity");
	AddFunction(ScriptHandlerInternal::SetEntityAcceleration, "SetEntityAcceleration");

	AddFunction(ScriptHandlerInternal::GetEntityRadius, "GetEntityRadius");
}

ScriptHandler::~ScriptHandler()
{
	lua_close(ls);

	ls = nullptr;
	scriptPath = "";
	entityHandler = nullptr;
	assetHandler = nullptr;

	ScriptHandlerInternal::SetState(ls, scriptPath, entityHandler, assetHandler);
}

void ScriptHandler::AddFile(std::string filename)
{
	ScriptHandlerInternal::SetState(ls, scriptPath, entityHandler, assetHandler);

	std::string filepath = ScriptHandlerInternal::scriptPath + filename;
	luaL_dofile(ls, filepath.c_str());
}

void ScriptHandler::AddFunction(lua_CFunction function, std::string functionName)
{
	lua_pushcfunction(ls, function);
	lua_setglobal(ls, functionName.c_str());
}

void ScriptHandler::TriggerEvent(std::string id, int eventData)
{
	ScriptHandlerInternal::SetState(ls, scriptPath, entityHandler, assetHandler);

	lua_getglobal(ls, "triggerEvent");
	lua_pushstring(ls, id.c_str());
	lua_pushnumber(ls, eventData);
	if (lua_pcall(ls, 2, 0, 0) != 0)
	{
		throw std::runtime_error("Error running function 'triggerEvent': " + std::string(lua_tostring(ls, -1)));
	}
}
void ScriptHandler::TriggerEvent(SDL_MouseButtonEvent event)
{
	ScriptHandlerInternal::SetState(ls, scriptPath, entityHandler, assetHandler);

	lua_getglobal(ls, "triggerEvent");
	lua_pushstring(ls, "mouseButtonEvent");
	lua_pushnumber(ls, static_cast<int>(event.button));
	lua_pushnumber(ls, static_cast<int>(event.clicks));
	lua_pushnumber(ls, static_cast<int>(event.state));
	lua_pushnumber(ls, static_cast<int>(event.x));
	lua_pushnumber(ls, static_cast<int>(event.y));
	if (lua_pcall(ls, 6, 0, 0) != 0)
	{
		throw std::runtime_error("Error running function 'triggerEvent': " + std::string(lua_tostring(ls, -1)));
	}
}
void ScriptHandler::TriggerEvent(SDL_MouseMotionEvent event)
{
	ScriptHandlerInternal::SetState(ls, scriptPath, entityHandler, assetHandler);

	lua_getglobal(ls, "triggerEvent");
	lua_pushstring(ls, "mouseMotionEvent");
	lua_pushnumber(ls, static_cast<int>(event.state));
	lua_pushnumber(ls, static_cast<int>(event.x));
	lua_pushnumber(ls, static_cast<int>(event.y));
	lua_pushnumber(ls, static_cast<int>(event.xrel));
	lua_pushnumber(ls, static_cast<int>(event.yrel));
	if (lua_pcall(ls, 6, 0, 0) != 0)
	{
		throw std::runtime_error("Error running function 'triggerEvent': " + std::string(lua_tostring(ls, -1)));
	}
}
void ScriptHandler::TriggerEvent(SDL_KeyboardEvent event)
{
	ScriptHandlerInternal::SetState(ls, scriptPath, entityHandler, assetHandler);

	lua_getglobal(ls, "triggerEvent");
	lua_pushstring(ls, "keyboardEvent");
	lua_pushnumber(ls, static_cast<int>(event.keysym.sym));
	lua_pushnumber(ls, static_cast<int>(event.state));
	lua_pushboolean(ls, static_cast<bool>(event.repeat));
	if (lua_pcall(ls, 4, 0, 0) != 0)
	{
		throw std::runtime_error("Error running function 'triggerEvent': " + std::string(lua_tostring(ls, -1)));
	}
}
