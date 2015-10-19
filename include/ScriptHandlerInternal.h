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
		glm::vec2 size = camera->GetSize();
		lua_pushnumber(ls, size.x);
		lua_pushnumber(ls, size.y);
		return 2;
	}
	static int GetWorldPositionFromScreenPosition(lua_State* ls) //x,y = GetWorldPositionFromScreenPosition(x, y)
	{
		float x = static_cast<float>(luaL_checknumber(ls, 1));
		float y = static_cast<float>(luaL_checknumber(ls, 2));
		Camera* camera = dynamic_cast<Camera*>(entityHandler->GetEntity(entityHandler->GetCameraId()));

		glm::vec4 translatedPoint = glm::inverse(camera->GetCameraMatrix()) * glm::vec4(x, y, 1, 1);
		lua_pushnumber(ls, translatedPoint.x);
		lua_pushnumber(ls, translatedPoint.y);
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

	static int AddCollisionLine(lua_State* ls) //AddCollisionLine(x1, y1, x2, y2)
	{
		glm::vec2 point1;
		glm::vec2 point2;
		point1.x = static_cast<float>(luaL_checknumber(ls, 1));
		point1.y = static_cast<float>(luaL_checknumber(ls, 2));
		point2.x = static_cast<float>(luaL_checknumber(ls, 3));
		point2.y = static_cast<float>(luaL_checknumber(ls, 4));
		entityHandler->AddCollisionLine(new LineSegment(point1, point2));
		return 0;
	}

	static int RemoveEntity(lua_State* ls) //result = RemoveEntity(id)
	{
		unsigned int id = static_cast<unsigned int>(luaL_checknumber(ls, 1));
		bool result = entityHandler->Remove(id);
		lua_pushboolean(ls, result);
		return 1;
	}

	static int SaveToFile(lua_State* ls) //SaveToFile(filename)
	{
		std::string filename(luaL_checkstring(ls, 1));
		entityHandler->SaveToFile(filename, assetHandler);
		return 0;
	}

	static int GetFirstPlayerId(lua_State* ls) //id = GetFirstPlayerId()
	{
		lua_pushnumber(ls, entityHandler->GetFirstPlayerId());
		return 1;
	}

	//Entity functions
	static int GetRenderPosition(lua_State* ls) //x,y = GetRenderPosition(id)
	{
		int id = static_cast<int>(luaL_checknumber(ls, 1));

		Entity* entity = entityHandler->GetEntity(id);
		glm::vec2 position;
		if (entity)
		{
			position = entity->GetRenderPosition();
		}
		lua_pushnumber(ls, position.x);
		lua_pushnumber(ls, position.y);
		return 2;
	}

	static int SetRenderPosition(lua_State* ls) //SetRenderPosition(id, x, y)
	{
		int id = static_cast<int>(luaL_checknumber(ls, 1));
		glm::vec2 position;
		position.x = static_cast<glm::f32>(luaL_checknumber(ls, 2));
		position.y = static_cast<glm::f32>(luaL_checknumber(ls, 3));

		Entity* entity = entityHandler->GetEntity(id);
		if (entity)
		{
			entity->SetRenderPosition(position);
		}
		return 0;
	}

	//Physics functions
	static int ApplyForceOffset(lua_State* ls) //ApplyForceOffset(id, forcex, forcey, offsetx, offsety)
	{
		int id = static_cast<int>(luaL_checknumber(ls, 1));
		glm::f32 forcex =	static_cast<glm::f32>(luaL_checknumber(ls, 2));
		glm::f32 forcey =	static_cast<glm::f32>(luaL_checknumber(ls, 3));
		glm::f32 offsetx =	static_cast<glm::f32>(luaL_checknumber(ls, 4));
		glm::f32 offsety =	static_cast<glm::f32>(luaL_checknumber(ls, 5));

		Entity* entity = entityHandler->GetEntity(id);
		if (entity)
		{
			Body* body = entity->GetPhysicsBody();
			if (body)
			{
				body->ApplyForce(glm::vec2(forcex, forcey), glm::vec2(offsetx, offsety));
			}
		}
		return 0;
	}
	static int ApplyForce(lua_State* ls) //ApplyForce(id, forcex, forcey)
	{
		int id = static_cast<int>(luaL_checknumber(ls, 1));
		glm::f32 forcex = static_cast<glm::f32>(luaL_checknumber(ls, 2));
		glm::f32 forcey = static_cast<glm::f32>(luaL_checknumber(ls, 3));

		Entity* entity = entityHandler->GetEntity(id);
		if (entity)
		{
			Body* body = entity->GetPhysicsBody();
			if (body)
			{
				body->ApplyForce(glm::vec2(forcex, forcey));
			}
		}
		return 0;
	}
	static int ApplyImpulseOffset(lua_State* ls) //ApplyImpulseOffset(id, forcex, forcey, time, offsetx, offsety)
	{
		int id = static_cast<int>(luaL_checknumber(ls, 1));
		glm::f32 forcex = static_cast<glm::f32>(luaL_checknumber(ls, 2));
		glm::f32 forcey = static_cast<glm::f32>(luaL_checknumber(ls, 3));
		glm::f32 time = static_cast<glm::f32>(luaL_checknumber(ls, 4));
		glm::f32 offsetx = static_cast<glm::f32>(luaL_checknumber(ls, 5));
		glm::f32 offsety = static_cast<glm::f32>(luaL_checknumber(ls, 6));
		
		Entity* entity = entityHandler->GetEntity(id);
		if (entity)
		{
			Body* body = entity->GetPhysicsBody();
			if (body)
			{
				body->ApplyImpulse(glm::vec2(forcex, forcey), time, glm::vec2(offsetx, offsety));
			}
		}
		return 0;
	}
	static int ApplyImpulse(lua_State* ls) //ApplyImpulse(id, forcex, forcey, time)
	{
		int id = static_cast<int>(luaL_checknumber(ls, 1));
		glm::f32 forcex = static_cast<glm::f32>(luaL_checknumber(ls, 2));
		glm::f32 forcey = static_cast<glm::f32>(luaL_checknumber(ls, 3));
		glm::f32 time = static_cast<glm::f32>(luaL_checknumber(ls, 4));

		Entity* entity = entityHandler->GetEntity(id);
		if (entity)
		{
			Body* body = entity->GetPhysicsBody();
			if (body)
			{
				body->ApplyImpulse(glm::vec2(forcex, forcey), time);
			}
		}
		return 0;
	}
	static int GetPosition(lua_State* ls) //x,y = GetPosition(id)
	{
		int id = static_cast<int>(luaL_checknumber(ls, 1));
		glm::vec2 position;

		Entity* entity = entityHandler->GetEntity(id);
		if (entity)
		{
			Body* body = entity->GetPhysicsBody();
			if (body)
			{
				position = body->GetPosition();
			}
		}
		lua_pushnumber(ls, position.x);
		lua_pushnumber(ls, position.y);
		return 2;
	}
	static int SetPosition(lua_State* ls) //SetPosition(id, x, y)
	{
		int id = static_cast<int>(luaL_checknumber(ls, 1));
		glm::vec2 position(static_cast<glm::f32>(luaL_checknumber(ls, 2)), static_cast<glm::f32>(luaL_checknumber(ls, 3)));

		Entity* entity = entityHandler->GetEntity(id);
		if (entity)
		{
			Body* body = entity->GetPhysicsBody();
			if (body)
			{
				body->SetPosition(position);
			}
		}
		return 0;
	}

	static int GetAngle(lua_State* ls) //a = GetAngle(id)
	{
		int id = static_cast<int>(luaL_checknumber(ls, 1));
		glm::f32 angle;

		Entity* entity = entityHandler->GetEntity(id);
		if (entity)
		{
			Body* body = entity->GetPhysicsBody();
			if (body)
			{
				angle = body->GetAngle();
			}
		}
		lua_pushnumber(ls, angle);
		return 1;
	}

	//Marker functions
	static int SetMarkerTexture(lua_State* ls) //SetMarkerTexture(id, filename)
	{
		int id = static_cast<int>(luaL_checknumber(ls, 1));
		std::string filename(luaL_checkstring(ls, 2));
		Marker* marker = dynamic_cast<Marker*>(entityHandler->GetEntity(id));
		if (marker)
		{
			marker->SetTexture(assetHandler->GetTexture(filename));
		}
		return 0;
	}
}