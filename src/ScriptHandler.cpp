#include "ScriptHandler.h"

ScriptHandler::ScriptHandler(EntityHandler* entityHandler, AssetHandler* assetHandler)
{
	this->ls = luaL_newstate();
	luaL_openlibs(ls);

	this->entityHandler = entityHandler;
	this->assetHandler = assetHandler;

	AddFile("assets/scripts/global.lua");

	//Push Lua functions on the stack
	AddFunction(ScriptHandlerInternal::GetKeyCodeFromName, "GetKeyCodeFromName");

	AddFunction(ScriptHandlerInternal::GetKeyNameFromCode, "GetKeyNameFromCode");

	AddFunction(ScriptHandlerInternal::GetCameraId, "GetCameraId");
	AddFunction(ScriptHandlerInternal::GetCameraSize, "GetCameraSize");
	AddFunction(ScriptHandlerInternal::GetWorldPositionFromScreenPosition, "GetWorldPositionFromScreenPosition");
	AddFunction(ScriptHandlerInternal::AddEntity, "AddEntity");
	AddFunction(ScriptHandlerInternal::AddCollisionLine, "AddCollisionLine");
	AddFunction(ScriptHandlerInternal::RemoveEntity, "RemoveEntity");
	AddFunction(ScriptHandlerInternal::SaveToFile, "SaveToFile");
	AddFunction(ScriptHandlerInternal::GetFirstPlayerId, "GetFirstPlayerId");

	AddFunction(ScriptHandlerInternal::GetRenderPosition, "GetRenderPosition");
	AddFunction(ScriptHandlerInternal::SetRenderPosition, "SetRenderPosition");

	AddFunction(ScriptHandlerInternal::ApplyForceOffset, "ApplyForceOffset");
	AddFunction(ScriptHandlerInternal::ApplyForce, "ApplyForce");
	AddFunction(ScriptHandlerInternal::ApplyImpulseOffset, "ApplyImpulseOffset");
	AddFunction(ScriptHandlerInternal::ApplyImpulse, "ApplyImpulse");

	AddFunction(ScriptHandlerInternal::GetPosition, "GetPosition");
	AddFunction(ScriptHandlerInternal::SetPosition, "SetPosition");
	AddFunction(ScriptHandlerInternal::GetAngle, "GetAngle");

	AddFunction(ScriptHandlerInternal::SetMarkerTexture, "SetMarkerTexture");
}

ScriptHandler::~ScriptHandler()
{
	lua_close(ls);

	ls = nullptr;
	entityHandler = nullptr;
	assetHandler = nullptr;

	ScriptHandlerInternal::SetState(ls, entityHandler, assetHandler);
}

void ScriptHandler::AddFile(std::string filename)
{
	ScriptHandlerInternal::SetState(ls, entityHandler, assetHandler);

	luaL_dofile(ls, filename.c_str());
}

void ScriptHandler::AddFunction(lua_CFunction function, std::string functionName)
{
	lua_pushcfunction(ls, function);
	lua_setglobal(ls, functionName.c_str());
}

void ScriptHandler::TriggerEvent(std::string id)
{
	ScriptHandlerInternal::SetState(ls, entityHandler, assetHandler);

	lua_getglobal(ls, "errorHandler");
	int errorHandlerIndex = lua_gettop(ls);

	lua_getglobal(ls, "triggerEvent");
	lua_pushstring(ls, id.c_str());
	if (lua_pcall(ls, 1, 0, errorHandlerIndex) != 0)
	{
		std::cerr << std::string(lua_tostring(ls, -1)) << std::endl;
		lua_pop(ls, 1);
	}
}
void ScriptHandler::TriggerEvent(std::string id, float deltaTime)
{
	ScriptHandlerInternal::SetState(ls, entityHandler, assetHandler);

	lua_getglobal(ls, "errorHandler");
	int errorHandlerIndex = lua_gettop(ls);

	lua_getglobal(ls, "triggerEvent");
	lua_pushstring(ls, id.c_str());
	lua_pushnumber(ls, deltaTime);
	if (lua_pcall(ls, 2, 0, errorHandlerIndex) != 0)
	{
		std::cerr << std::string(lua_tostring(ls, -1)) << std::endl;
		lua_pop(ls, 1);
	}
}

void ScriptHandler::TriggerEvent(SDL_MouseButtonEvent event)
{
	ScriptHandlerInternal::SetState(ls, entityHandler, assetHandler);
	
	lua_getglobal(ls, "errorHandler");
	int errorHandlerIndex = lua_gettop(ls);

	lua_getglobal(ls, "triggerEvent");
	lua_pushstring(ls, "mouseButtonEvent");
	lua_pushnumber(ls, static_cast<int>(event.button));
	lua_pushnumber(ls, static_cast<int>(event.clicks));
	lua_pushnumber(ls, static_cast<int>(event.state));
	lua_pushnumber(ls, static_cast<int>(event.x));
	lua_pushnumber(ls, static_cast<int>(event.y));
	if (lua_pcall(ls, 6, 0, errorHandlerIndex) != 0)
	{
		std::cerr << std::string(lua_tostring(ls, -1)) << std::endl;
		lua_pop(ls, 1);
	}
}
void ScriptHandler::TriggerEvent(SDL_MouseMotionEvent event)
{
	ScriptHandlerInternal::SetState(ls, entityHandler, assetHandler);

	lua_getglobal(ls, "errorHandler");
	int errorHandlerIndex = lua_gettop(ls);

	lua_getglobal(ls, "triggerEvent");
	lua_pushstring(ls, "mouseMotionEvent");
	lua_pushnumber(ls, static_cast<int>(event.state));
	lua_pushnumber(ls, static_cast<int>(event.x));
	lua_pushnumber(ls, static_cast<int>(event.y));
	lua_pushnumber(ls, static_cast<int>(event.xrel));
	lua_pushnumber(ls, static_cast<int>(event.yrel));
	if (lua_pcall(ls, 6, 0, errorHandlerIndex) != 0)
	{
		std::cerr << std::string(lua_tostring(ls, -1)) << std::endl;
		lua_pop(ls, 1);
	}
}
void ScriptHandler::TriggerEvent(SDL_KeyboardEvent event)
{
	ScriptHandlerInternal::SetState(ls, entityHandler, assetHandler);

	lua_getglobal(ls, "errorHandler");
	int errorHandlerIndex = lua_gettop(ls);

	lua_getglobal(ls, "triggerEvent");
	lua_pushstring(ls, "keyboardEvent");
	lua_pushnumber(ls, static_cast<int>(event.keysym.sym));
	lua_pushnumber(ls, static_cast<int>(event.state));
	lua_pushboolean(ls, static_cast<bool>(event.repeat != 0));
	if (lua_pcall(ls, 4, 0, errorHandlerIndex) != 0)
	{
		std::cerr << std::string(lua_tostring(ls, -1)) << std::endl;
		lua_pop(ls, 1);
	}
}
