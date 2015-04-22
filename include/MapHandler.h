#pragma once
#include <string>
#include <fstream>
#include "EntityHandler.h"
#include "ScriptHandler.h"

class MapHandler
{
private:
	float tilesize;
public:
	MapHandler(std::string filename, EntityHandler* entityHandler, AssetHandler* assetHandler, ScriptHandler* scriptHandler);
	~MapHandler();
};

